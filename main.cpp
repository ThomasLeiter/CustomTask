#include <iostream>
#include <thread>

template <typename _FunctionType>
class Task;

template <typename _ReturnType, typename... _ArgType>
class Task<_ReturnType (*)(_ArgType...)>
{
    _ReturnType result;
    _ReturnType (*func_ptr)(_ArgType...);

public:
    Task(_ReturnType (*_func_ptr)(_ArgType...)) : func_ptr{_func_ptr} {}
    _ReturnType operator()(_ArgType... args) { return result = func_ptr(args...); }
    _ReturnType get_result() const { return result; }
};

template <typename... _ArgType>
class Task<void (*)(_ArgType...)>
{
    void (*func_ptr)(_ArgType...);

public:
    Task(void (*_func_ptr)(_ArgType...)) : func_ptr{_func_ptr} {}
    void operator()(_ArgType... args) { func_ptr(args...); }
    void get_result() const { std::cerr << "WARNING: Trying to retrieve result of void task.\n"; }
};

template <typename _ReturnType>
class Task<_ReturnType (*)()>
{
    _ReturnType result;
    _ReturnType (*func_ptr)();

public:
    Task(_ReturnType (*_func_ptr)()) : func_ptr{_func_ptr} {}
    _ReturnType operator()() { return result = func_ptr(); }
    _ReturnType get_result() const { return result; }
};

template <>
class Task<void (*)()>
{
    void (*func_ptr)();

public:
    Task(void (*_func_ptr)()) : func_ptr{_func_ptr} {}
    void operator()() { func_ptr(); }
    void get_result() const { std::cerr << "WARNING: Trying to retrieve result of void task.\n"; }
};

void say_hello() { std::cout << "Hello World!\n"; }
void say_welcome(const std::string &name) { std::cout << "Hello " << name << "!\n"; }

int double_or_nothing(int number) { return 2 * number; }
int divide_and_conquer(int divident, int divisor) { return divident / divisor; }

int main()
{
    auto t_hello = Task<void (*)()>{say_hello};
    auto t_welcome = Task<void (*)(const std::string &)>{say_welcome};

    auto t_double = Task<int (*)(int)>{double_or_nothing};
    auto t_divide = Task<int (*)(int, int)>{divide_and_conquer};

    auto t1 = std::thread(std::ref(t_hello));
    auto t2 = std::thread(std::ref(t_welcome), "Bob");
    auto t3 = std::thread(std::ref(t_double), 21);
    auto t4 = std::thread(std::ref(t_divide), 999, 27);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::cout << t_double.get_result() << "\n";
    std::cout << t_divide.get_result() << "\n";

    return 0;
}
// main.cpp

#include "task.h"

#include <iostream>
#include <thread>


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
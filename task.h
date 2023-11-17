#ifndef TASK_H
#define TASK_H

#include <iostream>

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


#endif // TASK_H
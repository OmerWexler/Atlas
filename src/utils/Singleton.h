#pragma once

#include <future>

template <class T>
class Singleton: public T
{
private:
    Singleton()= default;
    ~Singleton()= default;
    Singleton(const Singleton&)= delete;
    Singleton& operator=(const Singleton&)= delete;
    
public:
    static Singleton& Singleton::GetInstance() 
    {
        static Singleton Instance;
        return Instance;
    }
};
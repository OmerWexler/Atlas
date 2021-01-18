#pragma once

template <class T>
class Singleton: public T
{
private:
    Singleton() {};

public:
    Singleton(Singleton &other) = delete;
    void operator=(const Singleton &) = delete;
    
    inline static T& GetInstance() 
    {
        static T* Instance;

        if (Instance == nullptr)
        {
            Instance = new T();
        }

        return *Instance;
    }
    
    ~Singleton() { delete T; }
};
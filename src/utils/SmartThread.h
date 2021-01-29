#pragma once

#include <future>
#include <thread>

#include "Utils.h"
#include "Logger.h"
#include "Singleton.h"

using namespace std;

class SmartThread
{
private:
    thread RunThread;
    bool IsRunning = false;
    promise<void> ShouldRunPromise;
    promise<void> IsRunningPromise;
    string Name;

public:
    SmartThread() {};

    template<class _Fn, class... _Args>
    SmartThread(string Name, float Interval, _Fn&& Runnable, _Args... Args)
    {
        this->Name = Name;
        IsRunning = true;
        
        RunThread = thread([this, Runnable, Interval, Args...](future<void> ShouldRunFuture){
            thread TempThread;
            IsRunningPromise.set_value_at_thread_exit();

            if (Interval == 0.f)
            {
                Singleton<Logger>::GetInstance().Debug("Statring single call to SmartThread - " + this->Name);
                TempThread = thread(Runnable, Args...);
                TempThread.join();
            }
            else if (Interval > 0.f)
            {
                Singleton<Logger>::GetInstance().Debug("Statring periodic call to SmartThread - " + this->Name);

                while (ShouldRunFuture.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout)
                {
                    TempThread = thread(Runnable, Args...);
                    TempThread.join();
                    Utils::CPSleep(Interval);
                }
            }
        }, move(ShouldRunPromise.get_future()));
    }

    void Stop()
    {   
        if (!IsRunning)
            return;
        
        Singleton<Logger>::GetInstance().Debug("Killing SmartThread - " + Name);
        ShouldRunPromise.set_value();
        future<void> IsRunningFuture = IsRunningPromise.get_future();
    
        IsRunningFuture.wait();
        IsRunning = false;

        RunThread.join();
        Singleton<Logger>::GetInstance().Debug(Name + " succesfully killed");
    }

    bool GetIsRunning() { 
        return IsRunning; 
    }
};
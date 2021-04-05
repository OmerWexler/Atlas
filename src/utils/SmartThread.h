#pragma once

#include <future>
#include <thread>

#include "Utils.h"
#include "Logger.h"
#include "Singleton.h"

#define ST_SINGLE_CALL -1000.f
#define ST_UNLIMITED_RUNTIME -2000.f

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
    SmartThread(string Name, float PollFrequency, _Fn&& Runnable, _Args... Args)
    {
        this->Name = Name;
        IsRunning = true;
        
        RunThread = thread([this, Runnable, PollFrequency, Args...](future<void> ShouldRunFuture){
            thread TempThread;
            IsRunningPromise.set_value_at_thread_exit();

            if (PollFrequency == ST_SINGLE_CALL)
            {
                Singleton<Logger>::GetInstance().Debug("Statring single call to SmartThread - " + this->Name);
                TempThread = thread(Runnable, Args...);
                TempThread.join();
            }
            else
            {
                Singleton<Logger>::GetInstance().Debug("Statring periodic call to SmartThread - " + this->Name);
                if (PollFrequency == ST_UNLIMITED_RUNTIME)
                {
                    while (ShouldRunFuture.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout)
                    {   
                        TempThread = thread(Runnable, Args...);
                        TempThread.join();
                    }
                }
                else
                {
                    double StartTime;
                    double EndTime;
                    double CallTime;
                    while (ShouldRunFuture.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout)
                    {   
                        StartTime = Utils::NanoToSec(Utils::GetTimeNS());
                        
                        TempThread = thread(Runnable, Args...);
                        TempThread.join();

                        EndTime = Utils::NanoToSec(Utils::GetTimeNS());
                        
                        CallTime = (EndTime - StartTime);
                        if (PollFrequency > CallTime) 
                        {
                            Utils::CPSleep(PollFrequency - CallTime);
                        }
                    }
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

    bool GetIsRunning() const
    { 
        return IsRunning; 
    }
};
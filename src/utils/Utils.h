#pragma once

#include <chrono>
#include <thread>

using namespace std;

class Utils
{
public:
    static void CPSleep(int TimeSeconds)
    {
        this_thread::sleep_for(chrono::seconds(1));
    }
};
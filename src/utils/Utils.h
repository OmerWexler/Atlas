#pragma once

#include <chrono>
#include <thread>
#include <random>
#include <string>

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>

#ifdef _DEBUG
    #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
    // Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
    // allocations to be of _CLIENT_BLOCK type
#else
    #define DBG_NEW new
#endif

#pragma comment(lib, "user32.lib")
#pragma warning( disable : 4244 ) 
#pragma warning( disable : 4996 ) 
#pragma warning( disable : 4267 ) 


using namespace std;
using namespace std::chrono;

class Utils
{
public:
    inline static void CPSleep(float TimeSeconds)
    {
        this_thread::sleep_for(chrono::milliseconds((int) (TimeSeconds * 1000)));
    }

    inline static uint64_t GetTimeNS()
    {
        high_resolution_clock::time_point tp = high_resolution_clock::now();

        return (tp - high_resolution_clock::time_point()).count();
    }

    inline static double NanoToMilli(uint64_t Nano)
    {
        return Nano / 1e6;
    }

    inline static double NanoToSec(uint64_t Nano)
    {
        return Nano / 1e9;
    }

    inline static uint64_t SecToNano(uint64_t Sec)
    {
        return Sec * (uint64_t) 1e9;
    }

    inline static double HZToGHZ(uint64_t Nano)
    {
        return Nano / 1e9;
    }

    inline static uint64_t BytesToMegabytes(uint64_t Bytes)
    {
        return Bytes / 1000000;
    }

    inline static uint64_t SafeRound(double Value)
    {
        return (uint64_t) Value;
    }

    inline static void SetupMemoryCheck()
    {
        _CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_WNDW );
        // _CrtSetReportFile( _CRT_WARN, _CRTDBG_MODE_FILE );
        
        _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_WNDW );
        // _CrtSetReportFile( _CRT_ERROR, _CRTDBG_MODE_FILE );

        _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_WNDW );
        // _CrtSetReportFile( _CRT_ASSERT, _CRTDBG_MODE_FILE );
        
        _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    }

    inline static string GenerateRandomDescriptor(size_t Length)
    {
        const std::string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

        random_device random_device;
        mt19937 generator(random_device());
        uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

        string random_string;

        for (size_t i = 0; i < Length; ++i)
        {
            random_string += CHARACTERS[distribution(generator)];
        }

        return random_string;
    }

    inline static string PadInt(int Value, int Size)
    {
        string Padded = to_string(Value);

        while (Padded.length() < Size)
        {
            Padded = "0" + Padded;
        }

        return Padded;
    }
};
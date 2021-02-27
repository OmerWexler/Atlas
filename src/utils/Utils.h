#pragma once

#include <chrono>
#include <thread>

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
    #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
    // Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
    // allocations to be of _CLIENT_BLOCK type
#else
    #define DBG_NEW new
#endif

#pragma comment(lib, "user32.lib")

using namespace std;

class Utils
{
public:
    inline static void CPSleep(float TimeSeconds)
    {
        this_thread::sleep_for(chrono::milliseconds((int) (TimeSeconds * 1000)));
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
};
#pragma once

#include <chrono>
#include <thread>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#pragma comment(lib, "user32.lib")

using namespace std;

class Utils
{
public:
    inline static void CPSleep(int TimeSeconds)
    {
        this_thread::sleep_for(chrono::seconds(TimeSeconds));
    }

    inline static void SetupMemoryCheck()
    {
        _CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE );
        _CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDOUT );

        _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_FILE );
        _CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDOUT );

        _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_FILE );
        _CrtSetReportFile( _CRT_ASSERT, _CRTDBG_FILE_STDOUT );
        _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    }
};
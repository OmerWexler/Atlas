#include "WinPerformanceAnalyzer.h"
#include "Windows.h"
#include "winternl.h"
#include "Utils.h"


int WinPerformanceAnalyzer::LoadDryStats(PCPerformance& Performance)
{
    MEMORYSTATUSEX RAMStats;
    RAMStats.dwLength = sizeof (RAMStats);
    if (!GlobalMemoryStatusEx(&RAMStats))
        return GetLastError();

    Performance.RAMPerformance.TotalPhysicalBytes = RAMStats.ullTotalPhys;
    Performance.RAMPerformance.AvailablePhysicalBytes = RAMStats.ullAvailPhys;
    Performance.RAMPerformance.MemoryLoad = RAMStats.dwMemoryLoad;

    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    Performance.CPUPerformance.Cores = sysinfo.dwNumberOfProcessors;

    return 0;
}

int WinPerformanceAnalyzer::MeasureCPUFrequency(PCPerformance& PCPerformance)
{
    unsigned long long int StartCycles = __rdtsc();
    unsigned long long int StartTime = GetTickCount64();
 
    Utils::CPSleep(1.f);
    unsigned long long int EndCycles = __rdtsc();
    unsigned long long int EndTime = GetTickCount64();
 
    unsigned long long int msDiff = (EndTime - StartTime);
    unsigned long long int CycleDiff = EndCycles - StartCycles;
    unsigned long long int Freq = CycleDiff / msDiff / 1000;

    PCPerformance.CPUPerformance.FrequencyHZ = Freq;
    return 0;
}

static float GetMomenteryCPULoad(unsigned long long idleTicks, unsigned long long totalTicks)
{
    static unsigned long long _previousTotalTicks = 0;
    static unsigned long long _previousIdleTicks = 0;

    unsigned long long totalTicksSinceLastTime = totalTicks-_previousTotalTicks;
    unsigned long long idleTicksSinceLastTime  = idleTicks-_previousIdleTicks;

    float ret = 1.0f-((totalTicksSinceLastTime > 0) ? ((float)idleTicksSinceLastTime)/totalTicksSinceLastTime : 0);

    _previousTotalTicks = totalTicks;
    _previousIdleTicks  = idleTicks;
    return ret;
}

static unsigned long long FileTimeToInt64(const FILETIME & ft) 
{
    return (((unsigned long long)(ft.dwHighDateTime))<<32)|((unsigned long long)ft.dwLowDateTime);
}

int WinPerformanceAnalyzer::MeasureCPULoad(PCPerformance& PCPerformance)
{
    FILETIME idleTime, kernelTime, userTime;
    if (GetSystemTimes(&idleTime, &kernelTime, &userTime))
    {
        Filter.Feed((int) (GetMomenteryCPULoad(FileTimeToInt64(idleTime), FileTimeToInt64(kernelTime) + FileTimeToInt64(userTime)) * 100.f));  
    }

    PCPerformance.CPUPerformance.CPULoad = Filter.GetValue();
    return 0;
}
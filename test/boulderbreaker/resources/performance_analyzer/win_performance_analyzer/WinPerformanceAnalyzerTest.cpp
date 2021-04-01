#include "WinPerformanceAnalyzer.h"
#include "Singleton.h"
#include "Logger.h"
#include "Utils.h"

using namespace std;

int WinPerformanceAnalyzerTest() 
{
    WinPerformanceAnalyzer Test;
    
    PCPerformance Performance;
    Test.LoadDryStats(Performance);

    Singleton<Logger>::GetInstance().Debug("TotalPhysicalBytes: " + to_string(Performance.RAMPerformance.TotalPhysicalBytes));
    Singleton<Logger>::GetInstance().Debug("AvailablePhysicalBytes: " + to_string(Performance.RAMPerformance.AvailablePhysicalBytes));
    Singleton<Logger>::GetInstance().Debug("MemoryLoad: " + to_string(Performance.RAMPerformance.MemoryLoad));
    Singleton<Logger>::GetInstance().Debug("CPUCores: " + to_string(Performance.CPUPerformance.Cores));
    
    Test.MeasureCPUFrequency(Performance);
    Singleton<Logger>::GetInstance().Debug("FreqHZ: " + to_string(Performance.CPUPerformance.FrequencyHZ));

    for (int i = 0; i < 10; i++)
    {
        Test.MeasureCPULoad(Performance);
        Utils::CPSleep(0.5f);
        Singleton<Logger>::GetInstance().Debug("CPU Load: " + to_string(Performance.CPUPerformance.CPULoad));
    }

    return 0;
}
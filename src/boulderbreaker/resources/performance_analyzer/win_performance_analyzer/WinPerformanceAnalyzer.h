#pragma once

#include "IPerformanceAnalyzer.h"
#include "CyclicKalmanFilter.h"

class WinPerformanceAnalyzer: IPerformanceAnalyzer
{
private:
    float MeasurementInterval = 0.2f;
    CyclicKalmanFilter Filter;

public:
    WinPerformanceAnalyzer() : Filter(3) {}
    
    int LoadDryStats(PCPerformance& PCPerformance);
    int MeasureCPUFrequency(PCPerformance& PCPerformance);
    int MeasureCPULoad(PCPerformance& PCPerformance);
};
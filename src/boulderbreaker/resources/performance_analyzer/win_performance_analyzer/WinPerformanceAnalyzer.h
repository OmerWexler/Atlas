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
    WinPerformanceAnalyzer(int KalmanFilterSize) : Filter(KalmanFilterSize) {}
    
    int LoadDryStats(PCPerformance& PCPerformance);
    int MeasureCPUFrequency(PCPerformance& PCPerformance, float Timelapse=0.02f);
    int MeasureCPULoad(PCPerformance& PCPerformance);
};
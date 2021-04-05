#pragma once

#include "PCPerformance.h"

class IPerformanceAnalyzer
{
public:
    virtual int LoadDryStats(PCPerformance& PCPerformance) = 0;
    virtual int MeasureCPUFrequency(PCPerformance& PCPerformance, float Timelapse=0.02f) = 0;
    virtual int MeasureCPULoad(PCPerformance& PCPerformance) = 0;
};
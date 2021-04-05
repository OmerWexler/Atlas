#include "PCPerformance.h"
#pragma warning( disable : 4244 ) 

bool PCPerformance::operator>(PCPerformance& Other)
{
    float ScoreSum = 
            (1 / 1000.0 + (float) CPUPerformance.Cores) / 
            (1 / 1000.0 + (float) Other.CPUPerformance.Cores) +
        
            (1 / 1000.0 + (float) CPUPerformance.FrequencyHZ) / 
            (1 / 1000.0 + (float) Other.CPUPerformance.FrequencyHZ) +
        
            (1 / 1000.0 + (float) Other.CPUPerformance.CPULoad) / 
            (1 / 1000.0 + (float) CPUPerformance.CPULoad) +
        
            (1 / 1000.0 + (float) RAMPerformance.TotalPhysicalBytes) / 
            (1 / 1000.0 + (float) Other.RAMPerformance.TotalPhysicalBytes) +
        
            (1 / 1000.0 + (float) RAMPerformance.AvailablePhysicalBytes) / 
            (1 / 1000.0 + (float) Other.RAMPerformance.AvailablePhysicalBytes) +
        
            (1 / 1000.0 + (float) Other.RAMPerformance.MemoryLoad) / 
            (1 / 1000.0 + (float) RAMPerformance.MemoryLoad);

    float AverageScore = ScoreSum / 6.f;
    
    return AverageScore > 1.f;
}

bool PCPerformance::operator<(PCPerformance& Other)
{
    return Other > *this;
}

PCPerformance& PCPerformance::operator=(const PCPerformance& Other)
{
    CPUPerformance.Cores = Other.CPUPerformance.Cores;
    CPUPerformance.FrequencyHZ = Other.CPUPerformance.FrequencyHZ;
    CPUPerformance.CPULoad = Other.CPUPerformance.CPULoad;
    RAMPerformance.TotalPhysicalBytes = Other.RAMPerformance.TotalPhysicalBytes;
    RAMPerformance.AvailablePhysicalBytes = Other.RAMPerformance.AvailablePhysicalBytes;
    RAMPerformance.MemoryLoad = Other.RAMPerformance.MemoryLoad;

    return *this;
}

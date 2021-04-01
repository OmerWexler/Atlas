#pragma once

struct CPUPerformance
{
    int Cores;
    unsigned long long int FrequencyHZ;
    int CPULoad; 
};

struct RAMPerformance
{
    unsigned long long int TotalPhysicalBytes;
    unsigned long long int AvailablePhysicalBytes;
    int MemoryLoad;
};

struct PCPerformance
{
    CPUPerformance CPUPerformance;
    RAMPerformance RAMPerformance;
};
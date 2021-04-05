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

    bool operator > (PCPerformance& Other);
    bool operator < (PCPerformance& Other);
    PCPerformance& operator = (const PCPerformance& Other);
};
#pragma once

struct CPUPerformance
{
    int CPUCores;
    int CPUFrequency;
    int CPULoad; // 0 - 100
};

struct PCPerformance
{
    CPUPerformance CPUPerformance;
};
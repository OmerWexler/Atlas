#pragma once

struct CPUPerformance
{
    int CPUCores;
    int CPUFrequency;
    float CPULoad;
};

struct PCPerformance
{
    CPUPerformance CPUPerformance;
};

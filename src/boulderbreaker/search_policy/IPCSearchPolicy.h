#pragma once

#include "PCPerformance.h"

class IPCSearchPolicy
{
    void GetBetter(PCPerformance& OutBetter, const PCPerformance& P1, const PCPerformance P2);
    struct PCPerformace& GetMinimumAcceptablePerformance();
    int GetRange();
};
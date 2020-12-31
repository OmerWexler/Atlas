#pragma once

#include "IJob.h"

using namespace std;

class JobRegistry
{
public:
    static IJob* GetJob(int Type, int Success, string GetUniqueDescriptor);
};
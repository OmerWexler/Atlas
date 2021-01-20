#pragma once

#include <memory>

#include "IJob.h"

using namespace std;

class JobRegistry
{
public:
    static void JobRegistry::GetJob(int Type, shared_ptr<IJob>& OutJob);
};
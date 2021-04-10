#pragma once

#include <memory>

#include "IJob.h"

using namespace std;

class JobRegistry
{
public:
    static void JobRegistry::GetJob(const string Type, shared_ptr<IJob>& OutJob);
};
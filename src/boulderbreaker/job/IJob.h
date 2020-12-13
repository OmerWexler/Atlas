#pragma once

#include "Output.h"

class IJob
{
public:
    virtual string GetType() = 0;
    virtual Output Execute() = 0;
    virtual string GetUniqueDescriptor() = 0;
};
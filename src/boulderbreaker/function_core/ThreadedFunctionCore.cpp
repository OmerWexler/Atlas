#pragma once

#include "ThreadedFunctionCore.h"

void ThreadedFunctionCore::StartCore() const
{

}

bool ThreadedFunctionCore::IsRunning() const
{
    return true;
}

int ThreadedFunctionCore::StopCore() const
{
    return 0;
}

ThreadedFunctionCore::~ThreadedFunctionCore() 
{

}
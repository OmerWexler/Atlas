#pragma once

#include <vector>

#include "Argument.h"
#include "Cloneable.h"

using namespace std;

class IJob: public Cloneable<IJob*>
{
public: 
    virtual int GetType() const = 0;
    virtual void Execute(vector<Argument>& Input) = 0;
    virtual int Kill() = 0;
    virtual bool IsAlive() = 0;
    
    virtual int GetSuccess() const = 0;
    virtual void SetSuccess(int Success) = 0;

    virtual string GetUniqueDescriptor() const = 0;
    virtual void SetUniqueDescriptor(string UniqueDescriptor) = 0;
    virtual vector<Argument> GetOutput() const = 0;

    virtual ~IJob() {};
};

#define ATLS_CREATE_SHARED_JOB(type) shared_ptr<IJob>((IJob*) DBG_NEW type())
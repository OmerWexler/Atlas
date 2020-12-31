#pragma once

#include <vector>

#include "Argument.h"
#include "Cloneable.h"

using namespace std;

class IJob: public Cloneable<IJob*>
{
public: 
    virtual int GetType() const = 0;
    virtual vector<Argument> Execute(vector<Argument>& Input) = 0;
    virtual int GetSuccess() const = 0;
    virtual string GetUniqueDescriptor() const = 0;
    virtual void SetUniqueDescriptor(string UniqueDescriptor) = 0;
};
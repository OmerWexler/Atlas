#pragma once

#include "IMessage.h"
#include "Path.h"

using namespace std;

class CancelJobMessage: IMessage
{
private:
    string Descriptor = "";
    Path PathToTarget;

public:
    const static string TYPE;
    
    CancelJobMessage(const string Descriptor, string PathToTarget);
    string GetType() const;
    
    Path& GetPathToTarget();
    
    string GetDescriptor();
};
#pragma once

#include "IMessage.h"
#include "PCPerformance.h"
#include "Path.h"

using namespace std;

class SendNodePerformanceMessage: public IMessage
{
private:
    Path NodePath;
    struct PCPerformance& NodePerformance = PCPerformance();
    
public:
    const static string TYPE;
    
    SendNodePerformanceMessage(const PCPerformance& NodePerformance);
    SendNodePerformanceMessage(const PCPerformance& NodePerformance, Path Path);

    string GetType() const override;
    PCPerformance& GetNodePerformance();
    Path& GetPath();
};
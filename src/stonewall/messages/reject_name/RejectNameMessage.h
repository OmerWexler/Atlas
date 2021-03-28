#pragma once

#include "IMessage.h"

using namespace std;

class RejectNameMessage: IMessage
{
private:
    string Name;

public:
    const static string TYPE;

    RejectNameMessage(string Name);
    string GetType() const override;
    string GetInvalidName() const;
};
#pragma once

#include "IMessage.h"

using namespace std;

class AcceptNameMessage: IMessage
{
private:
    bool Accepted;
    string Name;

public:
    const static string TYPE;

    AcceptNameMessage(bool Accepted, string Name);
    string GetType() const override;
    bool IsAccepted() const;
    string GetInvalidName() const;
};
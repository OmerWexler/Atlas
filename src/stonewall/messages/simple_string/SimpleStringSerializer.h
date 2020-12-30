#pragma once

#include "IMessage.h"
#include "ISerializer.h"
#include "Logger.h"

#include <string>

using namespace std;

class SimpleStringSerializer: public ISerializer
{
public:
    string GetType() const override;
    string Serialize(const unique_ptr<IMessage>& Message) const override;
    ISerializer* Clone() override;
};
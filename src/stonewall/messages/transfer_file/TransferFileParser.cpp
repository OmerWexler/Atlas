#pragma once

#include "Utils.h"
#include "TransferFileParser.h"
#include "TransferFileMessage.h"
#include "SeperatorBasedMessage.h"

using namespace std;

TransferFileParser::TransferFileParser()
{
    SPBParser = SeperatorBasedParser();
}

string TransferFileParser::GetType() const
{
    return TransferFileMessage::TYPE;
}

void TransferFileParser::Parse(const string& SMsg, unique_ptr<IMessage>& Message)
{
    unique_ptr<IMessage> USPBMsg;
    SPBParser.Parse(SMsg.substr(HEADER.length()), USPBMsg);
    
    vector<string> Values = ((SeperatorBasedMessage*) USPBMsg.get())->GetValues();

    Message.reset((IMessage*) DBG_NEW TransferFileMessage(Values[0], Path(Values[1]), Values[2]));
}

bool TransferFileParser::CanParse(const string& SMsg) const
{
    return SMsg.substr(0, HEADER.length()) == HEADER &&
            SPBParser.CanParse(SMsg.substr(HEADER.length()));
}
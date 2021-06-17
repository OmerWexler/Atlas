#pragma once

#include "Utils.h"
#include "TransferFileBlockParser.h"
#include "TransferFileBlockMessage.h"
#include "SeperatorBasedMessage.h"

using namespace std;

TransferFileBlockParser::TransferFileBlockParser()
{
    SPBParser = SeperatorBasedParser();
}

string TransferFileBlockParser::GetType() const
{
    return TransferFileBlockMessage::TYPE;
}

void TransferFileBlockParser::Parse(const string& SMsg, unique_ptr<IMessage>& Message)
{
    unique_ptr<IMessage> USPBMsg;
    SPBParser.Parse(SMsg.substr(HEADER.length()), USPBMsg);
    
    vector<string> Values = ((SeperatorBasedMessage*) USPBMsg.get())->GetValues();

    Message.reset((IMessage*) DBG_NEW TransferFileBlockMessage(Values[0], Path(Values[1]), atoi(Values[2].c_str()), Values[3] == "1", Values[4]));
}

bool TransferFileBlockParser::CanParse(const string& SMsg) const
{
    return SMsg.substr(0, HEADER.length()) == HEADER &&
            SPBParser.CanParse(SMsg.substr(HEADER.length()));
}
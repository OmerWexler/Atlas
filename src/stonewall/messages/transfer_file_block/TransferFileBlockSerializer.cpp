#pragma once

#include "utils.h"
#include "TransferFileBlockSerializer.h"
#include "TransferFileBlockMessage.h"
#include "SeperatorBasedMessage.h"

using namespace std;

TransferFileBlockSerializer::TransferFileBlockSerializer()
{
    this->SPBSerializer = SeperatorBasedSerializer();
}

string TransferFileBlockSerializer::GetType() const
{
    return TransferFileBlockMessage::TYPE;
}

string TransferFileBlockSerializer::Serialize(const unique_ptr<IMessage>& Message) const
{
    TransferFileBlockMessage* TFBMsg = (TransferFileBlockMessage*) Message.get();

    SeperatorBasedMessage* SPBMsg = DBG_NEW SeperatorBasedMessage();
    SPBMsg->AddValue(TFBMsg->GetFilepath());
    SPBMsg->AddValue(TFBMsg->GetPathToTarget().GetStrPath());
    SPBMsg->AddValue(Utils::PadInt(TFBMsg->GetWriteIndex(), 6));
    SPBMsg->AddValue(TFBMsg->IsEnd() ? "1" : "0");
    SPBMsg->AddValue(TFBMsg->GetDataBlock());
    
    string SMsg = "" + HEADER;
    SMsg += SPBSerializer.Serialize(unique_ptr<IMessage>((IMessage*) SPBMsg));

    return SMsg;
}
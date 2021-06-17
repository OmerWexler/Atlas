#pragma once

#include "TransferFileMessage.h"

const string TransferFileMessage::TYPE = "TF";
const int TransferFileMessage::BLOCK_SIZE = 4096;

TransferFileMessage::TransferFileMessage(string Filepath, Path PathToTarget, string DataBlock)
{
    this->Filepath = Filepath;
    this->PathToTarget = PathToTarget;
    this->DataBlock = DataBlock;
}
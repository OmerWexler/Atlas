#pragma once

#include <memory>

#include "IMessage.h"
#include "Path.h"
#include <string>

using namespace std;

class TransferFileMessage: public IMessage
{
private:
    string Filepath;
    Path PathToTarget;
    string DataBlock;

public:
    const static string TYPE;
    const static int BLOCK_SIZE;
    
    TransferFileMessage(string Filepath, Path PathToTarget, string DataBlock);

    string GetType() const { return TYPE; }

    string GetFilepath() { return Filepath; };
    string GetDataBlock() { return DataBlock; };
    Path GetPathToTarget() { return PathToTarget; };
};
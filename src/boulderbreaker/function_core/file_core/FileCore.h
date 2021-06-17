#pragma once

#include "ASyncFunctionCore.h"
#include "File.h"

#define DEFAULT_POLL_FREQUENCY 0.02f
using namespace std;

struct FileBundle
{
    unordered_map<int, string> QueuedDataBlocks;
    int NextWriteIndex;
    File File;

    bool EndFound;
    int EndIndex;
};

class FileCore: public ASyncFunctionCore
{
private:
    unordered_map<string, FileBundle> LocalFiles;
    void TransferFileMessageFunc(unique_ptr<IMessage>& Message, GridConnection& Sender, bool IsExistingBlock);

protected:
    void HandleMessage(unique_ptr<IMessage>& Message, GridConnection& Sender);
    void Periodic();

public:
    FileCore(string Name, float PollFrequency): ASyncFunctionCore(Name, PollFrequency) {};
    FileCore(string Name): ASyncFunctionCore(Name, DEFAULT_POLL_FREQUENCY) {};

    string GetType() const;
    bool IsMessageRelated(const unique_ptr<IMessage>& Message) const;
    void StopCore() override;
    
    ~FileCore()=default;
};
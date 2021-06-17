#pragma once

#include <vector>
#include <unordered_map>

#include "Argument.h"
#include "Cloneable.h"
#include "Utils.h"
#include "Path.h"
#include "SmartThread.h"

using namespace std;

class IJob: public Cloneable<IJob*>
{
private:
    SmartThread ASyncThread;

protected:
    Path PathToTarget;
    int Success = 0;
    bool m_IsAlive = false;
    bool m_IsDone = false;
    vector<Argument> Output;
    string UniqueDescriptor;

public: 
    static size_t RANDOM_DESCRIPTOR_LENGTH;

    IJob() { UniqueDescriptor = Utils::GenerateRandomDescriptor(RANDOM_DESCRIPTOR_LENGTH); }

    virtual string GetType() const = 0;
    virtual void PrepareJobToSend(vector<Argument>& Input) {};
    virtual void Execute(vector<Argument>& Input) = 0;
    virtual bool IsInputValid(vector<Argument>& Input) = 0;
    virtual int Kill() = 0;

    virtual IJob* Clone() = 0;

    void StartASync(vector<Argument>& Input);

    void SetUniqueDescriptor(string UniqueDescriptor) { this->UniqueDescriptor = UniqueDescriptor; };
    virtual string GetUniqueDescriptor() { return UniqueDescriptor; };
    
    void SetSuccess(int Success) { this->Success = Success; };
    virtual int GetSuccess() { return Success; };
    
    void SetPathToTarget(Path PathToTarget) { this->PathToTarget = PathToTarget; };
    virtual Path& GetPathToTarget() { return PathToTarget; }
    
    void SetOutput(vector<Argument> Output) { this->Output = Output; };
    virtual vector<Argument> GetOutput() { return Output; };

    void SetIsAlive(bool IsAlive) { this->m_IsAlive = IsAlive; }
    virtual bool IsAlive() { return m_IsAlive; }
    
    void SetIsDone(bool IsDone) { this->m_IsDone = IsDone; }
    virtual bool IsDone() { return m_IsDone; }

    virtual ~IJob();
};

#define ATLS_CREATE_SHARED_JOB(type, ...) shared_ptr<IJob>((IJob*) DBG_NEW type(__VA_ARGS__))
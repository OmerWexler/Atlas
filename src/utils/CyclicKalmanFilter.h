#pragma once

#include <vector>

using namespace std;

class CyclicKalmanFilter
{
private:
    int Size;
    int Index;
    vector<int> Buffer;

public:
    CyclicKalmanFilter(int Size)
    {
        this->Size = Size;
        Index = 0;
    }

    void Feed(int Value)
    {
        if (Buffer.size() < Size)
        {
            Buffer.push_back(Value);
        }
        else 
        {
            Buffer[Index] = Value;
        }

        Index++;
        Index %= Size;
    }

    int GetValue()
    {
        int Average = 0;

        for (int Value: Buffer)
        {
            Average += Value / Size;
        }

        return Average;
    }
};
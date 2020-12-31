#pragma once

template<class T>
class Cloneable
{
public:
    virtual T Clone() = 0;
};
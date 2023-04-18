#pragma once
class INotifiable
{
public:
    virtual void Notify() = 0;
    virtual ~INotifiable() = default;
};
#pragma once
#include "INotifiable.h"
#include <atomic>

template<typename T>
class WatchedValue : public INotifiable
{
    T value;
public:
    WatchedValue() = default;
    WatchedValue(T initial_value, std::function<void(T)> onValueChangedFn)
    : value(initial_value), OnValueChanged(onValueChangedFn) {}
    virtual ~WatchedValue() = default;
    void Set(T new_value);
    T Get();
    std::function<void(T)> OnValueChanged;
    virtual void Notify() override;
};

template <typename T>
inline void WatchedValue<T>::Set(T new_value)
{
    if (new_value != value)
    {
        if (OnValueChanged != nullptr)
            OnValueChanged(new_value);
    }
    value = new_value;
}

template <typename T>
inline T WatchedValue<T>::Get()
{
    return value;
}

template <typename T>
inline void WatchedValue<T>::Notify()
{
    if (OnValueChanged != nullptr)
        OnValueChanged(value);
    else
        Serial.println("Warning: Value notified but no function assigned.");
}

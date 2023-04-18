#pragma once
#include <functional>
#include <thread>
#include "Task.h"

class AsyncTaskScheduler
{
    Task task;
public:
    void QueueAsyncTask(std::function<void()> task);
    void Join();
};



#pragma once
#include <functional>
#include <thread>


class AsyncTaskScheduler
{
    std::shared_ptr<std::thread> thread;
public:
    void QueueAsyncTask(std::function<void()> task);
    void Join();
    bool IsJoinable();
};



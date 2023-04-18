#include "AsyncTaskScheduler.h"

void AsyncTaskScheduler::QueueAsyncTask(std::function<void()> task)
{
    thread = std::make_shared<std::thread>(task);
}

void AsyncTaskScheduler::Join()
{
    thread->join();
}

bool AsyncTaskScheduler::IsJoinable()
{
    return thread->joinable();
}

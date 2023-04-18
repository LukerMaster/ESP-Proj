#include "AsyncTaskScheduler.h"

void AsyncTaskScheduler::QueueAsyncTask(std::function<void()> task)
{
    this->task.setFn(task);
    this->task.setPriority(0);
    this->task.start();
}

void AsyncTaskScheduler::Join()
{
    task.stop();
}
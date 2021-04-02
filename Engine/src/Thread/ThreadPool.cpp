#include "../include/Thread/ThreadPool.hpp"

#include <iostream>

using namespace Thread;

/* ==== Thread Interface ==== */

void ThreadInterface::Initialise(std::shared_ptr<TaskInterface> tsk)
{
    if (state == THREAD_STATE::running || state == THREAD_STATE::paused)
    {
        return;
    }

    task = std::move(tsk);
    state = THREAD_STATE::running;

    thread = std::make_unique<std::thread>(&ThreadInterface::Execute, this);
}


void ThreadInterface::Execute()
{
    if (state == THREAD_STATE::running)
    {
        if (task)
        {
            (*task).Execute();
        }

        if(threadPool->GetTask(this))
        {
            Execute();
        }
        else
        {
            state = THREAD_STATE::completed;
        }
    }
}

void ThreadInterface::Reset()
{
    state = THREAD_STATE::init;
}



/* ==== Thread Pool ==== */

ThreadPool::ThreadPool()
{
    for (unsigned int i = 0u; i < MAX_THREAD; i++)
    {
        threadList.push_back(std::make_unique<ThreadInterface>(this));
    }
}


bool ThreadPool::TaskAvailable()
{
    if (taskSystem->taskList.size() > 0)
    {
        return true;
    }
    return false;
}

bool ThreadPool::GetTask(ThreadInterface* thd)
{
    m.lock();

    if (taskSystem->taskList.size() > 0)
    {
        if (taskSystem->taskList.front())
        {

            thd->task = std::move(taskSystem->taskList.front());
            taskSystem->taskList.pop();

            m.unlock();
            return true;
        }
    }
    else
    {
        taskSystem->taskList.empty();
    }

    m.unlock();
    return false;
}


void ThreadPool::Run(TaskSystem* taskSys)
{
    bool init = true;

    taskSystem = taskSys;

    while (taskSys->taskList.size() > 0)
    {
        if (init)
        {
           for (int i = 0; i < threadList.size(); i++)
           {
                if (taskSys->taskList.empty())
                {
                    break;
                }

                threadList[i]->Initialise(taskSys->taskList.front());
                taskSys->taskList.pop();
           }
           init = false;
        }
    }
    for (int i = 0; i < threadList.size(); i++) // Join all thread to make sure they all finish
    {
        if (threadList[i]->state != THREAD_STATE::init)
        {
            threadList[i]->thread->join();
        }
    }
    for (int i = 0; i < threadList.size(); i++) // Reset all ThreadInterface
    {
        threadList[i]->Reset();
    }
}
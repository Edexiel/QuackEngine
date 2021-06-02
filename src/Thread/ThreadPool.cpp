#include "../include/Thread/ThreadPool.hpp"

#include <iostream>

using namespace Thread;

/* ==== Thread Interface ==== */

void ThreadInterface::Initialise(std::unique_ptr<TaskInterface>& tsk)
{
    if (_state == ThreadState::T_RUNNING || _state == ThreadState::T_PAUSED)
    {
        return;
    }

    _task = std::move(tsk);
    _state = ThreadState::T_RUNNING;

    _thread = std::make_unique<std::thread>(&ThreadInterface::Execute, this);
}


void ThreadInterface::Execute()
{
    if (_state == ThreadState::T_RUNNING)
    {
        if (_task)
        {
            (*_task).Execute();
        }

        if(_threadPool->GetTask(this))
        {
            Execute();
        }
        else
        {
            _state = ThreadState::T_COMPLETE;
        }
    }
}

void ThreadInterface::Reset()
{
    _state = ThreadState::T_INIT;
}



/* ==== Thread Pool ==== */

ThreadPool::ThreadPool()
{
    for (unsigned int i = 0u; i < maxThread; i++)
    {
        _threadList.push_back(std::make_unique<ThreadInterface>(this));
    }
}

bool ThreadPool::GetTask(ThreadInterface* thd)
{
    _mutex.lock();

    if (_taskSystem->_taskList.size() > 0)
    {
        if (_taskSystem->_taskList.front())
        {

            thd->_task = std::move(_taskSystem->_taskList.front());
            _taskSystem->_taskList.pop();

            _mutex.unlock();
            return true;
        }
    }
    else
    {
        _taskSystem->_taskList.empty();
    }

    _mutex.unlock();
    return false;
}


void ThreadPool::Run(TaskSystem* taskSys)
{
    bool init = true;

    _taskSystem = taskSys;

    while (taskSys->_taskList.size() > 0)
    {
        if (init)
        {
           for (int i = 0; i < _threadList.size(); i++)
           {
                if (taskSys->_taskList.empty())
                {
                    break;
                }

                _threadList[i]->Initialise(taskSys->_taskList.front());
                taskSys->_taskList.pop();
           }
           init = false;
        }
    }
    for (int i = 0; i < _threadList.size(); i++) // Join all thread to make sure they all finish when the function finish
    {
        if (_threadList[i]->_state != ThreadState::T_INIT)
        {
            _threadList[i]->_thread->join();
        }
    }
    for (int i = 0; i < _threadList.size(); i++) // Reset all ThreadInterface for a next usage
    {
        _threadList[i]->Reset();
    }
}
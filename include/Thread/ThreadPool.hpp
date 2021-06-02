#pragma once

#include "TaskSystem.hpp"
#include <thread>
#include <mutex>

#include <list>
#include <queue>
#include <atomic>

const unsigned int maxThread = std::thread::hardware_concurrency() - 1;

enum ThreadState
{
    T_INIT, T_PAUSED, T_RUNNING, T_COMPLETE
};

namespace Thread
{
    class ThreadInterface
    {
        public:
        ThreadState _state {ThreadState::T_INIT};

        class ThreadPool* _threadPool {nullptr};
        std::unique_ptr<TaskInterface> _task;
        std::unique_ptr<std::thread> _thread {nullptr};


        ThreadInterface(ThreadPool* threadPool) : _threadPool{threadPool}{};

        void Initialise(std::unique_ptr<TaskInterface>& tsk);

        void Execute();
        void Reset();
    };


    class ThreadPool
    {
    public:

        /* ==== Variable ==== */

        std::mutex _mutex;

        std::vector<std::unique_ptr<ThreadInterface>> _threadList;
        TaskSystem* _taskSystem;

        /* ==== Function ==== */
        ThreadPool();
        ~ThreadPool (){};

        void Run(TaskSystem* taskSys);
        bool GetTask(ThreadInterface* thd);
    };
}


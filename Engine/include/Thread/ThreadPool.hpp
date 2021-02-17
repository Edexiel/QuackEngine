#pragma once

#include "TaskSystem.hpp"
#include <thread>
#include <mutex>

#include <list>
#include <queue>
#include <atomic>

#define MAX_THREAD std::thread::hardware_concurrency() - 1


enum THREAD_STATE
{
    init, paused, running, completed
};

namespace Thread
{
    class ThreadInterface
    {
        public:
        THREAD_STATE state {THREAD_STATE::init};

        class ThreadPool* threadPool;
        std::shared_ptr<TaskInterface> task;
        std::unique_ptr<std::thread> thread {nullptr};


        ThreadInterface(ThreadPool* _threadPool) : threadPool{_threadPool}{};

        void Initialise(std::shared_ptr<TaskInterface> tsk);

        void Execute();
        void Reset();
    };


    class ThreadPool
    {
    public:

        /* ==== Variable ==== */

        std::mutex m;

        std::vector<std::unique_ptr<ThreadInterface>> threadList;

        TaskSystem* taskSystem;

        /* ==== Function ==== */
        ThreadPool();
        ~ThreadPool (){};

        void Run(TaskSystem* taskSys);

        void Play();
        void Add(TaskSystem& taskSys);

        bool TaskAvailable();
        bool GetTask(ThreadInterface* thd);
    };
}


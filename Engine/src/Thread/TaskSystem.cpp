#include "../include/Thread/TaskSystem.hpp"

using namespace Thread;

void LongTask::Execute()
{
    for (int i = 0; i < taskList.size(); i++)
    {
        taskList[i]->Execute();
    }
    taskList.clear();
}

void LongTask::AddTask(std::shared_ptr<TaskInterface> tsk)
{
    taskList.push_back(tsk);
}

/* ==== TaskSystem ===== */

void TaskSystem::AddTask(std::shared_ptr<TaskInterface> tsk)
{
    taskList.push(tsk);
};
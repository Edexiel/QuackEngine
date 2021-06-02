#include "../include/Thread/TaskSystem.hpp"

using namespace Thread;

/* ==== TaskSystem ===== */

void TaskSystem::AddTask(TaskInterface* tsk)
{
    _taskList.emplace(tsk);
};
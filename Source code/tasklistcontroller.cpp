#include "tasklistcontroller.h"

TaskListController::TaskListController(TaskList *taskList, QObject *parent) :
    QObject(parent),
    m_taskList( taskList )
{
    Q_ASSERT(taskList != nullptr);
}

SingleTask *TaskListController::createTask()
{
    auto result = m_taskList->createTask();
    if(result != nullptr){
        result->setName(tr("Edit your task"));

    }
    return result;
}

bool TaskListController::deleteTask(SingleTask *task)
{
    return m_taskList->deleteTask( task );
}

int TaskListController::countDoneTasks(SingleTask *task)
{
    return m_taskList->countDoneTasks( task );
}
int TaskListController::countDoneTasksDeleted(SingleTask *task)
{
    return m_taskList->countDoneTasksDeleted(task);
}

int TaskListController::countTasks()
{
    return m_taskList->countTasks();
}

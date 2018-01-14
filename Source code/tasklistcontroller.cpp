#include "tasklistcontroller.h"

TaskListController::TaskListController(TaskList *taskList, dbManager *db, QObject *parent) :
    QObject(parent),
    m_taskList( taskList ),
    m_db(db)
{
    Q_ASSERT(taskList != nullptr);
    Q_ASSERT(db != nullptr);
}
//bool dbManager::loadTasks()
//{
//    bool success = false;
//    QSqlQuery loadQuery;
//    loadQuery.prepare("SELECT * FROM tasks");
//    if (loadQuery.exec())
//    {
//        success = true;
//    }
//    else
//    {
//        qDebug() << "load all tasks failed: " << loadQuery.lastError();
//    }

//    return success;
//}
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

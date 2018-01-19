#ifndef TASKLISTCONTROLLER_H
#define TASKLISTCONTROLLER_H
#include "tasklist.h"
#include "dbmanager.h"


#include <QObject>

class TaskListController : public QObject
{
    Q_OBJECT
public:
    explicit TaskListController(TaskList *taskList, QObject *parent = 0);

    SingleTask *createTask();
    bool deleteTask(SingleTask *task);
    int countDoneTasks(SingleTask *task);
    int countDoneTasksDeleted(SingleTask *task);
    int countTasks();


signals:

public slots:


private:
    TaskList *m_taskList;
};

#endif // TASKLISTCONTROLLER_H

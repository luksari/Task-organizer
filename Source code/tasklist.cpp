#include "tasklist.h"


TaskList::TaskList(QObject *parent) : QObject(parent)
{

}

TaskList::Tasks TaskList::tasks() const
{
  return m_tasks;

}

SingleTask *TaskList::createTask()
{
    auto result = new SingleTask( this );
    if(result != nullptr){

        m_tasks.append( result );
        emit taskAdded( result );
    }
    return result;

}

bool TaskList::deleteTask(SingleTask *task)
{
    if(m_tasks.contains( task )){
        emit taskRemoved( task );
        m_tasks.removeOne( task );
        delete task;
        return true;

    }
    return false;
}


int TaskList::countTasks()
{
    int counter=tasks().count();
    return counter;

}


int TaskList::countDoneTasks(SingleTask *task)
{
    if(m_tasks.contains( task )){
        int counter=taskDoneCounter();
        if((task->isDone()) == true && task->changed()==true){
            counter++;
        }
       else if((task->isDone()) == false && task->changed()==true){
            counter--;
        }
        setTaskDoneCounter(counter);
    }

    return taskDoneCounter();

}
int TaskList::countDoneTasksDeleted(SingleTask *task)
{

    setTaskDoneCounter((countDoneTasks(task))-1);
    return taskDoneCounter();

}

int TaskList::taskDoneCounter() const
{
    return m_taskDoneCounter;
}

void TaskList::setTaskDoneCounter(int taskDoneCounter)
{
    if(m_taskDoneCounter != taskDoneCounter){

        m_taskDoneCounter = taskDoneCounter;
        emit taskDoneCounterChanged();
    }
}

#ifndef TASKLIST_H
#define TASKLIST_H

#include "singletask.h"
#include "dbmanager.h"

#include <QObject>
#include <QList>

class TaskList : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int taskDoneCounter READ taskDoneCounter WRITE setTaskDoneCounter NOTIFY taskDoneCounterChanged)
public:
    typedef QList<SingleTask*> Tasks; //Definiowanie typu Tasks w celu skrócenia zapisu

    explicit TaskList(QObject *parent = 0);

    Tasks tasks() const; //Metoda getter

    SingleTask *createTask(); //Tworzenie zadania
    bool deleteTask( SingleTask *task); //Usuwanie zadania

    int countTasks();
    int countDoneTasks(SingleTask *task);
    int countDoneTasksDeleted(SingleTask *task);

    int taskDoneCounter() const;
    void setTaskDoneCounter(int taskDoneCounter);

signals:

    void taskAdded( SingleTask *task); //Sygnał oczekujący na dodanie zadania
    void taskRemoved( SingleTask *task); //Sygnał oczekujący na usunięcie zadania
    void taskDoneCounterChanged();

public slots:

private:

    Tasks m_tasks; //Prywatny obiekt typu Tasks
    int m_taskDoneCounter = 0;




};

#endif // TASKLIST_H

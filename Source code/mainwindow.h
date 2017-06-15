#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tasklistcontroller.h"

#include <QMainWindow>
#include <QHash>
#include <QColor>
#include <QPushButton>
#include <QWidget>

namespace Ui {
class MainWindow;
}

class QListWidgetItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(TaskListController *controller, QWidget *parent = 0);
    ~MainWindow();

public slots:
    void createTask();
    void deleteTask();
    void editTask();
    void saveTask();
    void discardTask();
    void resetTask();
    void countDoneTasks();
    void countDoneTasksDeleted();
    void countTasks();

private:
    Ui::MainWindow *ui;
    TaskListController *m_controller;
    QHash<QListWidgetItem*, SingleTask*> m_taskMap;
    void setupConnections();

};

#endif // MAINWINDOW_H

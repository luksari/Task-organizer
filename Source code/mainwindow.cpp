#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(TaskListController *controller, dbManager *db, QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_controller(controller),
    m_db(db)
{
    Q_ASSERT(controller != nullptr);
    Q_ASSERT(db != nullptr);
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->listPage);
    setupConnections();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createTask()
{
    auto task = m_controller->createTask();
    if(task){
        ui->listWidget->addItem(task->name());
        auto listItem = ui->listWidget->item(ui->listWidget->count() - 1);
        m_taskMap.insert(listItem, task);
    }
}

void MainWindow::deleteTask()
{
    auto listItem = ui->listWidget->currentItem();
    if(listItem){
        auto task = m_taskMap.value(listItem);
        if(task){
            if(m_controller->deleteTask( task ) ){
                if(task->isDone()==true)
                {
                    countDoneTasksDeleted();

                }
                m_db->removeTask(task->id());
                m_taskMap.remove(listItem);
                delete listItem;
            }
        }
    }
}

void MainWindow::editTask()
{
    auto listItem = ui->listWidget->currentItem();
    if(listItem){
        auto task = m_taskMap.value(listItem);
        if(task){
           ui->stackedWidget->setCurrentWidget(ui->formPage);
           ui->menuTasks->setEnabled(false);
           resetTask();
        }
    }
}

void MainWindow::saveTask()
{
    auto listItem = ui->listWidget->currentItem();
    if(listItem){
        auto task = m_taskMap.value(listItem);

        if(task){
           auto name = ui->titleEdit->text();
           auto deadline = ui->deadlineEdit->date();
           auto description = ui->descriptionEdit->toPlainText();
           auto isDone = ui->isDoneEdit->isChecked();
           auto id = ui->listWidget->currentRow();
           task->setName(name);
           task->setDeadline(deadline);
           task->setDescription(description);
           task->setIsDone(isDone);
           task->setId(id);
           listItem->setText(name);

           /*DB SEGMENT*/
           m_db->addTask(id, name, description, deadline, isDone);
           m_db->printAllTasks();

           if((task->isDone())==true)
           {
               listItem->setBackgroundColor(QColor::fromRgb(88, 226, 178));
           }
           else
           {
               listItem->setBackgroundColor(Qt::transparent);
           }
           discardTask();
        }
    }
}

void MainWindow::discardTask()
{
    ui->stackedWidget->setCurrentWidget(ui->listPage);
    ui->menuTasks->setEnabled(true);
}

void MainWindow::resetTask()
{
    auto listItem = ui->listWidget->currentItem();
    if(listItem){
        auto task = m_taskMap.value(listItem);
        if(task){
           ui->stackedWidget->setCurrentWidget(ui->formPage);
           ui->menuTasks->setEnabled(false);
           ui->titleEdit->setText(task->name());
           ui->deadlineEdit->setDate(task->deadline());
           ui->descriptionEdit->setPlainText(task->description());
           ui->isDoneEdit->setChecked(task->isDone());

        }
    }
}

void MainWindow::countDoneTasks()
{
    auto listItem = ui->listWidget->currentItem();
    if(listItem){
        auto task = m_taskMap.value(listItem);
        if(task){

                ui->progressBar->setValue(m_controller->countDoneTasks(task));

        }
    }
}
void MainWindow::countDoneTasksDeleted()
{
    auto listItem = ui->listWidget->currentItem();
    if(listItem){
        auto task = m_taskMap.value(listItem);
        if(task){

                ui->progressBar->setValue(m_controller->countDoneTasksDeleted(task));

        }
    }
}
void MainWindow::countTasks()
{
    auto listItem = ui->listWidget->currentItem();
    if(listItem){
        auto task = m_taskMap.value(listItem);
        if(task){

                ui->progressBar->setMaximum(m_controller->countTasks());
              }
         }
}

void MainWindow::setupConnections()
{
    connect(ui->actionAdd, &QAction::triggered, this, &MainWindow::createTask);
    connect(ui->actionRemove, &QAction::triggered, this, &MainWindow::deleteTask);
    connect(ui->actionEdit, &QAction::triggered, this, &MainWindow::editTask);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::saveTask);
    connect(ui->discardButton, &QPushButton::clicked, this, &MainWindow::discardTask);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::resetTask);
    connect(ui->listWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::editTask);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::countDoneTasks);
    connect(ui->actionAdd, &QAction::triggered, this, &MainWindow::countTasks);
    connect(ui->actionRemove, &QAction::triggered, this, &MainWindow::countTasks);

}

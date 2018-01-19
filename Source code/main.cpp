#include "mainwindow.h"
#include <QApplication>
#include "dbmanager.h"

static const QString path = "tasks.db";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dbManager db(path);
    db.createTable();
    TaskList taskList;
    TaskListController controller(&taskList);
    MainWindow w(&controller, &db);
    w.show();


    return a.exec();
}

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TaskList taskList;
    TaskListController controller( &taskList);
    MainWindow w(&controller);
    w.show();
    a.setWindowIcon(QIcon("./images/Logo.png"));

    return a.exec();
}

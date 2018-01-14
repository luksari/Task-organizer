#include "dbmanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

dbManager::dbManager(const QString &path)
{
      m_db = QSqlDatabase::addDatabase("QSQLITE");
      m_db.setDatabaseName(path);

      if (!m_db.open())
      {
          qDebug() << "Error: connection with database fail";
      }
      else
      {
          qDebug() << "Database: connection ok";
  }
}
dbManager::~dbManager()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }
}
bool dbManager::isOpen() const
{
    return m_db.isOpen();
}
bool dbManager::createTable()
{
    bool success = false;

    QSqlQuery query;
    query.prepare("CREATE TABLE tasks(id INTEGER, name TEXT, description TEXT, deadline INTEGER, isdone INTEGER);");

    if (!query.exec())
    {
       qDebug() << "Couldn't create the table 'tasks': one might already exist." << query.lastError();
       success = false;
    }


    return success;
}

bool dbManager::addTask(const int id, const QString name, const QString description, const QDate deadline, const bool isdone)
{
    bool success = false;

    if (!name.isNull() && !description.isNull() && !deadline.isNull())
    {
        QSqlQuery queryAdd;
        queryAdd.prepare("INSERT INTO tasks(id,name,description,deadline,isdone) VALUES (:id, :name, :description, :deadline, :isdone)");
        queryAdd.bindValue(":id", id);
        queryAdd.bindValue(":name", name);
        queryAdd.bindValue(":description", description);
        queryAdd.bindValue(":deadline", deadline);
        queryAdd.bindValue(":isdone", isdone);


        if(queryAdd.exec())
        {
            success = true;
        }
        else
        {
            qDebug() << "add task failed: " << queryAdd.lastError();
        }
    }
    else
    {
        qDebug() << "add task failed: args cannot be empty";
    }

    return success;
}

bool dbManager::removeTask(const int id)
{
    bool success = false;

    if (taskExists(id))
    {
        QSqlQuery queryDelete;
        queryDelete.prepare("DELETE FROM tasks WHERE id = (:id)");
        queryDelete.bindValue(":id", id);
        success = queryDelete.exec();

        if(!success)
        {
            qDebug() << "remove task failed: " << queryDelete.lastError();
        }
    }
    else
    {
        qDebug() << "remove task failed: task doesnt exist";
    }

    return success;
}

void dbManager::printAllTasks() const
{
    qDebug() << "Tasks in db:";
    QSqlQuery query("SELECT * FROM tasks");
    int idName = query.record().indexOf("name");
    int idDescription = query.record().indexOf("description");
    int idID = query.record().indexOf("id");
    while (query.next())
    {
        QString name = query.value(idName).toString();
        QString description = query.value(idDescription).toString();
        QString ID = query.value(idID).toString();
        qDebug() << "===" << name << "===" << description << ID;
    }
}
bool dbManager::taskExists(const int &id) const
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT id FROM tasks WHERE id = (:id)");
    checkQuery.bindValue(":id", id);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            exists = true;
        }
    }
    else
    {
        qDebug() << "task exists failed: " << checkQuery.lastError();
    }

    return exists;
}

bool dbManager::removeAllTasks()
{
    bool success = false;

    QSqlQuery removeQuery;
    removeQuery.prepare("DELETE FROM tasks");

    if (removeQuery.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "remove all tasks failed: " << removeQuery.lastError();
    }

    return success;
}
//int dbManager::getId(const QString &name){


//    QSqlQuery getQuery;
//    getQuery.prepare("SELECT id FROM tasks WHERE name = (:name)");
//    getQuery.bindValue(":name", name);
//    if (getQuery.exec())
//    {
//        int idID = getQuery.record().indexOf("id");
//        int newId = getQuery.value(idID).toInt();
//        return newId;
//    }
//    else
//    {
//        qDebug() << "get id of task failed: " << getQuery.lastError();
//    }
//    return -1;

//}


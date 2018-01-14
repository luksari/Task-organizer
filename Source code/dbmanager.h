#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QDate>
#include <QSqlQueryModel>


class dbManager
{
public:
    /**
     * @brief Constructor
     *
     * Constructor sets up connection with db and opens it
     * @param path - absolute path to db file
     */
    dbManager(const QString& path);

    /**
     * @brief Destructor
     *
     * Close the db connection
     */
    ~dbManager();

    bool isOpen() const;

    /**
     * @brief Creates a new 'tasks' table if it doesn't already exist
     * @return true - 'people' table created successfully, false - table not created
     */
    bool createTable();

    /**
     * @brief Add Task data to db
     * @param name - name of Task to add
     * @return true - Task added successfully, false - Task not added
     */
    bool addTask(const int id, const QString name, const QString description, const QDate deadline, const bool isdone);

    /**
     * @brief Remove Task data from db
     * @param name - name of Task to remove.
     * @return true - Task removed successfully, false - Task not removed
     */
    bool removeTask(const int id);

    /**
     * @brief Check if Task of name "name" exists in db
     * @param name - name of Task to check.
     * @return true - Task exists, false - Task does not exist
     */
    bool taskExists(const int& id) const;

    /**
     * @brief Print names of all Tasks in db
     */
    void printAllTasks() const;

    /**
     * @brief Remove all Tasks from db
     * @return true - all Tasks removed successfully, false - not removed
     */
    bool removeAllTasks();


    int getId(const QString &name);
private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H

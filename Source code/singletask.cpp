 #include "singletask.h"

SingleTask::SingleTask(QObject *parent) : QObject(parent)
{

}

QString SingleTask::name() const
{
    return m_name;
}

void SingleTask::setName(const QString &name)
{
    if(m_name != name)
    {
        m_name = name;
        emit nameChanged();
    }

}

QString SingleTask::description() const
{
    return m_description;
}

void SingleTask::setDescription(const QString &description)
{
    if(m_description != description){
        m_description = description;
        emit descriptionChanged();
    }
}

QDate SingleTask::deadline() const
{
    return m_deadline;
}

void SingleTask::setDeadline(const QDate &deadline)
{
    if(m_deadline != deadline){
        m_deadline = deadline;
        emit deadlineChanged();

    }
}

bool SingleTask::isDone() const
{
    return m_isDone;
}

void SingleTask::setIsDone(bool isDone)
{
    if(m_isDone != isDone){
        m_isDone = isDone;

            setChanged(true);
            emit isDoneChanged();
        }
      else
    {
       setChanged(false);
    }

}

bool SingleTask::changed() const
{
    return m_changed;
}

void SingleTask::setChanged(bool changed)
{
    m_changed = changed;
}

int SingleTask::id() const
{
    return m_id;
}

void SingleTask::setId(int id)
{
    if(m_id != id){
        m_id = id;
        emit idChanged();
    }
}

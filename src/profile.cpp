#include "profile.h"

Profile::Profile()
{}

Profile::Profile(QString &name, QString &description, QString &id) : m_name(name),
    m_description(description),
    m_id(id)
{

}
Profile::Profile(QString &name, QString &description, QString &id, QList<QString> &appList) : m_name(name),
    m_description(description),
    m_id(id),
    m_apps(appList)
{

}

QString Profile::name() const
{
    return m_name;
}

void Profile::setName(const QString &Name)
{
    m_name = Name;
}

QString Profile::description() const
{
    return m_description;
}

void Profile::setDescription(const QString &Description)
{
    if(Description.isEmpty())
    {
        m_description = "* Nothing *";
    } else
    {
        m_description = Description;
    }

}

QString Profile::id() const
{
    return m_id;
}

void Profile::setId(const QString &Id)
{
    m_id = Id;
}

QList<QString> Profile::apps() const
{

    return m_apps;
}

void Profile::setApps(const QList<QString> &appList)
{
    m_apps = appList;
}

#ifndef PROFILE_H
#define PROFILE_H

#include <QObject>

#include "app.h"

class Profile
{
public:
    Profile();
    Profile(QString &name, QString &description, QString &id);
    Profile(QString &name, QString &description, QString &id, QList<QString> &appList);

    QString name() const;
    void setName(const QString &name);
    QString description() const;
    void setDescription(const QString &description);
    QString id() const;
    void setId(const QString &id);

    QList<QString> apps() const;
    void setApps(const QList<QString> &appList);

private:
    QString m_name;
    QString m_description;
    QString m_id;
    QList<QString> m_apps;

};
#endif // PROFILE_H

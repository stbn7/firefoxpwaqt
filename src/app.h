#ifndef APP_H
#define APP_H

#include <QObject>

class App
{
public:
    App();
    App(QString &iconName, QString &name, QString &manifest, QString &id, QString &description, QString &profile);

    QString name() const;
    void setName(const QString &name);

    QString address() const;
    void setAddress(const QString &address);

    QString categories() const;
    void setCategories(const QString &categories);

    QString description() const;
    void setDescription(const QString &description);

    QString id() const;
    void setId(const QString &id);

    QString icon();
    void setIcon(QString &iconName);

    QString profile() const;
    void setProfile(const QString &manifest);

    QString manifest() const;
    void setManifest(const QString &manifest);

private:
    QString m_name;
    QString m_address;
    QString m_categories;
    QString m_description;
    QString m_keywords;
    QString m_id;
    QString m_profile;
    QString m_iconName;
    QString m_manifest;
};

#endif // APP_H

#ifndef FIREFOXPWA_H
#define FIREFOXPWA_H

#include <QObject>
#include <QProcess>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include "QJsonParseError"
#include <QFile>
#include <QDir>

#include "profile.h"
#include "app.h"
#include "utils.h"

class Firefoxpwa
{
public:
    Firefoxpwa();
    QString createApp(QString manifest, QString idProfile);
    void removeApp(QString idApp);
    QString searchAppID(QString name);
    App *searchAppForID(QString id);
    QList<App*> searchApp(QString name) const;
    void lauchApp(QString idApp);

    QString createProfile(QString name, QString description);
    void removeProfile(QString idProfile);

    QList<QString> listAppId();
    QString searchProfileID(QString name);
    QStringList listProfileNames();
    QList<Profile*> listProfile();

    QList<App*> listApps() const;
    static void editApp(App app, QString iconPath);
};

#endif // FIREFOXPWA_H

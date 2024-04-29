#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QDir>
#include <QFile>


#include "app.h"
#include "firefoxpwa.h"


class Utils
{
public:
    Utils();
    static QList<App*> loadAppList();
    static void createShortcut(App *app);
    static QList<QString> AppData();
    static void createIcon(QString idApp, QString iconPath);
    static void updateDescription(QString description, QString newDescription);

    static void createIcon(App app, QString rootPath);
    static void removeFolder();

private:
    QList<App*> m_appList;

};

#endif // UTILS_H

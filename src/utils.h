#ifndef UTILS_H
#define UTILS_H

#include <QDir>
#include <QFile>
#include <QDirIterator>
#include <QObject>
#include <QStandardPaths>
#include <QTextStream>


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

    static void updateIcons();
    static void createIconFile(QString app);
    static QString searchIcons(QString idApp);
    static void removeIconFile();

    static QString darkMode();
    static QString lightMode();

    static bool copyResources();

private:
    QList<App*> m_appList;

};

#endif // UTILS_H

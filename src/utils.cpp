#include "utils.h"

#include "QDebug"

#include "profile.h"
#include "qicon.h"

Utils::Utils()
{

}

void Utils::createShortcut(App *app)
{
    QFile file;
    QByteArray name = app->name().toUtf8();


    QByteArray comment = app->description().toUtf8();
    QByteArray pathIcon = app->icon().toUtf8();
    QByteArray idApp = app->id().toUtf8();

    QByteArray content = "[Desktop Entry]\n"
                         "Type=Application\n"
                         "Version=0.01\n"
                         "Name=" + name + "\n"
                                  "Comment=" + comment + "\n"
                                     "Keywords=;\n"
                                     "Categories=GTK;WebApps;;\n"
                                     "Icon=" + pathIcon + "\n"
                                      "Exec=/usr/bin/firefoxpwa site launch " + idApp + " --protocol %u\n"
                                   "Actions=\n"
                                   "MimeType=\n"
                                   "Terminal=false\n"
                                   "StartupNotify=true\n";
    //"StartupWMClass=" + name;

    file.setFileName(QDir::homePath() + "/.local/share/applications/" + "FFPWA-" + idApp + ".desktop");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(content);
    file.flush();
    file.close();
}

QList<QString> Utils::AppData()
{

    QList<QString> p;

    return p;


}

void Utils::createIcon(QString idApp, QString iconPath)
{
    QString path = QDir::homePath() + "/.local/share/icons/";
    path = path.append(QIcon::themeName()) + "/apps/scalable/";
    path = path + "FFPWA-" + idApp + ".svg";

    QString sourcePath = iconPath;
    QDir dirSource(path);
    QDir dirFile(sourcePath);
    QFile file (path);

    if(!dirSource.absoluteFilePath(path).isEmpty())
    {
        file.remove();
    }

    bool status = QFile::copy(sourcePath, path);

}

//Create apps refrescar lista
// void newappdialog::deleteShortcut(app *app)
// {
//     QString nameShortcut = "FFPWA-" + app->id() + ".desktop";
//     QDir dirApplication = QDir(QDir::homePath() + "/.local/share/applications/");
//     dirApplication.remove(nameShortcut);

// }
































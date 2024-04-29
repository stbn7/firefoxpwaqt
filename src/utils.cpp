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

void Utils::createIcon(App app, QString iconPath)
{
    QString scalablePath = QDir::homePath() + "/.local/share/icons/hicolor/scalable/apps/FFPWA-" + app.id() + ".svg";
    QDir dirSource(iconPath);
    QFile file (scalablePath);
    QDir dirDest(scalablePath);

    if(!dirDest.absoluteFilePath(scalablePath).isEmpty())
    {
        file.remove();
    }

    //QFile::copy(source,dest);
    bool status = QFile::copy(iconPath,scalablePath);
    Utils::removeFolder();

}

void Utils::removeFolder()
{
    QDir hicolorX16 = QDir::homePath() + "/.local/share/icons/hicolor/16x16/";
    QDir hicolorX24 = QDir::homePath() + "/.local/share/icons/hicolor/24x24/";
    QDir hicolorX32 = QDir::homePath() + "/.local/share/icons/hicolor/32x32/";
    QDir hicolorX48 = QDir::homePath() + "/.local/share/icons/hicolor/48x48/";
    QDir hicolorX60 = QDir::homePath() + "/.local/share/icons/hicolor/60x60/";
    QDir hicolorX64 = QDir::homePath() + "/.local/share/icons/hicolor/64x64/";
    QDir hicolorX90 = QDir::homePath() + "/.local/share/icons/hicolor/90x90/";
    QDir hicolorX128 = QDir::homePath() + "/.local/share/icons/hicolor/128x128/";
    QDir hicolorX144 = QDir::homePath() + "/.local/share/icons/hicolor/144x144/";
    QDir hicolorX180 = QDir::homePath() + "/.local/share/icons/hicolor/180x180/";
    QDir hicolorX192 = QDir::homePath() + "/.local/share/icons/hicolor/192x192/";
    QDir hicolorX256 = QDir::homePath() + "/.local/share/icons/hicolor/256x256/";
    QDir hicolorX512 = QDir::homePath() + "/.local/share/icons/hicolor/512x512/";

    hicolorX16.removeRecursively();
    hicolorX24.removeRecursively();
    hicolorX32.removeRecursively();
    hicolorX48.removeRecursively();
    hicolorX60.removeRecursively();
    hicolorX64.removeRecursively();
    hicolorX90.removeRecursively();
    hicolorX128.removeRecursively();
    hicolorX144.removeRecursively();
    hicolorX180.removeRecursively();
    hicolorX192.removeRecursively();
    hicolorX256.removeRecursively();
    hicolorX512.removeRecursively();
}



//Create apps refrescar lista
// void newappdialog::deleteShortcut(app *app)
// {
//     QString nameShortcut = "FFPWA-" + app->id() + ".desktop";
//     QDir dirApplication = QDir(QDir::homePath() + "/.local/share/applications/");
//     dirApplication.remove(nameShortcut);

// }
































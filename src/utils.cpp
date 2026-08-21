#include "utils.h"

#include "QDebug"

#include <qapplication.h>

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
                         "Version=1.4\n"
                         "Name=" + name + "\n"
                                  "Comment=" + comment + "\n"
                                     "Keywords=;\n"
                                     "Categories=GTK;WebApps;;\n"
                                     "Icon=" + pathIcon + "\n"
                                      "Exec=/usr/bin/firefoxpwa site launch " + idApp + " --protocol %u\n"
                                   "Actions=None\n"
                                   "MimeType=\n"
                                   "Terminal=false\n"
                                   "StartupNotify=true\n";
    //"StartupWMClass=" + name;

    file.setFileName(QDir::homePath() + "/.local/share/applications/" + "FFPWA-" + idApp + ".desktop");

    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        file.write(content);
        file.flush();
        file.close();
    }else
    {
        qWarning() << "No se pudo abrir el archivo para escritura:" << file.fileName();
    }

}

QList<QString> Utils::AppData()
{

    QList<QString> p;

    return p;


}

QString Utils::darkMode()
{
    qDebug() << "Activated mode dark";


        QString style = R"(
            QListWidget {
                border: none;
                outline: none;
                border-radius: 10px;
            }
            QListWidget::item {
                border-radius: 5px;
            }

            QListWidget::item:selected {
                background-color: #cccccc;
                border: none;
            }

            QListWidget::item:hover {
                background-color: #f0f0f0;
            }

            QListWidget::item:selected:hover {
                background-color: #cccccc;
            }
        )";



    return style;
}

QString Utils::lightMode()
{
    qDebug() << "Activated mode light";


    QString style = R"(
            QListWidget {
                border: none;
                outline: none;
                border-radius: 10px;
            }
            QListWidget::item {
                border-radius: 5px;
            }

            QListWidget::item:selected {
                background-color: #cccccc;
                border: none;
            }

            QListWidget::item:hover {
                background-color: #f0f0f0;
            }

            QListWidget::item:selected:hover {
                background-color: #cccccc;
            }
        )";



    return style;
}

void Utils::updateIcons()
{
    Firefoxpwa firefoxpwa;
    QList<QString> idApps;

    QList<App*> listApps;
    listApps = firefoxpwa.listApps();


    for(int i=0; i<listApps.size(); i++)
    {
        App *app = listApps.at(i);

        QString dirApplication = QDir::homePath() + "/.local/share/applications/FFPWA-" + app->id() + ".desktop";
        QFile file(dirApplication);


        if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
            qWarning() << "No se pudo abrir el archivo A:" << dirApplication;
            //return QString();
        }else

        {
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                if (line.contains("Icon=")) {
                    Utils::createIconFile(app->id() + ";" + line);
                    file.close();
                }
            }
        }
        file.close();

    }
}

void Utils::createIconFile(QString app)
{
    QString dirIconPath = QDir::homePath() + "/.config/firefoxpwaqt";

    QFile file(dirIconPath);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
            app.remove("Icon=");
            out << app<< Qt::endl;
        }
        file.close();
}

QString Utils::searchIcons(QString idApp)
{
    QString dirIconPath = QDir::homePath() + "/.config/firefoxpwaqt";
    QFile file(dirIconPath);

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qWarning() << "Error: No se pudo abrir el archivo en BBB" << dirIconPath;
        return QString();
    }

    QTextStream stream(&file);

    while (!stream.atEnd()) {
        QString linea = stream.readLine();

        if (linea.contains(idApp, Qt::CaseInsensitive)) {
            file.close();
            return linea;
            qDebug() << linea;
        }
    }

    file.close();
    return QString();
}

void Utils::removeIconFile()
{
    QString dirIconPath = QDir::homePath() + "/.config/firefoxpwaqt";
    QFile::remove(dirIconPath);
}

bool Utils::copyResources()
{

    QString desDir = QStandardPaths::writableLocation(
                             QStandardPaths::HomeLocation) + "/.local/share/firefoxpwaqt/";

    QDir().mkpath(desDir);

    QDirIterator it(":/icons", QDirIterator::Subdirectories);

    while (it.hasNext()) {
        it.next();

        if (it.fileInfo().isFile()) {
            QString relativePath = it.filePath().mid(2);

            // Ruta de destino completa
            QString destinationPath = desDir + "/" + relativePath;

            // Crea los subdirectorios necesarios
            QFileInfo infoDestino(destinationPath);
            QDir().mkpath(infoDestino.absolutePath());

            // Copia el archivo
            if (!QFile::copy(it.filePath(), destinationPath)) {
                qWarning() << "Copy Failed:" << it.filePath()
                << "a" << destinationPath;
                return false;
            } else {
                qDebug() << "Copied:" << relativePath;
            }
        }
    }


    QDirIterator permIterator(desDir + "/icons", QDirIterator::Subdirectories);
    while (permIterator.hasNext()) {
        permIterator.next();
        QString ruta = permIterator.filePath();
        if (ruta != "." && ruta != "..") {
            QFile::setPermissions(ruta,
                                  QFileDevice::ReadUser   | QFileDevice::WriteUser   | QFileDevice::ExeUser |
                                      QFileDevice::ReadGroup  | QFileDevice::WriteGroup  | QFileDevice::ExeGroup |
                                      QFileDevice::ReadOther  | QFileDevice::WriteOther  | QFileDevice::ExeOther);
        }
    }



    return true;
}
































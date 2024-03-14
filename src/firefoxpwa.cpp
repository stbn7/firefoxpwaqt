#include "firefoxpwa.h"

Firefoxpwa::Firefoxpwa()
{

}

QString Firefoxpwa::createProfile(QString profileName, QString description)
{
    QString result, idProfile;

    if(description == "")
    {
        description = "* Nothing *";
    }

    QStringList args, resultList;
    args << "profile" << "create" << "--name" << profileName << "--description" << description;

    QProcess *process = new QProcess;
    process->setProgram("firefoxpwa");
    process->setArguments(args);
    process->start();
    process->waitForFinished();
    QString list(process->readAllStandardOutput());
    process->close();

    resultList = list.split("\n");
    //resultList = firefoxpwa::execCommands(args);

    for(int i=0;i<resultList.size();i++)
    {
        result = resultList.at(i);
        if(result.contains("Profile created"))
        {
            idProfile = result.right(26);
        }
    }

    return idProfile;
}
QString Firefoxpwa::createApp(QString manifest, QString idProfile)
{
    QString idApp, result;
    QStringList args, resultList;
    args << "site" << "install" << manifest << "--profile" << idProfile;

    QProcess *process = new QProcess;
    process->setProgram("firefoxpwa");
    process->setArguments(args);
    process->start();
    process->waitForFinished();
    QString list(process->readAllStandardOutput());
    process->close();

    resultList = list.split("\n");

    for(int i=0; i<resultList.size(); i++)
    {
        result = resultList.at(i);
        if(result.contains("Web app installed:"))
        {
            idApp = result.right(26);
        }
    }
    return idApp;
}

void Firefoxpwa::removeApp(QString idApp)
{
    QStringList args;
    args << "site" << "uninstall" << idApp;

    QProcess *process = new QProcess();
    QObject::connect(process, &QProcess::readyReadStandardOutput, [process, this]()
                     {
                         QString output = process->readAllStandardOutput().simplified();

                         if (output.contains("(y/n)?", Qt::CaseInsensitive))
                         {
                             process->write("y");
                             process->write("\n");
                         }

                     });

    process->setProgram("firefoxpwa");
    process->setArguments(args);
    process->start();
    process->waitForFinished();
    process->close();

}

void Firefoxpwa::lauchApp(QString idApp)
{
    QStringList args;
    args << "site" << "launch" << idApp;

    QProcess *process = new QProcess;
    process->setProgram("firefoxpwa");
    process->setArguments(args);
    process->start();
    process->waitForFinished();
    QString tmpResults(process->readAllStandardOutput());
    process->close();

}

QList<QString> Firefoxpwa::listAppId()
{
    QList<QString> idApps;

    App *app = new App();
    QList<App*> listApps;

    listApps = Firefoxpwa::listApps();

    for(int i=0; i<listApps.size(); i++)
    {
        app = listApps.at(i);
        idApps.append(app->id());

    }

    delete app;
    return idApps;
}

QString Firefoxpwa::searchAppID(QString name)
{
    QString idApp;
    App *app = new App();
    QList<App*> listApps;

    listApps = Firefoxpwa::listApps();

    for(int i=0; i<listApps.size(); i++)
    {
        app = listApps.at(i);

        if(app->name() == name)
        {
            idApp = app->id();
        }

    }

    delete app;
    return idApp;
}

QList<App*> Firefoxpwa::searchApp(QString name) const
{
    App *app = new App();
    QList<App*> listApps;
    QList<App*> listApp;

    listApps = Firefoxpwa::listApps();

    for(int i=0; i<listApps.size(); i++)
    {
        app = listApps.at(i);

        if(app->name() == name)
        {
            listApp.append(app);
        }

    }

    return listApp;
}


void Firefoxpwa::removeProfile(QString idProfile)
{
    QStringList args;
    args << "profile" << "remove" << idProfile;

    QProcess *process = new QProcess();

    QObject::connect(process, &QProcess::readyReadStandardOutput, [process, this]()
                     {
                         QString output = process->readAllStandardOutput().simplified();

                         if (output.contains("(y/n)?", Qt::CaseInsensitive))
                         {
                             process->write("y");
                             process->write("\n");
                         }

                     });

    process->setProgram("firefoxpwa");
    process->setArguments(args);
    process->start();
    process->waitForFinished();
    process->close();
}

QString Firefoxpwa::searchProfileID(QString name)
{
    QString idProfile;
    Profile *profile = new Profile();
    QList<Profile*> listProfiles;
    listProfiles = Firefoxpwa::listProfile();

    for(int i=0; i<listProfiles.size();i++)
    {
        profile = listProfiles.at(i);
        if(name == profile->name())
        {
            idProfile = profile->id();
        }
    }
    delete profile;
    return idProfile;
}

QList<Profile*> Firefoxpwa::listProfile()
{
    QString nameProfile, description, idProfile, idApp, nameApp;
    QList<QString> listApps;

    QList<QString> keysListProfile;
    QList<Profile*> listProfile;

    QJsonParseError parseError;
    QJsonDocument configJson;

    QFile config(QDir::homePath() + "/.local/share/firefoxpwa/config.json");
    config.open(QIODevice::ReadOnly);
    QByteArray configJsonData= config.readAll();
    configJson = QJsonDocument::fromJson(configJsonData, &parseError);
    config.close();

    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "Parse error at" << parseError.offset << ":" << parseError.errorString();
    } else {
        QJsonObject objectJson = configJson.object();

        if( objectJson.contains("profiles"))
        {
            QJsonObject profileID = objectJson.value("profiles").toObject();
            keysListProfile = profileID.keys();

            foreach (QString key, keysListProfile) {

                QJsonValue values = profileID.value(key);
                description = values["description"].toString();

                if(description.isEmpty())
                {
                    description = "* Nothing *";
                }

                nameProfile = values["name"].toString();

                QJsonArray arrayApps = values["sites"].toArray();

                for (int i = 0; i < arrayApps.size(); ++i) {

                    idApp = arrayApps.at(i).toString();
                    nameApp = "";

                    if( objectJson.contains("sites"))
                    {
                        QJsonObject sites = objectJson.value("sites").toObject();
                        QJsonValue valueApp = sites.value(idApp);
                        QJsonValue valueConfig = valueApp.toObject().value("config");
                        nameApp = valueConfig["name"].toString();

                        if(nameApp.isEmpty()) {
                            QJsonValue valueManifest = valueApp.toObject().value("manifest").toObject();
                            nameApp = valueManifest["name"].toString();
                        }
                    }

                    listApps << nameApp;

                }

                if(listApps.isEmpty())
                {
                    listApps.append("* Nothing *");
                }

                idProfile = values["ulid"].toString();
                listProfile.append(new Profile(nameProfile,description,idProfile, listApps));
                listApps.clear();

            }
        }
    }

    return listProfile;
}

QStringList Firefoxpwa::listProfileNames()
{
    QStringList profileNames;
    Profile *profile = new Profile;
    QString name;

    QList<Profile*> listProfile = Firefoxpwa::listProfile();

    for(int i=0; i<listProfile.size(); i++)
    {
        profile = listProfile.at(i);
        profileNames.append(profile->name());

    }
    delete profile;
    return profileNames;
}

QList<App*> Firefoxpwa::listApps() const
{
    QList<App*> listApps;
    QList<QString> keysListApps;

    QString name, address, id, description, idProfile, nameProfile, iconPath;

    QJsonParseError parseError;
    QJsonDocument configJson;

    QFile config(QDir::homePath() + "/.local/share/firefoxpwa/config.json");
    config.open(QIODevice::ReadOnly);
    QByteArray configJsonData= config.readAll();
    configJson = QJsonDocument::fromJson(configJsonData, &parseError);
    config.close();

    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "Parse error at" << parseError.offset << ":" << parseError.errorString();
    } else {
        QJsonObject objectJson = configJson.object();

        if( objectJson.contains("sites"))
        {
            QJsonObject sites = objectJson.value("sites").toObject();
            keysListApps = sites.keys();

            foreach (QString key, keysListApps)
            {
                name = "None";
                address = "None";
                id = "None";
                description = "None";
                idProfile = "";

                //QList("config", "manifest", "profile", "ulid")
                QJsonValue valueApp = sites.value(key);
                id = valueApp.toObject().value("ulid").toString();
                idProfile = valueApp.toObject().value("profile").toString();

                QJsonValue valueConfig = valueApp.toObject().value("config");
                name = valueConfig["name"].toString();
                address = valueConfig["document_url"].toString();

                QJsonValue valueManifest = valueApp.toObject().value("manifest").toObject();
                description = valueManifest["description"].toString();

                if(name.isEmpty()) {
                    name = valueManifest["name"].toString();
                }

                if(objectJson.contains("profiles"))
                {
                    QJsonObject profileID = objectJson.value("profiles").toObject();
                    QJsonValue values = profileID.value(idProfile);
                    nameProfile = values["name"].toString();
                }

                nameProfile = nameProfile + " (" + idProfile + ")";
                iconPath = "FFPWA-" + id;

                listApps.append(new App(iconPath, name, address, id, description, nameProfile));

            }
        }
    }

    return listApps;
}

void Firefoxpwa::editApp(App app, QString iconPath)
{
    Utils::createIcon(app.id(), iconPath);

    QStringList args;
    args << "site" << "update" << app.id() <<"--name" << app.name() <<"--description" << app.description() <<"--no-manifest-updates";

    QProcess *process = new QProcess;
    process->setProgram("firefoxpwa");
    process->setArguments(args);
    process->start();
    process->waitForFinished();
    QString tmpResults(process->readAllStandardOutput());
    process->close();
    qDebug() << tmpResults;
}


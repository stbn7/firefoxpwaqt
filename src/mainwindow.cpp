#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QStyleHints>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QObject::connect(ui->btnAddApp, &QPushButton::clicked,
                     this, &MainWindow::addAppButtonClicked);

    QObject::connect(ui->btnAddProfile,&QPushButton::clicked,
                     this, &MainWindow::addProfileButtonClicked);

    QObject::connect(ui->btnLaunch,&QPushButton::clicked,
                     this, &MainWindow::launchButtonClicked);

    QObject::connect(ui->btnDeleteApp,&QPushButton::clicked,
                     this, &MainWindow::deleteAppButtonClicked);

    QObject::connect(ui->btnDeleteProfile,&QPushButton::clicked,
                     this, &MainWindow::deleteProfileButtonClicked);

    QObject::connect(ui->listWProfile, &QListWidget::activated,
                     this, &MainWindow::showProfileData);

    QObject::connect(ui->btnEditApp, &QPushButton::clicked,
                     this, &MainWindow::editButtonClicked);

    QObject::connect(ui->btnChanged, &QPushButton::clicked,
                     this, &MainWindow::changeButtonClicked);

    QObject::connect(ui->btnEditProfile, &QPushButton::clicked,
                     this, &MainWindow::editProfile);

    QObject::connect(ui->btnApp1, &QPushButton::clicked,
                     this, &MainWindow::showAppDataBtn1);

    QObject::connect(ui->btnApp2, &QPushButton::clicked,
                     this, &MainWindow::showAppDataBtn2);

    QObject::connect(ui->btnApp3, &QPushButton::clicked,
                     this, &MainWindow::showAppDataBtn3);

    const QPalette p = QGuiApplication::palette();
    const QColor bg = p.color(QPalette::Window);


    QFile workPath(QDir::homePath() + "/.local/share/firefoxpwaqt/icons");

    if(!workPath.exists())
    {
        Utils::copyResources();
    }


    ui->btnChanged->setHidden(true);
    ui->btnTool->setHidden(true);

    Utils::removeIconFile();
    Utils::updateIcons();

    if(bg.lightness() < 128)
    {
        ui->btnAddApp->setIcon(QIcon(QDir::homePath() + "/.local/share/firefoxpwaqt/icons/profiles/dark/add.svg"));
        ui->btnAddProfile->setIcon(QIcon(QDir::homePath() + "/.local/share/firefoxpwaqt/icons/profiles/dark/add.svg"));
    }else
    {
        ui->btnAddApp->setIcon(QIcon(QDir::homePath() + "/.local/share/firefoxpwaqt/icons/profiles/light/add.svg"));
        ui->btnAddProfile->setIcon(QIcon(QDir::homePath() + "/.local/share/firefoxpwaqt/icons/profiles/light/add.svg"));
    }

    ui->stackedWidget->setCurrentIndex(0);
    ui->btnDeleteProfile->setEnabled(false);
    ui->btnEditProfile->setHidden(true);
    ui->btnEditProfile->setEnabled(false);
    ui->btnChanged->setEnabled(false);

    QLabel *dockTitle = new QLabel("Profiles", ui->dockWidget);
    dockTitle->setStyleSheet("font-size: 10pt; padding-left: 10px; padding-top: 20px;");
    ui->dockWidget->setTitleBarWidget(dockTitle);

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::addAppButtonClicked()
{
    int option = ui->listWProfile->currentRow() + 1;

    AppDialog * appdialog = new AppDialog(this,option);

    if(appdialog->exec() == 0)
    {
        ui->listWProfile->clear();
        this->showListProfile();
        ui->stackedWidget->setCurrentIndex(0);

    }


}

void MainWindow::addProfileButtonClicked()
{
    ProfileDialog * profiledialog = new ProfileDialog(this);

    if(profiledialog->exec() == 0)
    {
        ui->listWProfile->clear();
        this->showListProfile();

    }


}

void MainWindow::launchButtonClicked()
{
    Firefoxpwa *pwa = new Firefoxpwa();
    QString idApp = ui->lblIdApp->text().remove("<b>ID: </b>");
    pwa->lauchApp(idApp);
    pwa->listAppId();
}

void MainWindow::editButtonClicked()
{
    QString idApp = ui->lblIdApp->text().remove("<b>ID: </b>");
    AppDialogEdit *editApp = new AppDialogEdit(this,idApp);

    if(editApp->exec() == 0)
    {
        //ui->listWApps->clear();
        this->showListApps();
        ui->stackedWidget->setCurrentIndex(2);
        MainWindow::showProfileData();
    }

}

void MainWindow::showListApps()
{
    App *app = new App();
    Firefoxpwa *pwa = new Firefoxpwa();
    QString iconPath;

    QList<App*> listApp = pwa->listApps();


    for(int i=0; i<listApp.size(); i++)
    {
        auto app = listApp.at(i);
        QString iconPath = QDir::homePath() + "/local/share/icons/" + QIcon::themeName() + "/apps/48/" + app->icon();//Change
        QFile file(iconPath);

        if(file.exists())
        {
            auto *item = new QListWidgetItem(QIcon::fromTheme(app->icon()),app->name(),ui->listWApps);
            item->setSizeHint(QSize(200, 25));
        }else
        {
            auto *item = new QListWidgetItem(QIcon(":/icons/profiles/" + MainWindow::darkMode() + "/foxy"),app->name(),ui->listWApps);
            item->setSizeHint(QSize(200, 25));
        }


    }
    listApp.clear();
    delete pwa;
    delete app;
}

void MainWindow::showListProfile()
{
    Firefoxpwa *pwa = new Firefoxpwa();
    //Profile *profile = new Profile();
    QString iconPath;


    QList<Profile*> listProfile = pwa->listProfile();


    std::sort(listProfile.begin(), listProfile.end(),
          [](const Profile* a, const Profile* b) {
        return a->name().localeAwareCompare(b->name()) < 0;
    });

    for(int i=0; i<listProfile.size();i++)
    {
        auto profile = listProfile.at(i);
        QString iconPath = QDir::homePath() + "/.local/share/firefoxpwaqt/icons/profiles/" + MainWindow::darkMode() + "/" + profile->name().toLower() + ".svg";
        QFile path(iconPath);

        if(path.exists())
        {
            auto *item = new QListWidgetItem(QIcon(iconPath), profile->name(),ui->listWProfile);
            item->setSizeHint(QSize(200, 25));
        }else
        {
            auto *item = new QListWidgetItem(QIcon(":/icons/profiles/" + MainWindow::darkMode() + "/foxy"), profile->name(),ui->listWProfile);
            item->setSizeHint(QSize(200, 25));
        }
    }

}
void MainWindow::showAppDataBtn1()
{
    MainWindow::showAppData(1);
}

void MainWindow::showAppDataBtn2()
{
    MainWindow::showAppData(2);
}

void MainWindow::showAppDataBtn3()
{
    MainWindow::showAppData(3);
}
void MainWindow::showAppData(int option)
{

    ui->btnEditApp->setIcon(QIcon(QDir::homePath() + "/.local/share/firefoxpwaqt/icons/profiles/"  + MainWindow::darkMode() + "/edit-app.svg"));
    ui->btnLaunch->setIcon(QIcon(QDir::homePath() + "/.local/share/firefoxpwaqt/icons/profiles/"  + MainWindow::darkMode() + "/run.svg"));
    ui->stackedWidget->setCurrentIndex(1);
    ui->btnDeleteProfile->setHidden(true);
    ui->btnEditProfile->setHidden(true);

    App *app = new App();
    Firefoxpwa *pwa = new Firefoxpwa();
    QString name = "";


    QString idProfile = ui->lblIdProfile->text().remove("ID: ");

    QList<App*> list = pwa->listApps();

    if(option == 1)
    {
        name = ui->btnApp1->text().remove(" 🡥");
    }
    if(option == 2)
    {
        name = ui->btnApp2->text().remove(" 🡥");
    }
    if(option == 3)
    {
        name = ui->btnApp3->text().remove(" 🡥");
    }



    for(int i=0; i<list.size(); i++)
    {
        app = list.at(i);

        if(app->name() == name && app->profile() == idProfile)
        {




            ui->lblNameApp->setText(app->name());


            if(QIcon::fromTheme(app->icon()).isNull())
            {
                ui->iconApp->setIcon(QIcon(QDir::homePath() + "/.local/share/firefoxpwaqt/icons/apps/file-unknown.svg"));
            }
            else
            {
                ui->iconApp->setIcon(QIcon::fromTheme(app->icon()));
            }
            
            
            ui->lblDescriptionApp->setText("<b>Description: </b>" + app->description());
            ui->lblDescriptionApp->setTextInteractionFlags(Qt::TextSelectableByMouse);
            ui->lblAddress->setText("<b>Address: </b>" + app->address());
            ui->lblIdApp->setText("<b>ID: </b>" + app->id());
            ui->lblIdApp->setTextInteractionFlags(Qt::TextSelectableByMouse);
            i = list.size();

        }

    }
}

void MainWindow::showProfileData()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->btnDeleteProfile->setEnabled(true);
    Firefoxpwa *pwa = new Firefoxpwa();
    ui->btnDeleteProfile->setHidden(false);
    ui->btnEditProfile->setEnabled(true);



    QList<Profile*> listProfile = pwa->listProfile();
    QString name = "";
    QString pathIcon;
    QList<QString> apps;

    Profile *profile = new Profile();

    name = ui->listWProfile->currentItem()->text();

    for(int i=0; i<listProfile.size(); i++)
    {
        profile = listProfile.at(i);
        if(profile->name() == name)
        {
            apps = profile->apps();
            ui->lblNameProfile->setText(profile->name());

            QString iconPath = QDir::homePath() + "/.local/share/firefoxpwaqt/icons/profiles/" + MainWindow::darkMode() + "/" + profile->name().toLower() + ".svg";
            QFile path(iconPath);

            if(path.exists())
            {
                ui->iconProfile->setIcon(QIcon(iconPath));
            }else
            {
                 ui->iconProfile->setIcon(QIcon(QDir::homePath() + "/.local/share/firefoxpwaqt/icons/profiles/" + MainWindow::darkMode() + "/foxy.svg"));
            }

            ui->lblDescriptionProfile->setText("Description: " + profile->description());
            ui->lblIdProfile->setText("ID: " + profile->id());
            ui->lblIdProfile->setTextInteractionFlags(Qt::TextSelectableByMouse);

            if(apps.at(0) == "* Nothing *")
            {
                ui->lblApps->setText("Apps: " + apps.at(0));
                ui->btnApp1->hide();
                ui->btnApp2->hide();
                ui->btnApp3->hide();
            }else
            {
                for(int i=0; i<apps.length(); i++)
                {
                    if(i==0)
                    {
                        ui->lblApps->show();
                        ui->lblApps->setText("Apps: ");
                        ui->btnApp1->show();
                        ui->btnApp1->setText(apps.at(i) + " 🡥");
                        ui->btnApp2->hide();
                        ui->btnApp3->hide();
                    }
                    if(i==1)
                    {
                        ui->btnApp2->show();
                        ui->btnApp2->setText(apps.at(i) + " 🡥");
                        ui->btnApp3->hide();
                    }
                    if(i==2)
                    {
                        ui->btnApp3->show();
                        ui->btnApp3->setText(apps.at(i) + " 🡥");
                    }

                }
            }


            i = listProfile.size();
        }

    }

    delete profile;
}

void MainWindow::deleteAppButtonClicked()
{
    Firefoxpwa *pwa = new Firefoxpwa();        
    QString id = ui->lblIdApp->text().remove("<b>ID: </b>");

    QMessageBox msgBox;
    msgBox.setWindowTitle("Remove Web App");
    //msgBox.setIcon(QIcon::fromTheme("info"));
    msgBox.setText("Are you sure you want to remove this web app?");
    msgBox.setInformativeText("This is the last app in this profile, so you can choose to delete it and the associated app data");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    if(msgBox.exec() == QMessageBox::Yes)
    {
        pwa->removeApp(id);
        this->showProfileData();
    }

    delete pwa;
}

void MainWindow::editProfile()
{
    ui->lblNameProfile->setTextInteractionFlags(Qt::TextEditable);
    ui->lblDescriptionProfile->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextEditable | Qt::TextSelectableByKeyboard);
}

void MainWindow::deleteProfileButtonClicked()
{
    Firefoxpwa *pwa = new Firefoxpwa();
    QString idProfile = ui->lblIdProfile->text().remove("ID: ");

    QMessageBox msgBox;
    msgBox.setWindowTitle("Remove Profile");
    //msgBox.setIcon(QIcon::fromTheme("info"));
    msgBox.setText("Are you sure you want to remove this profile?");
    msgBox.setInformativeText("This will completely remove the profile and all associated web apps, including their data. You might not be able to fully recover this action.");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    if(msgBox.exec() == QMessageBox::Yes)
    {
        pwa-> removeProfile(idProfile);
        ui->listWProfile->clear();
        this->showListProfile();
        //ui->listWidgetApps->item(0)->setSelected(true);
        ui->stackedWidget->setCurrentIndex(0);
    }
    delete pwa;
}

void MainWindow::changeButtonClicked()
{
    ui->listWApps->setEnabled(true);
    this->showListApps();

}

void MainWindow::colorSchemeChanged(bool enabled)
{
    if(enabled)
    {   //Dark Mode
        ui->listWProfile->setStyleSheet(R"(
            QListWidget {
                border: none;
                outline: none;
                border-radius: 10px;
            }
            QListWidget::item {
                border-radius: 5px;
            }

            QListWidget::item:selected {
                background-color: #464646;
                border: none;
                color: #ffffff;
            }

            QListWidget::item:hover {
                background-color: #2a2a2a;
            }

            QListWidget::item:selected:hover {
                background-color: #2a2a2a;
            }
        )");

        MainWindow::setStyleSheet(R"(
                background-color: #1c1f1e;
        )");


    }else
    {   //Ligth Mode
        ui->listWProfile->setStyleSheet(R"(
            QListWidget {
                border: none;
                outline: none;
                border-radius: 10px;
            }
            QListWidget::item {
                border-radius: 5px;
            }

            QListWidget::item:selected {
                background-color: #eeefef;
                border: none;
            }

            QListWidget::item:hover {
                background-color: #f0f0f0;
            }

            QListWidget::item:selected:hover {
                background-color: #cccccc;
            }
        )");

        MainWindow::setStyleSheet(R"(
                background-color: #ffffff;
        )");
    }

}

QString MainWindow::iconColor(bool enabled)
{
    QString color = "ligth";
    (enabled == true) ? MainWindow::setDarkMode("dark") : MainWindow::setDarkMode("light");
    return color;
}
void MainWindow::resetDataLabel()
{
    ui->listWProfile->clear();
}

QString MainWindow::darkMode() const
{
    return m_darkMode;
}

void MainWindow::setDarkMode(const QString &darkMode)
{
    m_darkMode = darkMode;
}



// void MainWindow::on_actionNewApp_triggered()
// {
//     this->addAppButtonClicked();
// }


// void MainWindow::on_actionNew_Profile_triggered()
// {
//     this->addProfileButtonClicked();
// }


// void MainWindow::on_actionQuit_triggered()
// {
//     this->close();
// }


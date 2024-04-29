#include "mainwindow.h"
#include "./ui_mainwindow.h"

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

    QObject::connect(ui->btnEditProfile, &QPushButton::clicked,
                     this, &MainWindow::editProfile);

    QObject::connect(ui->btnApp1, &QPushButton::clicked,
                     this, &MainWindow::showAppDataBtn1);

    QObject::connect(ui->btnApp2, &QPushButton::clicked,
                     this, &MainWindow::showAppDataBtn2);

    QObject::connect(ui->btnApp3, &QPushButton::clicked,
                     this, &MainWindow::showAppDataBtn3);


    this->showListProfile();
    ui->stackedWidget->setCurrentIndex(0);
    ui->btnDeleteProfile->setEnabled(false);
    ui->btnEditProfile->setHidden(true);
    ui->btnEditProfile->setEnabled(false);

    QLabel *dockTitle = new QLabel("Profiles", ui->dockWidget);
    dockTitle->setStyleSheet("font-size: 10pt; padding-left: 10px; padding-top: 20px;");
    ui->dockWidget->setTitleBarWidget(dockTitle);

    this->showListApps();



    //new QListWidgetItem(QIcon::fromTheme("applications-all"),"Applications",ui->listOption);
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
}

void MainWindow::editButtonClicked()
{
    QString idApp = ui->lblIdApp->text().remove("<b>ID: </b>");
    AppDialogEdit *editApp = new AppDialogEdit(this,idApp);

    if(editApp->exec() == 0)
    {
        //ui->listWApps->clear();
        this->showListApps();
    }

}

void MainWindow::showListApps()
{
    App *app = new App();
    Firefoxpwa *pwa = new Firefoxpwa();
    QList<App*> listApp = pwa->listApps();
    QString appIcon;


    for(int i=0; i<listApp.size(); i++)
    {
        app = listApp.at(i);

        if(QIcon::fromTheme(app->icon()).isNull())
        {
           // new QListWidgetItem(QIcon::fromTheme("foxy"),app->name(),ui->listWApps);
        }else
        {
            //new QListWidgetItem(QIcon::fromTheme(app->icon()),app->name(),ui->listWApps);
        }


    }
    listApp.clear();
    delete pwa;
    delete app;
}

void MainWindow::showListProfile()
{
    Firefoxpwa *pwa = new Firefoxpwa();
    Profile *profile = new Profile();
    QString iconPath;


    QList<Profile*> listProfile = pwa->listProfile();

    for(int i=0; i<listProfile.size();i++)
    {
        profile = listProfile.at(i);
        QString iconPath = QDir::homePath() + "/.local/share/icons/firefoxpwaqt/" + profile->name().toLower().split(" ").at(0) + ".svg";
        QFile path = iconPath;

        if(path.exists())
        {
            new QListWidgetItem(QIcon(iconPath), profile->name(),ui->listWProfile);
        }else
        {
            new QListWidgetItem(QIcon(":/icons/foxy"), profile->name(),ui->listWProfile);
        }
    }
    delete profile;
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

            QString appIcon = QDir::homePath() + "/.local/share/icons/hicolor/scalable/apps/FFPWA-" + app->id() + ".svg";
            QFile dirIcon(appIcon);

            if(!dirIcon.exists())
            {
                ui->iconApp->setIcon(QIcon(":/icons/foxy"));
            }
            else
            {
                ui->iconApp->setIcon(QIcon(appIcon));
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

            QString iconPath = QDir::homePath() + "/.local/share/icons/firefoxpwaqt/" + profile->name().toLower().split(" ").at(0) + ".svg";
            QFile path = iconPath;

            if(path.exists())
            {
                ui->iconProfile->setIcon(QIcon(iconPath));
            }else
            {
                 ui->iconProfile->setIcon(QIcon(":/icons/foxy"));
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
        Utils::removeFolder();
    }
    delete pwa;
}

void MainWindow::resetDataLabel()
{
    // ui->iconApp->setIcon(QIcon::fromTheme(""));
    // ui->lblDetails->setText("");
    // ui->lblNameApp->setText("");
    // ui->lblIdApp->setText("");
    // ui->lblDescriptionApp->setText("");
    // ui->lblAddress->setText("");
    // ui->lblProfile->setText("");
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


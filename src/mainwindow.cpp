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


    QObject::connect(ui->listOption,&QListWidget::activated,
                     this, &MainWindow::profileButtonClicked);

    QObject::connect(ui->listOption,&QListWidget::activated,
                     this, &MainWindow::appButtonClicked);

    QObject::connect(ui->btnLaunch,&QPushButton::clicked,
                     this, &MainWindow::launchButtonClicked);

    QObject::connect(ui->btnDeleteApp,&QPushButton::clicked,
                     this, &MainWindow::deleteAppButtonClicked);

    QObject::connect(ui->btnDeleteProfile,&QPushButton::clicked,
                     this, &MainWindow::deleteProfileButtonClicked);

    QObject::connect(ui->listWApps, &QListWidget::activated,
                     this, &MainWindow::showAppData);

    QObject::connect(ui->listWProfile, &QListWidget::activated,
                     this, &MainWindow::showProfileData);

    QObject::connect(ui->btnEditApp, &QPushButton::clicked,
                     this, &MainWindow::editButtonClicked);

    ui->listWProfile->hide();
    this->showListApps();
    ui->stackedWidget->setCurrentIndex(0);

    new QListWidgetItem(QIcon::fromTheme("applications-all"),"Applications",ui->listOption);
    new QListWidgetItem(QIcon::fromTheme("foxy"),"Profiles",ui->listOption);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::addAppButtonClicked()
{
    AppDialog * appdialog = new AppDialog(this);

    if(appdialog->exec() == 0)
    {
        ui->listWApps->clear();
        this->showListApps();
    }


}

void MainWindow::addProfileButtonClicked()
{
    ProfileDialog * profiledialog = new ProfileDialog();

    if(profiledialog->exec() == 0)
    {
        ui->listWProfile->clear();
        this->showListProfile();
    }


}

void MainWindow::profileButtonClicked()
{

    if(ui->listOption->currentItem()->text() == "Profiles")
    {
        ui->lblType->setText("Profiles");
        ui->listWApps->hide();
        ui->listWProfile->clear();   
        ui->listWProfile->show();
        this->showListProfile();
        ui->stackedWidget->setCurrentIndex(0);
    }


}

void MainWindow::appButtonClicked()
{
    if(ui->listOption->currentItem()->text() == "Applications")
    {
    ui->lblType->setText("Applications");
    ui->listWProfile->hide();
    ui->listWApps->clear(); 
    ui->listWApps->show();
    this->showListApps();
    ui->stackedWidget->setCurrentIndex(0);
    }

}

void MainWindow::launchButtonClicked()
{
    Firefoxpwa *pwa = new Firefoxpwa();
    QString name = ui->listWApps->currentItem()->text();
    QString idApp = pwa->searchAppID(name);
    pwa->lauchApp(idApp);
}

void MainWindow::editButtonClicked()
{
    QString name = ui->listWApps->currentItem()->text();
    AppDialogEdit *editApp = new AppDialogEdit(this,name);

    if(editApp->exec() == 0)
    {
        ui->listWApps->clear();
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
            new QListWidgetItem(QIcon::fromTheme("foxy"),app->name(),ui->listWApps);
        }else
        {
            new QListWidgetItem(QIcon::fromTheme(app->icon()),app->name(),ui->listWApps);
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

    QList<Profile*> listProfile = pwa->listProfile();

    for(int i=0; i<listProfile.size();i++)
    {
        profile = listProfile.at(i);
        new QListWidgetItem(QIcon::fromTheme("foxy"), profile->name(),ui->listWProfile);

    }
    delete profile;
}

void MainWindow::showAppData()
{

    ui->stackedWidget->setCurrentIndex(1);

    QString name = "";
    QString appIcon;
    Firefoxpwa *pwa = new Firefoxpwa();
    App *app = new App();

    QList<App*> list = pwa->listApps();

    name = ui->listWApps->currentItem()->text();

    for(int i=0; i<list.size(); i++)
    {
        app = list.at(i);
        if(app->name() == name)
        {
            ui->lblNameApp->setText(app->name());

            appIcon = "FFPWA-" + app->id();

            if(QIcon::fromTheme(appIcon).isNull())
            {                
                ui->iconApp->setIcon(QIcon::fromTheme(app->name().toLower()));
            }else
            {
                ui->iconApp->setIcon(QIcon::fromTheme("FFPWA-" + app->id()));
            }
            
            
            ui->lblDescriptionApp->setText("<b>Description: </b>" + app->description());
            ui->lblDescriptionApp->setTextInteractionFlags(Qt::TextSelectableByMouse);
            ui->lblAddress->setText("<b>Address: </b>" + app->address());
            ui->lblIdApp->setText("<b>ID: </b>" + app->id());
            ui->lblIdApp->setTextInteractionFlags(Qt::TextSelectableByMouse);

            ui->lblProfile->setText("<b>Profile:</b> " + app->profile());
            i = list.size();

        }

    }
}

void MainWindow::showProfileData()
{
    ui->stackedWidget->setCurrentIndex(2);

    Firefoxpwa *pwa = new Firefoxpwa();

    QList<Profile*> listProfile = pwa->listProfile();
    QString name = "";
    QString pathIcon;

    QDir filePath;

    pathIcon = QDir::homePath() + "/.local/share/icons/";
    pathIcon = pathIcon.append(QIcon::themeName()) + "/apps/symbolic/";

    Profile *profile = new Profile();

    name = ui->listWProfile->currentItem()->text();
    pathIcon = pathIcon + name.toLower().split(" ").at(0) + "-symbolic.svg";

    for(int i=0; i<listProfile.size(); i++)
    {
        profile = listProfile.at(i);
        if(profile->name() == name)
        {
            ui->lblNameProfile->setText(profile->name());

            if(filePath.exists(pathIcon))
            {
                ui->iconProfile->setIcon(QIcon::fromTheme(pathIcon));
            }else
            {
                ui->iconProfile->setIcon(QIcon::fromTheme("foxy"));
            }
            ui->lblDescriptionProfile->setText("Description: " + profile->description());
            ui->lblIdProfile->setText("ID: " + profile->id());
            ui->lblIdProfile->setTextInteractionFlags(Qt::TextSelectableByMouse);
            ui->lblApps->setText("Apps: " + profile->apps().at(0));
            i = listProfile.size();
        }

    }

    delete profile;
}

void MainWindow::deleteAppButtonClicked()
{
    Firefoxpwa *pwa = new Firefoxpwa();
    QString name, id;

    App *app = new App();

    QList<App*> listApp = pwa->listApps();
    name = ui->listWApps->currentItem()->text();

    for(int i=0; i<listApp.size(); i++)
    {
        app = listApp.at(i);
        if(app->name() == name)
        {
            id = app->id();
            i= listApp.size();
        }
    }

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
        ui->listWApps->clear();
        this->showListApps();
    }


    delete app;


}

void MainWindow::deleteProfileButtonClicked()
{
    Firefoxpwa *pwa = new Firefoxpwa();
    QString name, idProfile;

    Profile *profile = new Profile();

    QList<Profile*> listProfile = pwa->listProfile();
    name = ui->listWProfile->currentItem()->text();

    for(int i=0; i<listProfile.size(); i++)
    {
        profile = listProfile.at(i);
        if(profile->name() == name)
        {
            idProfile = profile->id();
            i= listProfile.size();
        }
    }

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
    }


    delete profile;
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



void MainWindow::on_actionNewApp_triggered()
{
    this->addAppButtonClicked();
}


void MainWindow::on_actionNew_Profile_triggered()
{
    this->addProfileButtonClicked();
}


void MainWindow::on_actionQuit_triggered()
{
    this->close();
}


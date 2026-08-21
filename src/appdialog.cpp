#include "appdialog.h"
#include "ui_appdialog.h"

AppDialog::AppDialog(QWidget *parent, int option) :
    QDialog(parent),
    m_option(option),
    ui(new Ui::AppDialog)
{
    ui->setupUi(this);

    QObject::connect(ui->appIcon, &QPushButton::pressed,
                     this, &AppDialog::appIconClick);
    QObject::connect(ui->buttonBox, &QDialogButtonBox::rejected,
                     this, &AppDialog::buttonCancelClick);
    QObject::connect(ui->buttonBox, &QDialogButtonBox::accepted,
                     this, &AppDialog::createButtonClick);
    QObject::connect(ui->lnEditName, &QLineEdit::editingFinished,
                     this, &AppDialog::ButtonBoxActive);
    QObject::connect(ui->lnEditManifest, &QLineEdit::textChanged,
                     this, &AppDialog::ButtonBoxActive);

    Firefoxpwa *pwa = new Firefoxpwa();

    ui->cmbBoxProfiles->addItem("Automatically Create a New Profile");
    ui->cmbBoxProfiles->addItems(pwa->listProfileNames());
    ui->cmbBoxProfiles->setCurrentIndex(option);
    ui->cmbBoxCategories->addItems(this->categoriesList());
    ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);

    ui->buttonBox->setMinimumHeight(30);

    QList<QAbstractButton *> buttons = ui->buttonBox->buttons();
    while(buttons.size())
        buttons.takeFirst()->setMinimumHeight(ui->buttonBox->minimumHeight());

}

AppDialog::~AppDialog()
{
    delete ui;
}

void AppDialog::buttonCancelClick()
{
    this->close();
}

void AppDialog::ButtonBoxActive()
{
    if(!ui->lnEditName->text().isEmpty() && !ui->lnEditManifest->text().isEmpty())
    {
        if(ui->lnEditManifest->text().startsWith("https://") || ui->lnEditManifest->text().startsWith("www."))
        {
            ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(false);
        }else{
            ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
        }

    }

}

void AppDialog::appIconClick()
{
    QString filter = "Images (*.svg)";
    QString iconPath = QFileDialog::getOpenFileName(this, "Select Icon", QDir::homePath() + "/.local/share/icons", filter);
    AppDialog::setIconPath(iconPath);

    if(iconPath.isEmpty())
    {
        //ui->appIcon->setIcon(QIcon(":/icons/foxy.svg"));
    }
    else
    {
        ui->appIcon->setIcon(QIcon(iconPath));
    }
}
void AppDialog::createButtonClick()
{
    QString idProfile;
    QString idApp;
    App *app = new App();
    Firefoxpwa *pwa = new Firefoxpwa();

    app->setName(ui->lnEditName->text());
    app->setAddress(ui->lnEditManifest->text());
    app->setCategories(ui->cmbBoxCategories->currentText());
    app->setDescription(ui->lnEditDescription->text());

    if(ui->cmbBoxProfiles->currentText() == "Automatically Create a New Profile")
    {
        idProfile = pwa->createProfile(app->name(), app->description());
        app->setId(pwa->createApp(app->address(),idProfile));
        idApp = app->id();

        App app(*pwa->searchAppForID(idApp));
        app.setName(ui->lnEditName->text());
        app.setDescription(ui->lnEditDescription->text());
        pwa->editApp(app,AppDialog::iconPath());
    }
    else
    {
        QString nameProfile;
        nameProfile = ui->cmbBoxProfiles->currentText();
        idProfile = pwa->searchProfileID(nameProfile);
        app->setId(pwa->createApp(app->address(),idProfile));

        idApp = app->id();

        App app(*pwa->searchAppForID(idApp));
        app.setName(ui->lnEditName->text());
        app.setDescription(ui->lnEditDescription->text());
        pwa->editApp(app,AppDialog::iconPath());

    }


    delete pwa;
    this->close();

}

QStringList AppDialog::categoriesList() const
{
    QStringList categoriesList = {
        "Audio",
        "Design",
        "Development",
        "Education",
        "Games",
        "Graphics",
        "Internet",
        "Multimedia",
        "Music",
        "Network",
        "Office",
        "Personalization",
        "Settings",
        "System",
        "Utilities",
        "Video",
        "Web",
    };

    categoriesList.sort();

    return categoriesList;
}

void AppDialog::setIconPath(const QString &path)
{
    m_iconPath = path;
}

QString AppDialog::iconPath() const
{
    return m_iconPath;
}

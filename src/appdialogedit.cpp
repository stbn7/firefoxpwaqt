#include "appdialogedit.h"
#include "ui_appdialogedit.h"

AppDialogEdit::AppDialogEdit(QWidget *parent, QString idApp)
    : QDialog(parent)
    , m_idApp(idApp)
    , ui(new Ui::AppDialogEdit)
{
    ui->setupUi(this);

    QObject::connect(ui->appIcon, &QPushButton::pressed,
                     this, &AppDialogEdit::appIconClick);
    QObject::connect(ui->buttonBox, &QDialogButtonBox::rejected,
                     this, &AppDialogEdit::rejectButtonClick);
    QObject::connect(ui->buttonBox, &QDialogButtonBox::accepted,
                     this, &AppDialogEdit::acceptedButtonClick);
    QObject::connect(ui->lnEditName, &QLineEdit::textChanged,
                     this, &AppDialogEdit::acceptedButtonActive);
    QObject::connect(ui->lnEditDescription, &QLineEdit::textChanged,
                     this, &AppDialogEdit::acceptedButtonActive);
    QObject::connect(ui->appIcon, &QPushButton::pressed,
                     this, &AppDialogEdit::acceptedButtonActive);

    Firefoxpwa *pwa = new Firefoxpwa();
    App *app = new App();

    ui->buttonBox->setMinimumHeight(30);

    QList<QAbstractButton *> buttons = ui->buttonBox->buttons();
    while(buttons.size())
        buttons.takeFirst()->setMinimumHeight(ui->buttonBox->minimumHeight());

    app = pwa->searchAppForID(idApp);

    this->setApp(app);

    ui->appIcon->setIcon(QIcon::fromTheme(app->icon()));
    ui->lnEditName->setText(app->name());
    ui->lnEditDescription->setText(app->description());
    ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
}

AppDialogEdit::~AppDialogEdit()
{
    delete ui;
}

void AppDialogEdit::setApp(const App *app)
{
    m_app = *app;
}

App AppDialogEdit::app() const
{
    return m_app;
}

void AppDialogEdit::appIconClick()
{
    QString filter = "Images (*.svg)";
    QString iconPath = QFileDialog::getOpenFileName(this, "Select Icon", QDir::homePath() + "/.local/share/icons", filter);
    this->setIconPath(iconPath);

    if(iconPath.isEmpty())
    {
        ui->appIcon->setIcon(QIcon::fromTheme(this->app().icon()));

    }
    else
    {
        ui->appIcon->setIcon(QIcon::fromTheme(iconPath));
    }
}

void AppDialogEdit::acceptedButtonClick()
{
    App app;
    app = AppDialogEdit::app();
    app.setName(ui->lnEditName->text());
    app.setDescription(ui->lnEditDescription->text());

    Utils::createIcon(app,this->iconPath());
    Firefoxpwa::editApp(app, this->iconPath());

    this->close();
}

void AppDialogEdit::acceptedButtonActive()
{
    if(!ui->lnEditName->text().isEmpty() && !ui->lnEditDescription->text().isEmpty())
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(false);
    }else if(!this->m_iconPath.isEmpty() && !ui->lnEditName->text().isEmpty()
               && !ui->lnEditDescription->text().isEmpty())
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(false);
    }else if(ui->lnEditName->text() == this->app().name() && ui->lnEditDescription->text() == this->app().description()
               && this->m_iconPath.isEmpty())
    {
         ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
    }
    else
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
    }
}

void AppDialogEdit::rejectButtonClick()
{
    this->close();
}

void AppDialogEdit::setIconPath(const QString &path)
{
    m_iconPath = path;
}

QString AppDialogEdit::iconPath() const
{
    return m_iconPath;
}


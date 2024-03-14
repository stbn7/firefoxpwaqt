#include "appdialogedit.h"
#include "ui_appdialogedit.h"

AppDialogEdit::AppDialogEdit(QWidget *parent, QString nameApp)
    : QDialog(parent)
    , m_nameApp(nameApp)
    , ui(new Ui::AppDialogEdit)
{
    ui->setupUi(this);

    QObject::connect(ui->appIcon, &QPushButton::pressed,
                     this, &AppDialogEdit::appIconClick);
    QObject::connect(ui->buttonBox, &QDialogButtonBox::rejected,
                     this, &AppDialogEdit::rejectButtonClick);
    QObject::connect(ui->buttonBox, &QDialogButtonBox::accepted,
                     this, &AppDialogEdit::acceptedButtonClick);

    Firefoxpwa *pwa = new Firefoxpwa();
    QList<App*> listApp;

    App *app = new App();

    ui->buttonBox->setMinimumHeight(30);

    QList<QAbstractButton *> buttons = ui->buttonBox->buttons();
    while(buttons.size())
        buttons.takeFirst()->setMinimumHeight(ui->buttonBox->minimumHeight());

    listApp = pwa->searchApp(nameApp);

    app = listApp.at(0);

    this->setApp(app);

    ui->appIcon->setIcon(QIcon::fromTheme(app->icon()));
    ui->lnEditName->setText(app->name());
    ui->lnEditDescription->setText(app->description());
}

AppDialogEdit::~AppDialogEdit()
{
    delete ui;
}

void AppDialogEdit::setNameApp(QString &nameApp)
{
    m_nameApp = nameApp;
}

QString AppDialogEdit::nameApp()
{
    return m_nameApp;
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
    this->app().setName(ui->lnEditName->text());
    this->app().setDescription(ui->lnEditDescription->toPlainText());
    Firefoxpwa::editApp(this->app(), this->iconPath());
    this->close();
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


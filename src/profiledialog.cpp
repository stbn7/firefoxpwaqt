#include "profiledialog.h"
#include "ui_profiledialog.h"

ProfileDialog::ProfileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProfileDialog)
{
    ui->setupUi(this);

    QObject::connect(ui->buttonBox,&QDialogButtonBox::rejected,
                     this, &ProfileDialog::buttonBoxRejected);

    QObject::connect(ui->buttonBox,&QDialogButtonBox::accepted,
                     this, &ProfileDialog::buttonBoxAccepted);
    QObject::connect(ui->lnName, &QLineEdit::textChanged,
                     this, &ProfileDialog::buttonBoxActive);


    ui->appIcon->setIcon(QIcon(":/icons/foxy"));
    ui->buttonBox->setMinimumHeight(30);

    QList<QAbstractButton *> buttons = ui->buttonBox->buttons();
    while(buttons.size())
        buttons.takeFirst()->setMinimumHeight(ui->buttonBox->minimumHeight());

    ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
}

ProfileDialog::~ProfileDialog()
{
    delete ui;
}

void ProfileDialog::buttonBoxAccepted()
{
    Firefoxpwa *pwa = new Firefoxpwa();
    QString nameProfile = ui->lnName->text();
    QString description = ui->lnDescription->text();
    pwa->createProfile(nameProfile,description);
    delete pwa;
    this->close();
}

void ProfileDialog::buttonBoxActive()
{
    if(!ui->lnName->text().isEmpty())
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(false);
    }else
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
    }
}

void ProfileDialog::buttonBoxRejected()
{
    this->close();
}

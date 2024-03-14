#ifndef APPDIALOG_H
#define APPDIALOG_H

#include <QDialog>
#include <QFileDialog>

#include "app.h"
#include "firefoxpwa.h"
#include "utils.h"

namespace Ui {
class AppDialog;
}

class AppDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AppDialog(QWidget *parent = nullptr);
    ~AppDialog();

    void setIconPath(const QString &path);
    QString iconPath() const;

private:
    Ui::AppDialog *ui;

    QStringList categoriesList() const;
    QString m_iconPath;

private slots:
    void appIconClick();
    void createButtonClick();
    void buttonCancelClick();
    void ButtonBoxActive();

};

#endif // APPDIALOG_H


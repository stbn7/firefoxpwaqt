#ifndef PROFILEDIALOG_H
#define PROFILEDIALOG_H

#include <QDialog>

#include "firefoxpwa.h"

namespace Ui {
class ProfileDialog;
}

class ProfileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProfileDialog(QWidget *parent = nullptr);
    ~ProfileDialog();

private:
    Ui::ProfileDialog *ui;

private slots:
    void buttonBoxAccepted();
    void buttonBoxRejected();
    void buttonBoxActive();
};

#endif // PROFILEDIALOG_H

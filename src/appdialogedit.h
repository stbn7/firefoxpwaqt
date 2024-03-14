#ifndef APPDIALOGEDIT_H
#define APPDIALOGEDIT_H

#include <QDialog>
#include <qstring.h>
#include "app.h"
#include "firefoxpwa.h"

#include <QFileDialog>

namespace Ui {
class AppDialogEdit;
}

class AppDialogEdit : public QDialog
{
    Q_OBJECT

public:
    explicit AppDialogEdit(QWidget *parent = nullptr, QString nameApp = nullptr);
    ~AppDialogEdit();

    QString nameApp();
    void setNameApp(QString &nameApp);

    App app() const;
    void setApp(const App *app);

    void setIconPath(const QString &path);
    QString iconPath() const;

private:
    Ui::AppDialogEdit *ui;

    QString m_nameApp;
    App m_app;
    QString m_iconPath;

private slots:
    void appIconClick();
    void acceptedButtonClick();
    void rejectButtonClick();
};

#endif // APPDIALOGEDIT_H

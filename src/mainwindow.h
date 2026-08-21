#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "appdialog.h"
#include "profiledialog.h"
#include "utils.h"
#include "app.h"
#include "appdialogedit.h"
#include <QResource>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void colorSchemeChanged(bool enabled);
    QString iconColor(bool enabled);

    QString darkMode() const;
    void setDarkMode(const QString &darkMode);

    void showListApps();
    void showListProfile();
    void resetDataLabel();


private:
    Ui::MainWindow *ui;

    QString m_darkMode;


    void editProfile();

    void showAppDataBtn1();
    void showAppDataBtn2();
    void showAppDataBtn3();

private slots:
    void addAppButtonClicked();
    void deleteAppButtonClicked();
    void deleteProfileButtonClicked();
    void addProfileButtonClicked();
    void launchButtonClicked();
    void showAppData(int option);
    void showProfileData();
    void editButtonClicked();
    void changeButtonClicked();


    //void on_actionNewApp_triggered();
    //void on_actionNew_Profile_triggered();
    //void on_actionQuit_triggered();
};
#endif // MAINWINDOW_H

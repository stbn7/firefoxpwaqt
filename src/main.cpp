#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QSettings>
#include <QStyleHints>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto *hints = QGuiApplication::styleHints();

    Qt::ColorScheme cs = Qt::ColorScheme::Dark;

    const QPalette p = QGuiApplication::palette();
    const QColor bg = p.color(QPalette::Window);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "firefoxpwaqt_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;

    if(bg.lightness() < 128)
    {
        w.iconColor(true);
        w.colorSchemeChanged(true);
        w.showListProfile();
    }else
    {
        w.iconColor(false);
        w.colorSchemeChanged(false);
        w.showListProfile();
    }


    QObject::connect(hints, &QStyleHints::colorSchemeChanged,
                     &a, [&](Qt::ColorScheme cs) {
                         bool dark = (cs == Qt::ColorScheme::Dark);

                         if(dark)
                         {
                             w.iconColor(true);
                             w.colorSchemeChanged(true);
                             //borrar ui->listWProfile->clear();
                             w.resetDataLabel();
                             w.showListProfile();


                         }else
                         {
                             w.iconColor(false);
                             w.colorSchemeChanged(false);
                             w.resetDataLabel();
                             w.showListProfile();

                         }

                     });



    w.show();
    return a.exec();
}

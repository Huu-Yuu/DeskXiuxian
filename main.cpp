#include "mainui.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "mainctrl.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "DeskXiuxian_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainCtrl *main_ctrl = new MainCtrl;
    main_ctrl->Init();
    main_ctrl->ShowMainUi();

    a.exec();
    delete main_ctrl;
    return 0;
}

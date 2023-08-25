#include "mainui.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QLockFile>
#include "mainctrl.h"


int main(int argc, char* argv[])
{
    //防止程序重复启动
    QLockFile lockFile("./Saite_RIDS_V5.lock");
    if(!lockFile.tryLock(2000))       //上锁失败，不能启动
    {
        printf("请不要重复启动程序... \n");
        return -1;
    }
    QApplication a(argc, argv);
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString& locale : uiLanguages)
    {
        const QString baseName = "DeskXiuxian_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName))
        {
            a.installTranslator(&translator);
            break;
        }
    }
    MainCtrl* main_ctrl = new MainCtrl;
#if LOCAL_DATABASE
    main_ctrl->ShowMainUi();
#else


#endif

    a.exec();
    delete main_ctrl;
    return 0;
}

#include "modules/ui/mainui.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QLockFile>
#include "main_ctrl.h"

int main(int argc, char* argv[])
{
    //防止程序重复启动
    QLockFile lockFile("./.DeskXiuxian.lock");
    if(!lockFile.tryLock(2000))       //上锁失败，不能启动
    {
        printf("请不要双开修仙... \n");
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
#if DATABASE_TYPE == 0
    main_ctrl->CheckAutoLogIn();
#elif DATABASE_TYPE == 1
    main_ctrl->ShowMainUi();
    main_ctrl->InitRoleInfo();
#elif DATABASE_TYPE == 2
    main_ctrl->InitRoleNetworkData();
#endif

    a.exec();
//    delete main_ctrl;
    return 0;
}

#include "mainui.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QStyle>
#include <QDesktopWidget>

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
    MainUI w;
    // 设置logo
    QIcon ico(":/res/logo.jpg");
    w.setWindowIcon(ico);

    // 设置窗口标题
    w.setWindowTitle("桌面修仙");

    // 固定窗口
    w.setFixedSize(w.width(),w.height());

    // 将窗口居中显示
    w.setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            w.size(),
            qApp->desktop()->availableGeometry()
        )
    );
    w.show();
    return a.exec();
}

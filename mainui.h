#ifndef MAINUI_H
#define MAINUI_H

#include <QMainWindow>
#include <QStyle>
#include <QDesktopWidget>
#include <QDate>
#include <QScrollBar>
#include <QTimer>
#include <QDebug>
#include "logger/logger.h"
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainUI; }
QT_END_NAMESPACE

class MainUI : public QMainWindow
{
    Q_OBJECT

public:
    MainUI(QWidget *parent = nullptr);
    ~MainUI();

    /**
     * @brief 添加消息到消息列表
     */
    void AddMessage(QString& msg);

    Ui::MainUI* GetUI();

signals:
    void SignalLogOut(QtMsgType type, const QMessageLogContext& context, const QString& message);

public slots:
    void SlotShowMsg()
    {

        QString msg = "登录成功" + QString::number(i);
        i++;
        AddMessage(msg);
    }


private:
    Ui::MainUI *ui;
    Logger* logger_;
    int i = 0;
};
#endif // MAINUI_H

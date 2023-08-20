#ifndef MAINUI_H
#define MAINUI_H

#include <QMainWindow>
#include <QStyle>
#include <QDesktopWidget>
#include <QDate>
#include <QScrollBar>
#include <QTimer>
#include <QDebug>
#include <QProcess>
#include <QTextStream>
#include "logger/logger.h"
#include "role/rolesystem.h"
#include "filedata/datamanage.h"
#include "game_progress/gameprogress.h"


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
    void AddMessage(QString msg);

    Ui::MainUI* GetUI();

    /**
     * @brief 更新角色基本信息，昵称、寿命、声望、修为
     */
    void UpdateRoleInformation(QString name, QString life, QString prestige, QString cultivation);

    /**
     * @brief 更新角色身体强度，经验值、攻击力、防御力、生命值
     */
    void UpdatePhysicalStrength(QString exp, QString agg, QString def, QString hp);

    /**
     * @brief 更新角色五行数据，金木水火土
     */
    void UpdateFiveAtt(QString metal, QString wood, QString water, QString fire, QString earth);

    /**
     * @brief 更新角色装备,武器、法宝、头盔、上衣、腰带、鞋、首饰、坐骑
     */
    void UpdateEquip(QString weapon, QString magic, QString helmet, QString clothing,
                     QString britches, QString shoe, QString jewelrt, QString mount);

signals:
    /**
        * @brief 输出日志信号
        */
    void SignalLogOut(QtMsgType type, const QMessageLogContext& context, const QString& message);

    /**
        * @brief 修为突破信号
        */
    void SignalUpgradeLevel();

    /**
        * @brief 开始修行
        */
    void SignalStartFishing();

    /**
        * @brief 结束修行
        */
    void SignalStopFishing();

public slots:

    /**
     * @brief 显示消息到窗口 槽函数
     */
    void SlotShowMsg(QString msg);

    /**
     * @brief 更新角色信息标签，UI控件，更新的信息
     */
    void SlotUpdateUI(RoleUI part, QString new_data);

    /**
     * @brief 激活突破按钮 槽函数
     */
    void SlotActivateCultivaUpButton();

    /**
     * @brief 禁用突破按钮 槽函数
     */
    void SlotDisableCultivaUpButton();

protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void on_star_but_clicked();

    void on_end_but_clicked();

    void on_cultiva_up_but_clicked();

private:
    QProcess* process;  // 用于关闭窗口时杀死所有进程
    Ui::MainUI *ui;
    Logger* logger_obj_;
    DataManage* data_file_;
};
#endif // MAINUI_H

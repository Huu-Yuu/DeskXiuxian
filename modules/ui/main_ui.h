#ifndef MAINUI_H
#define MAINUI_H

#include <QMainWindow>
#include <QStyle>
#include <QScreen>
#include <QDate>
#include <QScrollBar>
#include <QTimer>
#include <QDebug>
#include <QProcess>
#include <QTextStream>
#include "modules/logger/logger.h"
#include "modules/role/role_player.h"
#include "modules/item/item_manage.h"
#include "modules/filedata/datamanage.h"
#include "modules/game_progress/gameprogress.h"
#include "loginwindow.h"
#include "modifyrolename.h"
#include "modules/interface_manager.h"


QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainUI;
}
QT_END_NAMESPACE

class MainUI : public QMainWindow, InterfaceManager
{
    Q_OBJECT

public:
    MainUI(QWidget* parent = nullptr);
    ~MainUI();

//    Ui::MainUI* GetUI();

    void UpdateRoleInformation(QString name, QString life, QString prestige, QString cultivation);  ///< 更新角色基本信息，昵称、寿命、声望、修为
    void UpdatePhysicalStrength(QString exp, QString agg, QString def, QString hp);             ///< 更新角色身体强度，经验值、攻击力、防御力、生命值
    void UpdateFiveAtt(QString metal, QString wood, QString water, QString fire, QString earth);    ///< 更新角色五行数据，金木水火土
    void UpdateEquip(QString weapon, QString magic, QString helmet, QString clothing,
                     QString britches, QString shoe, QString jewelrt, QString mount);   ///< 更新角色装备,武器、法宝、头盔、上衣、腰带、鞋、首饰、坐骑
    void ShowLoginWidget();     ///< 显示登录窗口
    void ShowModifyNameWidget();    ///< 显示改名窗口
    void CloseLoginWidget();    ///< 关闭登录窗口
    void CloseModifyNameWidget();   ///< 关闭改名窗口

     // 初始化角色UI信息
    void InitRoleUI(QJsonObject role_info_data, QJsonObject role_item_data, QJsonObject role_rc_data, QJsonObject role_equic_data = QJsonObject());

signals:

    void SignalLogOut(QtMsgType type, const QMessageLogContext& context, const QString& message);   ///< 输出日志信号

    void SignalInitRoleData();  ///< 初始化角色数据信号
    void SignalUpgradeLevel();  ///< 修为突破信号
    void SignalStartFishing();  ///< 开始修行
    void SignalStopFishing();   ///< 结束修行

public slots:

    void SlotShowMsg(QString msg);  ///< 显示消息到窗口 槽函数
    void SlotUpdateUI(RoleUIEnum part, QString new_data);   ///< 更新角色信息标签，UI控件，更新的信息
    void SlotActivateCultivaUpButton(); ///<  激活突破按钮 槽函数
    void SlotDisableCultivaUpButton();  ///< 禁用突破按钮 槽函数
    void SlotLoginSuccessful(); ///< 登录成功处理 槽函数
    void SlotRenameSuccessful();    ///< 重命名成功处理 槽函数

protected:
    void closeEvent(QCloseEvent* event);

private slots:
    void on_star_but_clicked();

    void on_end_but_clicked();

    void on_cultiva_up_but_clicked();

private:
    /**
     * @brief 添加消息到消息列表
     */
    void AddMessage(QString msg);

    QProcess* process;  // 用于关闭窗口时杀死所有进程
    Ui::MainUI* ui;
    Logger* logger_obj_;
    DataManage* data_file_;
    ItemManage* role_item_; // 角色道具
    LoginWindow* login_obj_;    // 登录器
    ModifyRoleName* modify_obj_;    // 角色名修改窗口
};
#endif // MAINUI_H

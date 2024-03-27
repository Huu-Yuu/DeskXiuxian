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
#include "modules/item/item_service.h"
#include "modules/filedata/data_service.h"
#include "modules/progress/progress_service.h"
#include "loginwindow.h"
#include "modifyrolename.h"
#include "common/singleton.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainUI;
}
QT_END_NAMESPACE

class MainUI : public QMainWindow
{
    Q_OBJECT
    typedef void (MainUI::*Function_Rsp)(const QJsonObject&);
public:
    SINGLETON(MainUI);
    MainUI(QWidget* parent = nullptr);
    ~MainUI();

//    Ui::MainUI* GetUI();

    void UpdateRoleInformation(QString name, QString life, QString prestige, QString cultivation);  ///< 更新角色基本信息，昵称、寿命、声望、修为
    void UpdatePhysicalStrength(QString exp, QString agg, QString def, QString hp);             ///< 更新角色身体强度，经验值、攻击力、防御力、生命值
    void UpdateFiveAtt(QString metal, QString wood, QString water, QString fire, QString earth);    ///< 更新角色五行数据，金木水火土
    void UpdateEquip(QString weapon, QString magic, QString helmet, QString clothing,
                     QString britches, QString shoe, QString jewelrt, QString mount, QString title);   ///< 更新角色装备,武器、法宝、头盔、上衣、腰带、鞋、首饰、坐骑、称号
    void ShowLoginWidget();     ///< 显示登录窗口
    void ShowModifyNameWidget();    ///< 显示改名窗口
    void CloseLoginWidget();    ///< 关闭登录窗口
    void CloseModifyNameWidget();   ///< 关闭改名窗口

     // 初始化角色UI信息
    void InitRoleUI(QJsonObject role_info_data, QJsonObject role_item_data, QJsonObject role_rc_data, QJsonObject role_equic_data = QJsonObject());

    void UpdateRoleUI(const QJsonObject& data);    ///< 更新角色信息UI

    void FistLogInDeal(int result); ///< 处理首次登录结果
    void AutomaticLogin(int result);  ///< 自动登录
    void ModifyRoleNameDeal(int result);    ///< 处理重命名结果
    void RoleNameIsOkDeal(int result);     ///< 处理角色名是否重复结果
    void LoginVerificationDeal(int result);   ///< 登录校验处理  1-登录成功 0-账号或密码错误 -1-数据库连接失败
    void AccountRegistrationDeal(int result);   ///< 注册结果交互 1-注册成功 0-注册失败 -2-数据库连接失败 -1-账号已存在
signals:

    void SignalLogOut(QtMsgType type, const QMessageLogContext& context, const QString& message);   ///< 输出日志信号

    void SignalInitRoleData();  ///< 初始化角色数据信号
    void SignalUpgradeLevel();  ///< 修为突破信号
    void SignalStartFishing();  ///< 开始修行
    void SignalStopFishing();   ///< 结束修行

    //请求外部动作
    void SignalActionRequest(const QJsonObject& request_data);
    //本模块动作执行结果抛给上一级
    void SignalActionResponse(const QJsonObject& request_data);
    //状态变化抛给上一级
    void SignalPubTopic(const QJsonObject& pub_data);

public slots:

    void SlotShowMsg(QString msg);  ///< 显示消息到窗口 槽函数
    void SlotUpdateUI(RoleUIEnum part, QString new_data);   ///< 更新角色信息标签，UI控件，更新的信息
    void SlotActivateCultivaUpButton(); ///<  激活突破按钮 槽函数
    void SlotDisableCultivaUpButton();  ///< 禁用突破按钮 槽函数
    void SlotLoginSuccessful(); ///< 登录成功处理 槽函数
    void SlotRenameSuccessful(QString name);    ///< 重命名成功处理 槽函数

protected:
    void closeEvent(QCloseEvent* event);

private slots:
    void on_star_but_clicked();

    void on_end_but_clicked();

    void on_cultiva_up_but_clicked();

private:
    void initResponseFunction();    ///< 预留 初始化应答函数
    void AddMessage(QString msg);   ///< 添加消息到消息列表
    QMap<QString, Function_Rsp> map_function_rsp_;  ///< 处理应答
    QProcess* process;  // 用于关闭窗口时杀死所有进程
    Ui::MainUI* ui;
    Logger* logger_obj_;
    LoginWindow* login_obj_;    // 登录器
    ModifyRoleName* modify_obj_;    // 角色名修改窗口
};
#endif // MAINUI_H

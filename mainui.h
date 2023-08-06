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
#include "role/rolesystem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainUI; }
QT_END_NAMESPACE

/**
 * @brief 角色面板枚举，用于UI更新
 */
enum RoleUI
{
    kUnknown = 0,       // 未知
    kRoleName,          // 昵称
    kRoleLife,          // 寿命
    kRolePrestige,      // 声望
    kRoleCultivation,   // 修为
    kRoleExp,           // 经验值
    kRoleAgg,           // 攻击力
    kRoleDef,           // 防御力
    kRoleHp,            // 血量
    kAttMetal,          // 金
    kAttWood,           // 木
    kAttWater,          // 水
    kAttFire,           // 火
    kAttEarth,          // 土
    kEquipWeapon,       // 武器
    kEquipMagic,        // 法宝
    kEquipHelmet,       // 头盔
    kEquipClothing,     // 上衣
    kEquipBritches,     // 裤子
    kEquipShoe,         // 鞋子
    kEquipJewelrt,      // 首饰
    kPropRenameCard     // 改名卡
};

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
     * @brief 更新角色装备,武器、法宝、头盔、上衣、腰带、鞋、首饰
     */
    void UpdateEquip(QString weapon, QString magic, QString helmet, QString clothing, QString britches, QString shoe, QString jewelrt);

signals:
    void SignalLogOut(QtMsgType type, const QMessageLogContext& context, const QString& message);

public slots:
    void SlotShowMsg()
    {
        QString msg = "登录成功" + QString::number(i);
        i++;
        AddMessage(msg);
    }

    void SlotUpdateUI(RoleUI part, QString new_name);
private:
    Ui::MainUI *ui;
    Logger* logger_;
    RoleSystem * role_obj_;
    int i = 0;
};
#endif // MAINUI_H

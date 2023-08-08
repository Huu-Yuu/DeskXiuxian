#ifndef ROLESYSTEM_H
#define ROLESYSTEM_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include <QEventLoop>
#include "public/public_type.h"
#include <QVariant>
#include <QRandomGenerator>
#include <QJsonObject>
#include <QDebug>
#include "item/itemsystem.h"

/**
 * @brief 角色系统类
 */
class RoleSystem : public QThread
{
    Q_OBJECT

public:

    /**
     * @brief 获取单例
     */
    static RoleSystem* GetInstance();

    /**
        * @brief 获取角色面板属性
        * @return 通用类型 目标属性
        */
    QVariant GetRoleTargetProperties(RoleUI tar_name);

    /**
        * @brief 获取昵称
        * @return 昵称
        */
    QString GetRoleName() const;

    /**
        * @brief 设置昵称
        * @param name 昵称
        */
    void SetRoleName(const QString& name);

    /**
        * @brief 获取寿命
        * @return 寿命
        */
    double GetRoleLife() const;

    /**
        * @brief 设置寿命
        * @param name 寿命
        */
    void SetRoleLife(double life);

    /**
        * @brief 获取声望
        * @return 声望
        */
    int GetRolePrestige() const;

    /**
        * @brief 设置声望
        * @param name 声望
        */
    void SetRolePrestige(int prestige);

    /**
        * @brief 获取修为
        * @return 修为
        */
    QString GetRoleCultivation() const;

    /**
        * @brief 设置修为
        * @param cultivation 修为
        */
    void SetRoleCultivation(const QString& cultivation);

    /**
        * @brief 获取经验值
        * @return 经验值
        */
    int GetRoleExp() const;

    /**
        * @brief 设置经验值
        * @param exp 经验值
        */
    void SetRoleExp(int exp);

    /**
        * @brief 获取攻击力
        * @return 攻击力
        */
    int GetRoleAgg() const;

    /**
        * @brief 设置攻击力
        * @param agg 攻击力
        */
    void SetRoleAgg(int agg);

    /**
        * @brief 获取防御力
        * @return 防御力
        */
    int GetRoleDef() const;

    /**
        * @brief 设置防御力
        * @param def 防御力
        */
    void SetRoleDef(int def);

    /**
        * @brief 获取血量
        * @return 血量
        */
    int GetRoleHp() const;

    /**
        * @brief 设置血量
        * @param hp 血量
        */
    void SetRoleHp(int hp);

    /**
        * @brief 获取金属性
        * @return 金属性
        */
    int GetAttMetal() const;

    /**
        * @brief 设置金属性
        * @param metal 金属性
        */
    void SetAttMetal(int metal);

    /**
        * @brief 获取木属性
        * @return 木属性
        */
    int GetAttWood() const;

    /**
        * @brief 设置木属性
        * @param wood 木属性
        */
    void SetAttWood(int wood);

    /**
        * @brief 获取水属性
        * @return 水属性
        */
    int GetAttWater() const;

    /**
        * @brief 设置水属性
        * @param water 水属性
        */
    void SetAttWater(int water);

    /**
        * @brief 获取火属性
        * @return 火属性
        */
    int GetAttFire() const;

    /**
        * @brief 设置火属性
        * @param fire 火属性
        */
    void SetAttFire(int fire);

    /**
        * @brief 获取土属性
        * @return 土属性
        */
    int GetAttEarth() const;

    /**
        * @brief 设置土属性
        * @param earth 土属性
        */
    void SetAttEarth(int earth);

    /**
        * @brief 获取武器
        * @return 武器
        */
    QString GetEquipWeapon() const;

    /**
        * @brief 设置武器
        * @param weapon 武器
        */
    void SetEquipWeapon(const QString& weapon);

    /**
        * @brief 获取法宝
        * @return 法宝
        */
    QString GetEquipMagic() const;

    /**
        * @brief 设置法宝
        * @param magic 法宝
        */
    void SetEquipMagic(const QString& magic);

    /**
        * @brief 获取头盔
        * @return 头盔
        */
    QString GetEquipHelmet() const;

    /**
        * @brief 设置头盔
        * @param helmet 头盔
        */
    void SetEquipHelmet(const QString& helmet);

    /**
        * @brief 获取上衣
        * @return 上衣
        */
    QString GetEquipClothing() const;

    /**
        * @brief 设置上衣
        * @param clothing 上衣
        */
    void SetEquipClothing(const QString& clothing);

    /**
        * @brief 获取裤子
        * @return 裤子
        */
    QString GetEquipBritches() const;

    /**
        * @brief 设置裤子
        * @param britches 裤子
        */
    void SetEquipBritches(const QString& britches);

    /**
        * @brief 获取鞋子
        * @return 鞋子
        */
    QString GetEquipShoe() const;

    /**
        * @brief 设置鞋子
        * @param shoe 鞋子
        */
    void SetEquipShoe(const QString& shoe);

    /**
        * @brief 获取首饰
        * @return 首饰
        */
    QString GetEquipJewelry() const;

    /**
        * @brief 设置首饰
        * @param jewelry 首饰
        */
    void SetEquipJewelry(const QString& jewelry);

    /**
        * @brief 线程退出
        */
    void stopThread();

    /**
     * @brief 设置修仙资质
     */
    void SetAptitude(int aptitude);

    /**
     * @brief 获取修仙资质
     */
    double GetAptitude();

    /**
     * @brief 生成减益事件 当前12种
     */
    QString DebuffEvents(int rand, QString name, int money = 0, int exp = 0);

    /**
     * @brief 生成增益事件 当前15种
     */
    QString BuffEvents(int rand, QString name, int money = 0, int exp = 0);

    /**
     * @brief EXP对应修仙等级
     */
    QString ExpToCulStage(int exp);

signals:

    /**
        * @brief 发生消息到UI
        */
    void SignalShowMsgToUI(QString msg);

    /**
        * @brief 更新UI
        */
    void SignalUpdateUI(RoleUI part, QString new_data);

    /**
        * @brief 更新角色基本信息数据库
        */
    void SignalUpdateRoleInfoDatabase(QJsonObject role_data);

    /**
        * @brief 更新角色物品数据库
        */
    void SignalUpdateRoleItemDatabase(QJsonObject role_data);

public slots:
    /**
        * @brief 循环修炼，随机经验值、随机货币
        */
    void SlotCyclicCultivation();

protected:
    void run();

private:
    RoleSystem();

    // 阻止拷贝构造函数和赋值运算符
    RoleSystem(const RoleSystem&) = delete;
    RoleSystem& operator=(const RoleSystem&) = delete;

    static QMutex mutex;  // 互斥锁
    static RoleSystem* instance;  // 单例对象指针
    bool m_stopRequested = false;   // 线程停止
    QString role_name_;         // 昵称
    double role_life_;          // 寿命
    int role_prestige_;         // 声望
    QString role_cultivation_;  // 修为
    int role_exp_;      // 经验值
    int role_agg_;      // 攻击力
    int role_def_;      // 防御力
    int role_hp_;       // 血量
    int att_metal_;             // 金
    int att_wood_;              // 木
    int att_water_;             // 水
    int att_fire_;              // 火
    int att_earth_;             // 土
    QString equip_weapon_;      // 武器
    QString equip_magic_;       // 法宝
    QString equip_helmet_;      // 头盔
    QString equip_clothing_;    // 上衣
    QString equip_britches_;    // 裤子
    QString equip_shoe_;        // 鞋子
    QString equip_jewelry_;     // 首饰

    double aptitude_;   // 修仙资质 0.01 ~ 1
    double need_epx_;   // 每次升级所需要的经验值

    ItemSystem* role_item_; // 角色道具
};

#endif // ROLESYSTEM_H

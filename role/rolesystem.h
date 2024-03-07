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
    QVariant GetRoleTargetProperties(RoleUIEnum tar_name);

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
        * @param life 寿命
        */
    void SetRoleLife(double life);

    /**
        * @brief 获取角色最大寿命
        * @return 最大寿命
        */
    double GetMaxRoleLife() const;

    /**
        * @brief 更新角色最大寿命
        */
    void UpdataMaxRoleLife();

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
        * @brief 获取当前修为枚举类型
        * @return 修为枚举值
        */
    CultivationStage GetRoleCultivation() const;

    /**
        * @brief 设置当前修为枚举
        * @param cultivation 修为枚举
        */
    void SetRoleCultivation(CultivationStage cultivation);

    /**
        * @brief 获取角色总经验值
        * @return 经验值
        */
    int GetRoleExp() const;

    /**
        * @brief 设置角色总经验值
        * @param exp 经验值
        */
    void SetRoleExp(int exp);

    /**
        * @brief 获取当前角色经验值
        * @return 经验值
        */
    int GetCurRoleExp();

    /**
        * @brief 设置角色当前经验值
        * @
        * */
    void SetCurRoleExp(int exp);

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
     * @brief 设置角色寿命系数
     */
    void SetLifeCoefficient(int life_coefficient);

    /**
     * @brief 设置角色突破概率加成
     */
    void SetSurviveDisaster(int rc_survive_disaster);

    /**
     * @brief 获取修仙资质
     */
    int GetLifeCoefficient();

    /**
     * @brief 生成基础减益事件 当前12种 货币和经验值
     */
    QString DebuffEvents(int rand, QString name, int money = 0, int exp = 0);

    /**
     * @brief 生成基础增益事件 当前15种 货币和经验值
     */
    QString BuffEvents(int rand, QString name, int money = 0, int exp = 0);

    /**
     * @brief 生成3属性减益事件 攻击防御血量
     */
    QString DebuffEvents3Att(int rand, QString name, int agg = 0, int def = 0, int hp = 0);

    /**
     * @brief 生成3属性增益事件 攻击防御血量
     */
    QString BuffEvents3Att(int rand, QString name, int agg = 0, int def = 0, int hp = 0);

    /**
     * @brief 通用成长事件 3属性
     */
    QString GrowthEvents3Att(int rand, QString name, int agg = 0, int def = 0, int hp = 0);

    /**
     * @brief 获取修为名称
     */
    static QString GetCultivationName(CultivationStage cur_lv);
    static QString GetCultivationName(int cur_lv);
    /**
     * @brief 更新下一等级需要的经验
     */
    void UpdateEextGradeEXP();

    /**
        * @brief 检查经验值是否可以升级
        * @return t-可以升级  f-不可以升级
        */
    bool CheckExpIsUpgrade();

    /**
        * @brief 获取修为突破奖励
        */
    void GetBreakthroughReward();

    /**
        * @brief 获取修为突破失败处罚
        */
    void GetBreakthroughPenalty();

    /**
        * @brief 更新角色全部面板数据
        */
    void UpdateAllUI();

    /**
        * @brief 保存角色基本信息数据
        */
    void SaveRoleInfo();

    /**
        * @brief 保存角色道具数据
        */
    void SaveRoleItem();

    /**
        * @brief 保存角色属性系数数据
        */
    void SaveCoefficient();

    /**
        * @brief 突破前进行渡劫 返回渡劫是否成功
        */
    bool SurviveDisaster();

signals:

    /**
        * @brief 发送消息到UI
        */
    void SignalShowMsgToUI(QString msg);

    /**
        * @brief 更新角色指定面板数据
        */
    void SignalUpdateUI(RoleUIEnum part, QString new_data);

    /**
        * @brief 更新角色基本信息数据库
        */
    void SignalUpdateRoleInfoDatabase(QJsonObject role_data);

    /**
        * @brief 更新角色物品数据库
        */
    void SignalUpdateRoleItemDatabase(QJsonObject role_data);

    /**
        * @brief 更新角色属性各项系数
        */
    void SignalUpdateRoleCoefficientDatabase(QJsonObject RC_data);

    /**
     * @brief 激活突破按钮信号
     */
    void SignalActivateCultivaUpButton();

    /**
     * @brief 禁用突破按钮信号
     */
    void SignalDisableCultivaUpButton();

public slots:
    /**
        * @brief 循环修炼，随机经验值、随机货币
        */
    void SlotCyclicCultivation();

    /**
        * @brief 循环提升 攻击力、防御力、HP
        */
    void SlotCyclicEnhanceAtt();

    /**
        * @brief 寿命开始增加 槽函数
        */
    void SlotLifeUpdata();

    /**
        * @brief 修为突破 槽函数
        */
    void SlotUpgradeLevel();
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
    double role_max_life_;      // 角色最大寿命
    int role_prestige_;         // 声望
    CultivationStage role_LV_;    // 当前角色修为
    int role_cur_exp_;  // 角色当前经验值
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
    QString equip_mount_;       // 坐骑

    double aptitude_;   // 修仙资质 0.01 ~ 1
    double next_need_epx_;   // 下次升级所需要的经验值
    int RC_Life_;        // 角色寿命系数
    double RC_SurviveDisaster; //渡劫成功概率加成
    ItemSystem* role_item_; // 角色道具
};

#endif // ROLESYSTEM_H

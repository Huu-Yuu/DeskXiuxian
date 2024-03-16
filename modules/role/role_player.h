#ifndef ROLEPLAY_H
#define ROLEPLAY_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include <QEventLoop>
#include "modules/public/public_type.h"
#include <QVariant>
#include <QRandomGenerator>
#include <QJsonObject>
#include <QDebug>
#include "modules/item/item_service.h"
#include "common/singleton.h"

/**
 * @brief 角色系统类
 */
class RolePlayer : public QThread
{
    Q_OBJECT

public:
    SINGLETON(RolePlayer);
    RolePlayer();

    QString GetRoleName() const;    ///< 获取昵称
    void SetRoleName(const QString& name);  ///< 设置昵称
    double GetRoleLife() const; ///< 获取寿命
    void SetRoleLife(double life);  ///< 设置寿命
    double GetMaxRoleLife() const;  ///< 获取角色最大寿命
    void UpdataMaxRoleLife();   ///< 更新角色最大寿命
    CultivationStage GetRoleCultivation() const;    ///< 获取当前修为枚举类型
    void SetRoleCultivation(CultivationStage cultivation);  ///< 设置当前修为枚举

    void SetRoleBaseAtt(RoleBaseAttEnum baseAttEnum, int attValue = 0);  ///< 设置基本属性值
    QVariant GetRoleTargetProperties(RoleUIEnum tar_name);  ///< 获取角色面板对应的真实属性

    int GetElementAtt(ElementAttEnum attEnum) const;  ///< 获取元素属性
    void SetElementAtt(ElementAttEnum attEnum, int attValue = 0);   ///< 设置元素属性
    QString GetEquipAreaName(RoleEquipAreaEnum equipAreaEnum);      ///< 获取装备名称
    void SetEquipAreaName(RoleEquipAreaEnum equipAreaEnum, QString name = "");   ///< 设置装备名称
    void stopThread();  ///< 线程退出
    void SetAptitude(int aptitude); ///< 设置修仙资质
    double GetAptitude();   ///< 获取修仙资质
    void SetLifeCoefficient(int life_coefficient);  ///< 设置角色寿命系数
    void SetSurviveDisaster(int rc_survive_disaster);   ///< 设置角色突破概率加成
    int GetLifeCoefficient();   ///< 获取修仙资质
    QString DebuffEvents(int rand, QString name, int money = 0, int exp = 0);   ///< 生成基础减益事件 当前12种 货币和经验值
    QString BuffEvents(int rand, QString name, int money = 0, int exp = 0); ///< 生成基础增益事件 当前15种 货币和经验值
    QString DebuffEvents3Att(int rand, QString name, int agg = 0, int def = 0, int hp = 0); ///<  生成3属性减益事件 攻击防御血量
    QString BuffEvents3Att(int rand, QString name, int agg = 0, int def = 0, int hp = 0);   ///< 生成3属性增益事件 攻击防御血量
    QString GrowthEvents3Att(int rand, QString name, int agg = 0, int def = 0, int hp = 0); ///< 通用成长事件 3属性

    static QString GetCultivationName(CultivationStage cur_lv); ///< 获取修为名称
    static QString GetCultivationName(int cur_lv);

    void UpdateEextGradeEXP();  ///< 更新下一等级需要的经验

    /**
        * @brief 检查经验值是否可以升级
        * @return t-可以升级  f-不可以升级
        */
    bool CheckExpIsUpgrade();

    void GetBreakthroughReward();   ///< 获取修为突破奖励
    void GetBreakthroughPenalty();  ///< 获取修为突破失败处罚
    void UpdateAllUI(); ///< 更新角色全部面板数据
    void SaveRoleInfo();    ///< 保存角色基本信息数据
    void SaveRoleItem();    ///< 保存角色道具数据
    void SaveRoleItem(ItemType item_type, RoleItemEnum item_enum, int sum);    ///< 保存角色道具数据
    void SaveRoleEquip(RoleEquipAreaEnum area, RoleItemEnum item_enum);   ///< 保存角色装备数据
    void SaveCoefficient(); ///< 保存角色属性系数数据
    bool SurviveDisaster(); ///< 突破前进行渡劫 返回渡劫是否成功

signals:

    void SignalShowMsgToUI(QString msg);    ///< 发送消息到UI
    void SignalUpdateUI(RoleUIEnum part, QString new_data); ///< 更新角色指定面板数据
    void SignalUpdateRoleInfoDatabase(QJsonObject role_data);   ///< 更新角色基本信息数据库
    void SignalUpdateRoleItemDatabase(QJsonObject role_data);   ///< 更新角色物品数据库
    void SignalUpdateEquipItemDatabase(QJsonObject role_data);   ///< 更新角色物品数据库
    void SignalUpdateRoleCoefficientDatabase(QJsonObject RC_data);  ///< 更新角色属性各项系数
    void SignalActivateCultivaUpButton();   ///< 激活突破按钮信号
    void SignalDisableCultivaUpButton();    ///< 禁用突破按钮信号

public slots:

    void SlotCyclicCultivation();   ///< 循环修炼，随机经验值、随机货币
    void SlotCyclicEnhanceAtt();    ///< 循环提升 攻击力、防御力、HP
    void SlotLifeUpdate();      ///< 寿命开始增加 槽函数
    void SlotUpgradeLevel();    ///< 修为突破 槽函数

protected:
    void run();

private:
    static QMutex mutex;  // 互斥锁
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
    QString equip_title_;       // 称号

    double aptitude_;   // 修仙资质 0.01 ~ 1
    double next_need_epx_;   // 下次升级所需要的经验值
    int RC_Life_;        // 角色寿命系数 一年等于多少秒
    double RC_SurviveDisaster_; //渡劫成功概率加成
    ItemService* role_item_; // 角色道具
};

#endif // ROLEPLAY_H

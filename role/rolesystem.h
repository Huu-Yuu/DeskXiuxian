#ifndef ROLESYSTEM_H
#define ROLESYSTEM_H

#include <QObject>
#include <mutex>

/**
 * @brief 角色系统类
 */
class RoleSystem
{
public:

    /**
     * @brief 获取单例
     */
    static RoleSystem* GetInstance();

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

private:
    RoleSystem();

    // 阻止拷贝构造函数和赋值运算符
    RoleSystem(const RoleSystem&) = delete;
    RoleSystem& operator=(const RoleSystem&) = delete;

    /**
     * @brief 昵称
     */
    QString role_name_;

    /**
     * @brief 寿命
     */
    double role_life_;

    /**
     * @brief 修为
     */
    QString role_cultivation_;

    /**
     * @brief 经验值
     */
    int role_exp_;

    /**
     * @brief 攻击力
     */
    int role_agg_;

    /**
     * @brief 防御力
     */
    int role_def_;

    /**
     * @brief 血量
     */
    int role_hp_;

    /**
     * @brief 金属性
     */
    int att_metal_;

    /**
     * @brief 木属性
     */
    int att_wood_;

    /**
     * @brief 水属性
     */
    int att_water_;

    /**
     * @brief 火属性
     */
    int att_fire_;

    /**
     * @brief 土属性
     */
    int att_earth_;

    /**
     * @brief 武器
     */
    QString equip_weapon_;

    /**
     * @brief 法宝
     */
    QString equip_magic_;

    /**
     * @brief 头盔
     */
    QString equip_helmet_;

    /**
     * @brief 上衣
     */
    QString equip_clothing_;

    /**
     * @brief 裤子
     */
    QString equip_britches_;

    /**
     * @brief 鞋子
     */
    QString equip_shoe_;

    /**
     * @brief 首饰
     */
    QString equip_jewelry_;


};

#endif // ROLESYSTEM_H

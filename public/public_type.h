#ifndef PUBLIC_TYPE_H
#define PUBLIC_TYPE_H

#endif // PUBLIC_TYPE_H

// 一些经常使用到的枚举

/**
 * @brief 角色面板枚举
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
    kEquipeMount        // 坐骑
};

/**
 * @brief 角色背包，道具
 */
enum RoleItem
{
    kUnknownProp = 0,   // 未知
    kRoleMoney,         // 灵石
    kPropRenameCard     // 改名卡

};

/**
 * @brief 修为等级
 */
enum CultivationStage {
    FANREN = 0,
    LIANQI,
    ZHUJI,
    JIEDAN,
    YUANYING,
    HUASHEN,
    HETI,
    DACHENG,
    WUDAO,
    YUHUA,
    XIAN
};

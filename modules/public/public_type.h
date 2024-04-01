#ifndef PUBLIC_TYPE_H
#define PUBLIC_TYPE_H

// 一些经常使用到的枚举

/**
 * @brief 通信协议指令枚举列表
 */
enum TcpCmadType
{
    kTcpUnknown                   = -1, ///<保留错误类型
    kTcpRequestConnect            = 1,  ///<与服务器建立通信
    kTcpHeartBeats                = 2,  ///<获取修仙状态（心跳包）
    kTcpCreateAccount             = 3,  ///<创建账号
    kTcpCreateRole                = 4,  ///<创建角色
    kTcpRoleInit                  = 5,  ///<角色初始化
    kTcpRoleInfo                  = 6,  ///<角色基本信息
    kTcpRoleItem                  = 7,  ///<角色物品信息
    kTcpRoleEquip                 = 8,  ///<角色装备信息
    kTcpRoleRC                    = 9,  ///<角色成长系数
    kTcpRoleStatus                = 10, ///<角色状态  在线，离线，死亡
};

/**
 * @brief 远程操作枚举
 * **/
enum TcpOptCode
{
    kTcpOptUnknown          = -1,   ///< 保留错误类型
    kTcpOptQuery            = 1,    ///< 查询数据
    kTcpOptModify           = 2,    ///< 修改数据
    kTcpOptKickOffLine      = 3,    ///< 踢下线
};

enum ItemType
{
    kItemProp,          ///< 道具
    kItemMaterial,      ///< 材料
    kItemSpecial,       ///< 特殊
    kItemEquip          ///< 装备
};

/**
 * @brief 角色面板枚举
 */
enum RoleUIEnum
{
    kUnknown = 0,       ///< 未知
    kRoleName,          ///< 昵称
    kRoleLife,          ///< 寿命
    kRolePrestige,      ///< 声望
    kRoleCultivation,   ///< 修为
    kRoleExp,           ///< 经验值
    kRoleAgg,           ///< 攻击力
    kRoleDef,           ///< 防御力
    kRoleHp,            ///< 血量
    kAttMetal,          ///< 金
    kAttWood,           ///< 木
    kAttWater,          ///< 水
    kAttFire,           ///< 火
    kAttEarth,          ///< 土
    kEquipWeapon,       ///< 武器
    kEquipMagic,        ///< 法宝
    kEquipHelmet,       ///< 头盔
    kEquipClothing,     ///< 上衣
    kEquipBritches,     ///< 裤子
    kEquipShoe,         ///< 鞋子
    kEquipJewelrt,      ///< 首饰
    kEquipeMount,       ///< 坐骑
    kEquipeTitle        ///< 称号
};

/**
 * @brief 元素属性枚举
 * **/
enum ElementAttEnum
{
    kElementMetal,          ///< 金
    kElementWood,           ///< 木
    kElementWater,          ///< 水
    kElementFire,           ///< 火
    ElementEarth            ///< 土
};

/**
 * @brief 角色装备部位枚举
 * **/
enum RoleEquipAreaEnum
{
    kOther,
    kWeaponArea,            ///< 武器
    kMagicArea,            ///< 法宝
    kHelmetArea,           ///< 头盔
    kClothingArea,         ///< 上衣
    kBritchesArea,         ///< 裤子
    kShoeArea,             ///< 鞋子
    kJewelrArea,          ///< 首饰
    kMountArea,            ///< 坐骑
    kTitleArea            ///< 称号
};

/**
 * @brief 角色背包，道具
 */
enum RoleItemEnum
{
    kUnknownProp = 0,   ///< 未知
    ///////——————10000 - 道具——————///////
    kRoleMoney          = 10001,        ///< 灵石
    kPropRenameCard     = 10002,       ///< 改名卡
    kYanshouDan10       = 10003        ///< 十年延寿丹
    ///////——————20000 - 材料——————///////

    ///////——————30000 - 特殊——————///////

    ///////——————40000 - 装备——————///////
    ///////——————41000 - 武器——————///////

    ///////——————42000 - 法宝——————///////
    ///////——————43000 - 头盔——————///////
    ///////——————44000 - 上衣——————///////
    ///////——————45000 - 裤子——————///////
    ///////——————46000 - 鞋子——————///////
    ///////——————47000 - 首饰——————///////
    ///////——————48000 - 坐骑——————///////
    ///////——————49000 - 称号——————///////
};

/**
 * @brief 角色基本属性枚举
 * **/
 enum RoleBaseAttEnum
{
     kRoleNameAtt,          ///< 昵称
     kRoleLifeAtt,          ///< 当前寿命
     kRolePrestigeAtt,      ///< 声望
     kRoleLvAtt,            ///< 修为
     kRoleExpAtt,           ///< 经验值
     kRoleAggAtt,           ///< 攻击力
     kRoleDefAtt,           ///< 防御力
     kRoleHpAtt,            ///< 血量
     kRoleMaxLifeAtt,       ///< 最大寿命
     kRoleMaxExpAtt         ///< 总经验
};

/**
 * @brief 修为等级
 */
enum CultivationStage
{
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
    XIAN,
    MAXLV
};

// 话题发布
enum TopicSubActionType
{
    kSubType = 1,
    kUnsubType = 2,
};

// 道具操作枚举
enum PropOptEnum
{
    kNoOpt      = 0,        ///< 无操作
    kUseOpt,                ///< 使用道具
    kAcquireOpt,            ///< 获得道具
    kSellOpt                ///< 出售道具
};

#endif // PUBLIC_TYPE_H

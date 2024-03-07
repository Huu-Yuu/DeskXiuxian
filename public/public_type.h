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

enum TcpOptCode
{
    kTcpOptUnknown          = -1,   ///< 保留错误类型
    kTcpOptQuery            = 1,    ///< 查询数据
    kTcpOptModify           = 2,    ///< 修改数据
    kTcpOptKickOffLine      = 3,    ///< 踢下线
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
    kEquipeMount        ///< 坐骑
};

/**
 * @brief 角色背包，道具
 */
enum RoleItemEnum
{
    kUnknownProp = 0,   ///< 未知
    kRoleMoney,         ///< 灵石
    kPropRenameCard     ///< 改名卡

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
    XIAN
};

#endif // PUBLIC_TYPE_H

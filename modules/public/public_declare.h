#ifndef DESKXIUXINA_PUBLIC_DECLARE_H
#define DESKXIUXINA_PUBLIC_DECLARE_H

#include <QString>

const QString kRoleManage = "角色模块";
const QString kItemManage = "物品模块";
const QString kDataManage = "数据模块";
const QString kProgressManage = "进度模块";
const QString kUIManage = "UI模块";
const QString kMainCtrl = "主控模块";

namespace module_name
{
    const QString main = "main";
    const QString item = "item_system";                    ///< 物品模块
    const QString role = "role_system";                    ///< 角色模块
    const QString data = "data_system";              ///< 配置模块，数据管理
    const QString progress = "progress_system";            ///< 进度模块
    const QString ui = "ui_system";          ///< 界面模块
}

namespace ItemName
{
    const QString ItemMoney = "灵石";
    const QString ItemRenameCard = "改名卡";
}

namespace ProgressCmd
{
    const QString CyclicLifeUpdate = "CyclicLifeUpdate";        ///< 更新寿命
    const QString CyclicCultivation = "CyclicCultivation";        ///< 循环修炼
    const QString CyclicEnhanceAtt = "CyclicEnhanceAtt";        ///< 循环增加属性
}

namespace itemCmd
{
    const QString IncreaseMoney = "IncreaseMoney";      ///< 增加灵石
    const QString IncreModRoleBaseAtt = "IncreModRoleBaseAtt";      ///< 增量修改角色基本属性
    const QString UseProps = "DeductPropNum";                ///< 使用道具
    const QString UsePropsSuccessful = "UseProps";        ///< 使用道具成功
    const QString ItemAcquisition = "ItemAcquisition";  ///< 物品获取
    const QString GetItemIndex = "GetItemIndex";        ///< 获取物品索引
    const QString GetItemNum = "GetItemNum";            ///< 获取物品数量
    const QString SetItemNum = "SetItemNum";            ///< 设置物品数量
    const QString GetItemName = "GetItemName";          ///< 获取物品名称
    const QString SetItemName = "SetItemName";          ///< 设置物品名称
    const QString GetItemPrice = "GetItemPrice";        ///< 获取物品价格
    const QString SetItemPrice = "SetItemPrice";        ///< 设置物品价格
    const QString GetItemExplain = "GetItemExplain";    ///< 获取物品描述
    const QString SetItemExplain = "SetItemExplain";    ///< 设置物品描述
    const QString SellItem = "SellItem";                ///< 出售物品
}

namespace dbCmd
{
    const QString SaveRoleEquip = "SaveRoleEquip";  ///< 保存装备
    const QString SaveRoleItem = "SaveRoleItem";    ///< 保存物品
    const QString SaveRoleInfo = "SaveRoleInfo";    ///< 保存基本信息
    const QString SaveCoefficient = "SaveCoefficient";    ///< 保存属性系数
    const QString CheckLoginFist = "CheckLoginFist";    ///< 检测是否首次登录
    const QString CheckRoleNameIsOk = "CheckRoleNameIsOk";    ///< 检测角色昵称是否可用
    const QString LoginVerification = "LoginVerification";    ///< 登录校验
    const QString SetUserInfoToConfig = "SetUserInfoToConfig";    ///< 写入用户信息到配置文件
    const QString AccountRegistration = "AccountRegistration";    ///< 账号注册
    const QString UpdateLastLoginTime = "UpdateLastLoginTime";    ///< 更新最后登录时间
}

namespace roleCmd
{
    const QString ModifyRoleName = "ModifyRoleName";    ///< 修改角色名
}

namespace mainCmd
{
    const QString InitLocalRoleInfo = "InitLocalRoleInfo";    ///< 初始化本地角色信息
    const QString InitRemoteRoleInfo = "InitRemoteRoleInfo";    ///< 初始化远程角色信息
    const QString AutomaticLogin = "AutomaticLogin";    ///< 自动登录
    const QString UpdateLogInLog = "UpdateLogInLog";    ///< 更新登录日志
}

namespace uiCmd
{
    const QString ShowMainUI = "ShowMainUI";  ///< 显示主界面
    const QString ShowLoginWidget = "ShowLoginWidget";  ///< 显示登录窗口
    const QString ShowRenameWidget = "ShowRenameWidget";  ///< 显示改名窗口
    const QString InitRoleUI = "InitRoleUI";    ///< 初始化角色UI
    const QString ShowMsgToUI = "ShowMsgToUI";  ///< 显示信息到UI
    const QString DisableCultivaUpButton = "DisableCultivaUpButton";  ///< 禁用突破按钮
    const QString ActivateCultivaUpButton = "ActivateCultivaUpButton";  ///< 激活突破按钮
    const QString StartFishing = "StartFishing";    ///< 开始摸鱼
    const QString StopFishing = "StopFishing";    ///< 暂停摸鱼
    const QString UpgradeLevel = "UpgradeLevel";    ///< 突破等级
    const QString UpdateRoleUI = "UpdateRoleUI";    ///< 更新指定UI部件
    const QString UpdatePropShow = "InitPropShow";    ///< 初始化道具显示
}

#endif //DESKXIUXINA_PUBLIC_DECLARE_H

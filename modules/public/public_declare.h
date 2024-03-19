//
// Created by hu on 2024/3/7.
//

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

namespace itemCmd
{
    const QString GetItemIndex = "GetItemIndex";    ///< 获取物品索引
    const QString GetItemNum = "GetItemNum";        ///< 获取物品数量
    const QString SetItemNum = "SetItemNum";        ///< 设置物品数量
    const QString GetItemName = "GetItemName";      ///< 获取物品名称
    const QString SetItemName = "SetItemName";      ///< 设置物品名称
    const QString GetItemPrice = "GetItemPrice";    ///< 获取物品价格
    const QString SetItemPrice = "SetItemPrice";    ///< 设置物品价格
    const QString GetItemExplain = "GetItemExplain";///< 获取物品描述
    const QString SetItemExplain = "SetItemExplain";///< 设置物品描述
    const QString SellItem = "SellItem";            ///< 出售物品
}

namespace dbCmd
{
    const QString SaveRoleEquip = "SaveRoleEquip";  ///< 保存装备
    const QString SaveRoleItem = "SaveRoleItem";    ///< 保存物品
    const QString SaveRoleInfo = "SaveRoleInfo";    ///< 保存基本信息
    const QString SaveCoefficient = "SaveCoefficient";    ///< 保存属性系数
}

namespace mainCmd
{
    const QString InitRoleInfo = "InitRoleInfo";    ///< 初始化角色信息
}

namespace uiCmd
{
    const QString ShowMsgToUI = "ShowMsgToUI";  ///< 显示信息到UI
    const QString DisableCultivaUpButton = "DisableCultivaUpButton";  ///< 禁用图片按钮
    const QString StartFishing = "StartFishing";    ///< 开始摸鱼
    const QString StopFishing = "StopFishing";    ///< 暂停摸鱼
    const QString UpgradeLevel = "UpgradeLevel";    ///< 突破等级
}

#endif //DESKXIUXINA_PUBLIC_DECLARE_H

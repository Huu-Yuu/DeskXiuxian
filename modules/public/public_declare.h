//
// Created by hu on 2024/3/7.
//

#ifndef DESKXIUXINA_PUBLIC_DECLARE_H
#define DESKXIUXINA_PUBLIC_DECLARE_H

#include <QString>

namespace module_name
{
    const QString main = "main";
    const QString item = "item_system";                    ///< 物品模块
    const QString role = "role_system";                    ///< 角色模块
    const QString data = "data_system";  ///< 配置模块，数据管理
    const QString progress = "progress_system";            ///< 进度模块
    const QString userinterface = "ui_system";          ///< 界面模块
}

namespace ItemName
{
    const QString ItemMoney = "灵石";
    const QString ItemRenameCard = "改名卡";
}

namespace ItemCmd
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


#endif //DESKXIUXINA_PUBLIC_DECLARE_H

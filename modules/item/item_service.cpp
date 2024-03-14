#include "item_service.h"
#include "modules/public/public_declare.h"
#include "prop/prop_rename_card.h"

QMutex ItemService::mutex_;  // 初始化互斥锁对象

ItemService::ItemService()
{
    item_money_ = 0;
    InitItem();
}

ItemService::~ItemService()
{

}

int ItemService::GetItemMoney()
{
    return item_money_;
}

 void ItemService::SetItemMoney(int money)
 {
     item_money_ = money;
 }

void ItemService::ItemMoneyBusiness(int money) {
    item_money_ += money;
}

void ItemService::InitItem() {
    LOG_DEBUG("正在初始化道具...");
    m_action_strategy.insert(kPropRenameCard, RenameCard::getInstance());
}

void ItemService::SlotAddItems(RoleItemEnum item_enum, int obtain_num) {
    m_action_strategy.value(item_enum)->AddItemNum(obtain_num);
}

void ItemService::SlotSubtractItems(RoleItemEnum item_enum, int subtract_num) {
    m_action_strategy.value(item_enum)->AddItemNum(subtract_num);
}

void ItemService::initConnect() {
    for(QMap<int, ItemBase*>::iterator it = m_action_strategy.begin(); it != m_action_strategy.end(); ++it)
    {
        connect(it.value(), &ItemBase::SignalQuantityChanged, this, &ItemService::SlotQuantityChanged);
    }
}

void ItemService::SlotQuantityChanged(RoleItemEnum item_enum, int sum) {
    ItemType item_type = PublicFunc::ConvertItemType(item_enum);
    QJsonObject obj_data, obj_pub;
    if(item_type == kItemEquip)
    {
        RoleEquipAreaEnum area = PublicFunc::ConvertEquipArea(item_enum);
        QString area_str =  PublicFunc::ConvertEquipAreaStr(area);
        obj_data.insert(area_str, QString::number(item_enum));
        obj_pub.insert("type", dbCmd::SaveRoleEquip);
    }
    else
    {
        obj_data.insert(QString::number(item_enum), QString::number(item_enum));
        obj_pub.insert("type", dbCmd::SaveRoleItem);
    }
    obj_pub.insert("data", obj_data);
    emit SignalPubTopic(obj_pub);
}

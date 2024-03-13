#include "item_manage.h"
#include "modules/public/public_declare.h"
#include "prop/prop_rename_card.h"

QMutex ItemManage::mutex_;  // 初始化互斥锁对象

ItemManage::ItemManage()
{
    item_money_ = 0;
    InitItem();
}

ItemManage::~ItemManage()
{

}

int ItemManage::GetItemMoney()
{
    return item_money_;
}

 void ItemManage::SetItemMoney(int money)
 {
     item_money_ = money;
 }

void ItemManage::ItemMoneyBusiness(int money) {
    item_money_ += money;
}

void ItemManage::InitItem() {
    LOG_DEBUG("正在初始化道具...");
    m_action_strategy.insert(kPropRenameCard, RenameCard::getInstance());
}

void ItemManage::SlotAddItems(RoleItemEnum item_enum, int obtain_num) {
    m_action_strategy.value(item_enum)->AddItemNum(obtain_num);
}

void ItemManage::SlotSubtractItems(RoleItemEnum item_enum, int subtract_num) {
    m_action_strategy.value(item_enum)->AddItemNum(subtract_num);
}

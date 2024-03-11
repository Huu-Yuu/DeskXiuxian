#include "itemsystem.h"

QMutex ItemSystem::mutex_;  // 初始化互斥锁对象

ItemSystem::ItemSystem()
{
    item_money_ = 0;
}

ItemSystem::~ItemSystem()
{

}

int ItemSystem::GetItemMoney()
{
    return item_money_;
}

 void ItemSystem::SetItemMoney(int money)
 {
     item_money_ = money;
 }

void ItemSystem::ItemMoneyBusiness(int money) {
    item_money_ += money;
}

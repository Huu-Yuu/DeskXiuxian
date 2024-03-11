#include "item_manage.h"
#include "modules/public/public_declare.h"

QMutex ItemManage::mutex_;  // 初始化互斥锁对象

ItemManage::ItemManage()
{
    item_money_ = 0;
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

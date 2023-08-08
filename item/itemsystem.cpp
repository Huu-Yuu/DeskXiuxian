#include "itemsystem.h"

QMutex ItemSystem::mutex_;  // 初始化互斥锁对象
ItemSystem* ItemSystem::instance = nullptr;  // 初始化单例对象指针

ItemSystem::ItemSystem(QObject *parent) : QObject(parent)
{
    item_money_ = 0;
    item_rename_card_ = 0;
}

ItemSystem::~ItemSystem()
{

}

ItemSystem* ItemSystem::GetInstance()
{
    if (!instance) {
        QMutexLocker locker(&mutex_);  // 加锁
        if (!instance) {
            instance = new ItemSystem();
        }
    }
    return instance;
}

int ItemSystem::GetItemMoney()
{
    return item_money_;
}

 void ItemSystem::SetItemMoney(int money)
 {
     item_money_ = money;
 }

 int ItemSystem::GetItemRenameCard()
 {
     return item_rename_card_;
 }

 void ItemSystem::SetItemRenameCard(int item_rename_card)
 {
     item_rename_card_ = item_rename_card;
 }

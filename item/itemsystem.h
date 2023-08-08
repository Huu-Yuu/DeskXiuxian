#ifndef ITEMSYSTEM_H
#define ITEMSYSTEM_H

#include <QObject>
#include <QMutex>
#include "filedata/datamanage.h"


/**
 * @brief 物品系统类
 */
class ItemSystem : public QObject
{
    Q_OBJECT
public:
    static ItemSystem* GetInstance();

    ~ItemSystem();

    /**
     * @brief 获取灵石数量
     */
    int GetItemMoney();

    /**
     * @brief 写入灵石数量
     */
    void SetItemMoney(int money);

    /**
     * @brief 获取改名卡数量
     */
    int GetItemRenameCard();

    /**
     * @brief 写入改名卡数量
     */
    void SetItemRenameCard(int item_rename_card);

signals:

private:
    explicit ItemSystem(QObject *parent = nullptr);
    ItemSystem(const ItemSystem&) = delete;
    ItemSystem& operator=(const ItemSystem&) = delete;
    static ItemSystem* instance;  // 单例对象指针
    static QMutex mutex_; // 互斥锁，用于线程同步

    int item_money_;        // 角色货币
    int item_rename_card_;  // 改名卡
};

#endif // ITEMSYSTEM_H

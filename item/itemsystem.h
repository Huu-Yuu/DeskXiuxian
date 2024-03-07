#ifndef ITEMSYSTEM_H
#define ITEMSYSTEM_H

#include <QObject>
#include <QMutex>
#include "common//singleton.h"
#include "filedata/datamanage.h"
#include "itembase.h"


/**
 * @brief 物品系统类
 */
class ItemSystem : public QObject
{
    Q_OBJECT
public:
    SINGLETON(ItemSystem);
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
    static QMutex mutex_; ///< 互斥锁，用于线程同步
    QMap<int, ItemBase*> m_action_strategy; ///< 物品索引 和 类绑定
};

#endif // ITEMSYSTEM_H

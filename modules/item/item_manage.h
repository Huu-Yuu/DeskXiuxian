#ifndef ITEMSYSTEM_H
#define ITEMSYSTEM_H

#include <QObject>
#include <QMutex>
#include "common//singleton.h"
#include "modules/filedata/datamanage.h"
#include "itembase.h"

/**
 * @brief 物品系统类
 */
class ItemSystem : public QObject
{
    Q_OBJECT

    ItemSystem(QObject *parent);

public:
    SINGLETON(ItemManage);
    ItemManage();
    ~ItemManage();

    int GetItemMoney(); ///< 获取灵石数量

    void SetItemMoney(int money);   ///< 写入灵石数量
signals:

public slots:
    /**
     * @brief 灵石业务，用于增加或减少
     * @param money 增加或减少的灵石
     * **/
    void ItemMoneyBusiness(int money);

private:
    static QMutex mutex_; ///< 互斥锁，用于线程同步
    QMap<int, ItemBase*> m_action_strategy; ///< 物品索引 和 类绑定
    int item_money_;     ///< 货币灵石
};

#endif // ITEMSYSTEM_H

#ifndef ITEMSYSTEM_H
#define ITEMSYSTEM_H

#include <QObject>
#include <QMutex>
#include "common//singleton.h"
#include "modules/filedata/data_manage.h"
#include "itembase.h"

/**
 * @brief 物品系统类
 */
class ItemManage : public QObject
{
    Q_OBJECT

public:
    SINGLETON(ItemManage);
    ItemManage();
    ~ItemManage();

    void InitItem();    ///< 初始化物品
    int GetItemMoney(); ///< 获取灵石数量
    void SetItemMoney(int money);   ///< 写入灵石数量
signals:

public slots:
    /**
     * @brief 灵石业务，用于增加或减少
     * @param money 增加或减少的灵石
     * **/
    void ItemMoneyBusiness(int money);
    void SlotAddItems(RoleItemEnum item_enum, int add_num);   ///< 获取物品槽函数
    void SlotSubtractItems(RoleItemEnum item_enum, int subtract_num);   ///< 减少物品数量
private:
    static QMutex mutex_; ///< 互斥锁，用于线程同步
    QMap<int, ItemBase*> m_action_strategy; ///< 物品索引 和 类绑定
    QMap<int, int> m_item_sum; ///< 物品索引和数量
    int item_money_;     ///< 货币灵石
};

#endif // ITEMSYSTEM_H

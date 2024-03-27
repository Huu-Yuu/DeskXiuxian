#ifndef ITEMSYSTEM_H
#define ITEMSYSTEM_H

#include <QObject>
#include <QMutex>
#include "common//singleton.h"
#include "modules/filedata/data_service.h"
#include "itembase.h"

/**
 * @brief 物品管理类
 */
class ItemService : public QObject
{
    Q_OBJECT

public:
    SINGLETON(ItemService);
    ItemService();
    ~ItemService();

    void InitItem();    ///< 初始化物品
    void initConnect(); ///< 初始化连接
    int GetItemMoney(); ///< 获取灵石数量
    void SetItemMoney(int money);   ///< 写入灵石数量
    /**
     * @brief 灵石业务，用于增加或减少
     * @param money 增加或减少的灵石
     * **/
    void ItemMoneyBusiness(int money);
    void InitLocalRoleInfo(const QJsonObject& data);   ///< 初始化本地角色信息
signals:
    //请求外部动作
    void SignalActionRequest(const QJsonObject& request_data);
    //本模块动作执行结果抛给上一级
    void SignalActionResponse(const QJsonObject& request_data);
    //状态变化抛给上一级
    void SignalPubTopic(const QJsonObject& status);
public slots:

    void SlotAddItems(RoleItemEnum item_enum, int add_num);   ///< 获取物品槽函数
    void SlotSubtractItems(RoleItemEnum item_enum, int subtract_num);   ///< 减少物品数量
    void SlotQuantityChanged(RoleItemEnum item_enum , int sum); ///< 物品数量被改变槽函数，物品索引 变更后的数量
    void SlotUseItem(RoleItemEnum item_index, int sum = 1);     ///< 道具使用槽函数 物品索引 使用数量
private:
    void ShowMsgToUi(const QString& msg);       ///< 发送信息到UI显示
    static QMutex mutex_; ///< 互斥锁，用于线程同步
    QMap<int, ItemBase*> m_item_strategy; ///< 物品索引 和 类绑定
    QMap<int, int> m_item_sum; ///< 物品索引和数量
    int money_num_;     ///< 货币灵石
};

#endif // ITEMSYSTEM_H

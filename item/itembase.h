#ifndef ITEMBASE_H
#define ITEMBASE_H

#include <QObject>
#include <QMap>
#include "public/public_type.h"

/**
 * @brief 物品基类
 */
class ItemBase : public QObject
{
    Q_OBJECT
    typedef void (ItemBase::*Function_Action)(const QJsonObject&);
public:
    explicit ItemBase(QObject *parent = nullptr);

    int GetItemIndex();     ///< 获取物品索引

    int GetItemNum() const;     ///< 获取物品数量

    void SetItemNum(int num);       ///< 设置物品数量

    QString GetItemName() const;            ///< 获取物品名称

    void SetItemName(const QString& name);  ///< 写入物品名称

    int GetItemPrice() const;       ///< 获取物品价格

    void SetItemPrice(int price);   ///< 设置物品价格

    QString GetItemExplain() const; ///< 获取物品描述

    void SetItemExplain(const QString& explain);    ///< 写入物品描述

    /**
     * @brief 出售物品
     * @param quantity 出售数量
     * @return 总售价
     */
    int SellItem(int quantity) const;

signals:

protected:
    RoleItemEnum item_index_ = kUnknownProp;    ///< 物品索引
    QString item_name_ = "unknown";             ///< 名称
    QString item_explain_ = "unknown";          ///< 描述
    int item_num_ = 0;                          ///< 数量
    int item_price_ = 0;                        ///< 价格
    QMap<QString, Function_Action> m_function_action_;
};

#endif // ITEMBASE_H

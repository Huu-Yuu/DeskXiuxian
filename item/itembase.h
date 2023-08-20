#ifndef ITEMBASE_H
#define ITEMBASE_H

#include <QObject>

/**
 * @brief 物品基类
 */
class ItemBase : public QObject
{
    Q_OBJECT
public:
    explicit ItemBase(QObject *parent = nullptr);

    /**
     * @brief 获取物品数量
     */
    int GetItemNum() const;

    /**
     * @brief 设置物品数量
     */
    void SetItemNum(int num);

    /**
     * @brief 获取物品数量
     */
    QString GetItemName() const;

    /**
     * @brief 获取物品数量
     */
    void SetItemName(const QString& name);

    /**
     * @brief 获取物品价格
     */
    int GetItemPrice() const;

    /**
     * @brief 设置物品价格
     */
    void SetItemPrice(int price);

    /**
     * @brief 获取物品描述
     */
    QString GetItemExplain() const;

    /**
     * @brief 写入物品描述
     */
    void SetItemExplain(const QString& explain);

    /**
     * @brief 出售物品
     */
    virtual int SellItem(int quantity) const = 0;

signals:

private:
    QString item_name;      // 名称
    QString item_explain;   // 描述
    int item_num_;          // 数量
    int item_price_;        // 价格
};

#endif // ITEMBASE_H

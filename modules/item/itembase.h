#ifndef ITEMBASE_H
#define ITEMBASE_H

#include <QObject>
#include <QMap>
#include "modules/public/public_type.h"

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
    int GetItemType();      ///< 获取物品类型
    int GetItemNum() const;     ///< 获取物品数量
    void SetItemNum(int num);       ///< 设置物品数量
    void ItemNumCharge(int num);    ///< 物品数量改变 增加或减少
    QString GetItemName() const;            ///< 获取物品名称
    void SetItemName(const QString& name);  ///< 写入物品名称
    int GetItemPrice() const;       ///< 获取物品价格
    void SetItemPrice(int price);   ///< 设置物品价格
    QString GetItemExplain() const; ///< 获取物品描述
    void SetItemExplain(const QString& explain);    ///< 写入物品描述
    QString GetItemAccess();        ///< 获取物品的获取途径

    /**
     * @brief 出售物品
     * @param quantity 出售数量
     * @return 总售价
     */
    int SellItem(int quantity) const;

    /**
     * @brief 使用道具
     * @param sum 使用数量，默认为1
     * @return 返回错误码 无错误返回 NO_ERROR
     * **/
    int UseItem(int sum = 1);

signals:
    /**
     * @brief 数量被改变信号 用于修改数据库
     * @param sum 改变后的数量
     * **/
    void SignalQuantityChanged(RoleItemEnum item_enum , int sum);

    /**
     * @brief 佩戴装备信号
     * @param RoleItemEnum 物品索引
     * @param RoleEquipAreaEnum 佩戴部位
     * **/
    void SignalWearingEquipment(RoleItemEnum item_idenx, RoleEquipAreaEnum area_enum);

    /**
     * @brief 道具使用信号
     * @param item_idenx 物品索引
     * @param sum 使用数量
     * **/
    void SignalUseItem(RoleItemEnum item_index, int sum = 1);

public slots:

protected:
    virtual void UsageEffect(int sum = 1);  ///< 道具使用效果

    //////————————————物品基本属性——————————————//////
    RoleItemEnum item_index_ = kUnknownProp;    ///< 物品索引
    QString item_name_ = "unknown";             ///< 名称
    QString item_explain_ = "unknown";          ///< 描述
    int item_num_ = 0;                          ///< 数量
    int item_price_ = 0;                        ///< 价格
    QString item_access;                        ///< 获取途径
    QMap<QString, Function_Action> m_function_action_;      ///< 函数指针
    ItemType item_type_ = kItemMaterial;        ///< 物品类型


    //////————————————装备属性加成——————————————//////
    RoleEquipAreaEnum area = kOther;    ///< 装备部位 用于装备替换
    int agg_ = 0;       ///< 攻击力
    int def_ = 0;       ///< 防御力
    int hp_ = 0;        ///< 血量
    int metal_ = 0;     ///< 金
    int wood_ = 0;      ///< 木
    int water_ = 0;     ///< 水
    int fire_ = 0;      ///< 火
    int earth_ = 0;     ///< 土
    int prestige_ = 0;  ///< 声望
    int max_life_ = 0;  ///< 最大寿命
};

#endif // ITEMBASE_H

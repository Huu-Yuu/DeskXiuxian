#include "itembase.h"
#include "modules/public/error_code.h"
#include "modules/public/public_func.h"
#include "modules/public/public_declare.h"
#include <QJsonObject>

ItemBase::ItemBase(QObject *parent) : QObject(parent)
{

}

int ItemBase::GetItemNum() const {
    return item_num_;
}

void ItemBase::SetItemNum(int num) {
    item_num_ = num;
}

QString ItemBase::GetItemName() const {
    return item_name_;
}

void ItemBase::SetItemName(const QString &name) {
    item_name_ = name;
}

int ItemBase::GetItemPrice() const {
    return item_price_;
}

void ItemBase::SetItemPrice(int price) {
    item_price_ = price;
}

QString ItemBase::GetItemExplain() const {
    return item_explain_;
}

void ItemBase::SetItemExplain(const QString &explain) {
    item_explain_ = explain;
}

int ItemBase::SellItem(int quantity) const {
    return item_price_ * quantity;
}

int ItemBase::GetItemIndex() {
    return item_index_;
}

QString ItemBase::GetItemAccess()
{
    return item_access;
}

void ItemBase::UseItem(int sum) {
    Q_UNUSED(sum);
}

void ItemBase::ItemNumCharge(int num, PropOptEnum opt) {
    item_num_ += num;
    if(item_num_ >= 0)
        emit SignalQuantityChanged(item_index_, item_num_, opt);
    else
        qDebug() << item_name_ + "数量不能小于0";
}

int ItemBase::GetItemType() {
    return item_type_;
}

void ItemBase::ShowMsgToUi(const QString &msg) {
    QJsonObject data_obj;
    data_obj.insert("msg", msg);
    emit SignalActionRequest(PublicFunc::PackageRequest(uiCmd::ShowMsgToUI,
                                                        data_obj,
                                                        "",
                                                        module_name::ui,
                                                        module_name::item));
}

void ItemBase::IncrementItem(int num)
{
    item_num_ += num;
}


bool ItemBase::CanUpgrade()
{
    return false;
}

void ItemBase::EquipUpgrade()
{

}

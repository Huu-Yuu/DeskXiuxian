#include "itembase.h"
#include "modules/public/error_code.h"

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

int ItemBase::UseItem(int sum) {
    if(item_num_ >= sum)
    {
        item_num_ -= sum;
        UsageEffect(sum);
        return NO_ERROR;
    }
    return -1;
}

void ItemBase::ItemNumCharge(int num) {
    item_num_ += num;
    emit SignalQuantityChanged(item_index_, item_num_);
}

void ItemBase::UsageEffect(int sum) {
    Q_UNUSED(sum);
}

int ItemBase::GetItemType() {
    return item_type_;
}

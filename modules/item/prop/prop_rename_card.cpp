#include "prop_rename_card.h"

RenameCard::RenameCard() {
    item_index_ = kPropRenameCard;
    item_name_ = "改名卡";
    item_explain_ = "可以修改一次角色昵称";
    item_type_ = kItemProp;
}

RenameCard::~RenameCard()
{

}

void RenameCard::AddItemNum(int num) {
    item_num_ += num;
    emit SignalQuantityChanged(item_index_, item_num_);
}

void RenameCard::SubtractItemNum(int num) {
    item_num_ -= num;
    emit SignalQuantityChanged(item_index_, item_num_);
}

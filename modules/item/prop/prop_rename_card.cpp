#include "prop_rename_card.h"
#include "modules/public/public_declare.h"
#include "modules/public/public_macro.h"
#include <QFile>
#include <QDebug>
#include <QDateTime>

RenameCard::RenameCard() {
    item_index_ = kPropRenameCard;
    item_name_ = "改名卡";
    item_explain_ = "可以修改一次角色昵称";
    item_type_ = kItemProp;
    item_price_ = 1000;
    LOG_DEBUG(kItemManage, item_name_);
}

RenameCard::~RenameCard()
{
}

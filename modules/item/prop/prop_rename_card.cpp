#include "prop_rename_card.h"
#include "modules/public/public_declare.h"
#include "modules/public/public_macro.h"
#include "modules/public/public_func.h"
#include <QFile>
#include <QDebug>
#include <QDateTime>
#include <QJsonObject>

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

void RenameCard::UseItem(int num) {
    ShowMsgToUi("请重新设置昵称");
    emit SignalActionRequest(PublicFunc::PackageRequest(uiCmd::ShowRenameWidget,
                                                        QJsonObject(),
                                                        "",
                                                        module_name::ui,
                                                        module_name::item));
}


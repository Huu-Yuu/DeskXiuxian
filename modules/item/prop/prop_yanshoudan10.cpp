#include "prop_yanshoudan10.h"
#include "modules/public/public_declare.h"
#include "modules/public/public_macro.h"
#include "modules/public/public_func.h"
#include <QFile>
#include <QDebug>
#include <QDateTime>
#include <QJsonObject>

YanshouDan10::~YanshouDan10() {

}

YanshouDan10::YanshouDan10() {
    item_index_ = kYanshouDan10;
    item_name_ = "十年延寿药";
    item_explain_ = "延长十年寿命";
    item_type_ = kItemProp;
    item_price_ = 10000;
    LOG_DEBUG(kItemManage, item_name_);
}

void YanshouDan10::UsageEffect(int num) {
    QJsonObject data_obj;
    data_obj.insert("att_enum", kRoleMaxLifeAtt);
    data_obj.insert("sum", 10 * num);
    emit SignalActionRequest(PublicFunc::PackageRequest(itemCmd::IncreModRoleBaseAtt,
                                                        data_obj,
                                                        "",
                                                        module_name::role,
                                                        module_name::item));
}

#include "prop_yanshoudan10.h"
#include "modules/public/public_declare.h"
#include "modules/public/public_macro.h"
#include <QFile>
#include <QDebug>
#include <QDateTime>

YanshouDan10::~YanshouDan10() {

}

YanshouDan10::YanshouDan10() {
    item_index_ = kYanshouDan10;
    item_name_ = "十年延寿药";
    item_explain_ = "延长十年寿命";
    item_type_ = kItemProp;
    LOG_DEBUG(kItemManage, item_name_);
}

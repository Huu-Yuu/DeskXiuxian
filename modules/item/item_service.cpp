#include "item_service.h"
#include "modules/public/public_declare.h"
#include "prop/prop_rename_card.h"
#include "modules/item/prop/prop_yanshoudan10.h"
#include <QJsonArray>

QMutex ItemService::mutex_;  // 初始化互斥锁对象

ItemService::ItemService()
{
    money_num_ = 0;
    InitItem();
    initConnect();
}

ItemService::~ItemService()
{

}

int ItemService::GetItemMoney()
{
    return money_num_;
}

void ItemService::SetItemMoney(int money)
{
     money_num_ = money;
}

void ItemService::ItemMoneyBusiness(int money) {
    money_num_ += money;

    // 广播保存灵石数据
    QJsonObject obj_data, obj_pub;
    obj_data.insert(PublicFunc::ConvertItemEnumToDBStr(kRoleMoney), QString::number(money_num_));
    obj_pub.insert("type", dbCmd::SaveRoleItem);
    obj_pub.insert("data", obj_data);
    emit SignalPubTopic(obj_pub);
}

void ItemService::InitItem() {
    LOG_DEBUG(kItemManage, "正在初始化道具...");
    m_item_strategy.insert(kPropRenameCard, RenameCard::getInstance());
    m_item_strategy.insert(kPropYanshouDan10, YanshouDan10::getInstance());
}

void ItemService::initConnect() {
    for(QMap<int, ItemBase*>::iterator it = m_item_strategy.begin(); it != m_item_strategy.end(); ++it)
    {
        connect(it.value(), &ItemBase::SignalQuantityChanged, this, &ItemService::SlotQuantityChanged);
        connect(it.value(), &ItemBase::SignalActionRequest, this, &ItemService::SignalActionRequest);
    }
}

void ItemService::SlotQuantityChanged(RoleItemEnum item_enum, int sum, PropOptEnum opt) {
    QJsonObject obj_data, obj_pub;
    if(m_item_strategy[item_enum]->GetItemType() == kItemEquip)
    {
        RoleEquipAreaEnum area = PublicFunc::ConvertEquipArea(item_enum);
        QString area_str = PublicFunc::ConvertEquipAreaToDBStr(area);
        obj_data.insert(area_str, QString::number(item_enum));
        obj_pub.insert("type", dbCmd::SaveRoleEquip);
    }
    else
    {
        obj_data.insert(PublicFunc::ConvertItemEnumToDBStr(item_enum), QString::number(sum));
        obj_data.insert("prop_opt", opt);
        obj_pub.insert("type", dbCmd::SaveRoleItem);
    }
    obj_pub.insert("data", obj_data);
    emit SignalPubTopic(obj_pub);
}

void ItemService::InitLocalRoleInfo(const QJsonObject& data) {
    QJsonObject item_obj = data.value("RoleItem").toObject();
    QStringList keys = item_obj.keys(); ///< 键值对格式为： item_10001 int
    for(const auto& key : keys)
    {
        QString item_num = key.mid(5);  // 获取编号
        RoleItemEnum item_type = (RoleItemEnum) item_num.toInt();
        int num = item_obj.value(key).toString().toInt();
        if(item_type == kRoleMoney)
        {
            money_num_ = num;
        }
        else if(m_item_strategy.contains(item_type))
        {
            m_item_strategy[item_type]->SetItemNum(num);
        }
    }
}

void ItemService::ShowMsgToUi(const QString &msg) {
    QJsonObject data_obj;
    data_obj.insert("msg", msg);
    emit SignalActionRequest(PublicFunc::PackageRequest(uiCmd::ShowMsgToUI,
                                                        data_obj,
                                                        "",
                                                        module_name::ui,
                                                        module_name::item));
}

void ItemService::UpdatePropShow(const QJsonObject& request_data)
{
    QJsonArray item_arr;
    for(QMap<int, ItemBase*>::Iterator it = m_item_strategy.begin(); it != m_item_strategy.end(); it ++)
    {
        if(it.value()->GetItemNum() <= 0)
            continue;
        QJsonObject item_info;
        item_info.insert("prop_index", it.value()->GetItemIndex());
        item_info.insert("prop_name", it.value()->GetItemName());
        item_info.insert("prop_describe", it.value()->GetItemExplain());
        item_info.insert("prop_num", it.value()->GetItemNum());
        item_info.insert("prop_access", it.value()->GetItemAccess());
        item_info.insert("prop_price", it.value()->GetItemPrice());
        item_arr.append(item_info);
    }
    QJsonObject data_obj;
    data_obj.insert("prop_list", item_arr);
    emit SignalActionResponse(PublicFunc::PackageResponse(uiCmd::UpdatePropShow,
                                                          request_data.value("id").toString(),
                                                          0,
                                                          data_obj,
                                                          QJsonObject(),
                                                          request_data.value("ori").toString(),
                                                          module_name::item));
}

void ItemService::UseProps(int prop_index, int num) {
    m_item_strategy[prop_index]->UseItem(num);
}

void ItemService::DeductPropNum(int prop_index, int num) {
    m_item_strategy[prop_index]->ItemNumCharge(-num, kUseOpt);
}

void ItemService::IncrementItem(int prop_index, int num) {
    m_item_strategy[prop_index]->IncrementItem(num);
}


#include "item_service.h"
#include "modules/public/public_declare.h"
#include "prop/prop_rename_card.h"
#include "modules/item/prop/prop_yanshoudan10.h"

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
    m_item_strategy.insert(kYanshouDan10, YanshouDan10::getInstance());
}

void ItemService::SlotItemNumCharge(RoleItemEnum item_enum, int obtain_num) {
    m_item_strategy.value(item_enum)->ItemNumCharge(obtain_num);
}

void ItemService::initConnect() {
    for(QMap<int, ItemBase*>::iterator it = m_item_strategy.begin(); it != m_item_strategy.end(); ++it)
    {
        connect(it.value(), &ItemBase::SignalQuantityChanged, this, &ItemService::SlotQuantityChanged);
        connect(it.value(), &ItemBase::SignalUseItem, this, &ItemService::SlotUseItem);
    }
}

void ItemService::SlotQuantityChanged(RoleItemEnum item_enum, int sum) {
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
        int num = item_obj.value(key).toInt();
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

void ItemService::SlotUseItem(RoleItemEnum item_index, int sum) {
    switch (item_index) {
        case kUnknownProp:
            LOG_DEBUG(kItemManage, "未知道具");
            break;
        case kRoleMoney:
            LOG_DEBUG(kItemManage, "使用灵石");
            break;
        case kPropRenameCard:
            emit SignalActionRequest(PublicFunc::PackageRequest(uiCmd::ShowRenameWidget,
                                                                QJsonObject(),
                                                                "",
                                                                module_name::ui,
                                                                module_name::item));
            break;
        case kYanshouDan10:

            break;
    }
    ShowMsgToUi(QString("使用道具：%1，使用数量：%2").arg(m_item_strategy[item_index]->GetItemName()).arg(sum));
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

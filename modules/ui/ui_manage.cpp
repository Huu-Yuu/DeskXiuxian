#include "ui_manage.h"
#include "modules/public/public_declare.h"
#include <QJsonDocument>

UIManage::UIManage()
{
    m_module_name = module_name::ui;
    m_service_ = MainUI::getInstance();
}

int UIManage::Init() {
    return 0;
}

void UIManage::SlotActionResponse(const QJsonObject &request_data) {

}

void UIManage::SlotActionRequest(const QJsonObject &request_data) {
    LOG_DEBUG(kUIManage, QString("收到外部请求：%1").arg(QJsonDocument(request_data).toJson(QJsonDocument::Compact).data()));
    QString type = request_data.value("type").toString();
    if(type.contains(uiCmd::ShowMsgToUI))
    {
        QJsonObject data_obj = request_data.value("data").toObject();
        QString msg = data_obj.value("msg").toString();
        m_service_->SlotShowMsg(msg);
    }
}

void UIManage::SlotPubTopic(const QJsonObject &status) {

}

#ifndef DESKXIUXINA_ITEM_MANAGE_H
#define DESKXIUXINA_ITEM_MANAGE_H
#include <QObject>
#include "modules/interface_manager.h"
#include "item_service.h"

class ItemManage : public InterfaceManager
{
    Q_OBJECT
public:
    ItemManage();
    ~ItemManage();
    int Init() override;
    typedef void (ItemManage::*Function_Rsp)(const QJsonObject&);

public slots:
    void SlotActionResponse(const QJsonObject& response_data) override;
    void SlotActionRequest(const QJsonObject& request_data) override;
    void SlotPubTopic(const QJsonObject& topic_data) override;
private:
    void Do_Request_InitLocalRoleInfo(const QJsonObject& request_data);
    void Do_Request_IncreaseMoney(const QJsonObject& request_data);
    void Do_Request_UpdatePropShow(const QJsonObject& request_data);
    void Do_Request_UseProps(const QJsonObject& request_data);

    void Do_Topic_UsePropsSuccessful(const QJsonObject& topic_data);
private:
    ItemService* m_service_;
    QMap<QString, Function_Rsp> map_function_rsponse_;
    QMap<QString, Function_Rsp> map_function_request_;
    QMap<QString, Function_Rsp> map_function_topic_;

};

#endif //DESKXIUXINA_ITEM_MANAGE_H

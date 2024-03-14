//
// Created by hu on 2024/3/11.
//

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

public slots:
    void SlotActionResponse(const QJsonObject& request_data) override;
    void SlotActionRequest(const QJsonObject& request_data) override;
    void SlotPubTopic(const QJsonObject& status) override;
private:
    ItemService* item_obj_;
};

#endif //DESKXIUXINA_ITEM_MANAGE_H

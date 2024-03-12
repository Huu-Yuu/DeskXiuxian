//
// Created by hu on 2024/3/11.
//

#ifndef DESKXIUXINA_ITEM_SYSTEM_H
#define DESKXIUXINA_ITEM_SYSTEM_H
#include <QObject>
#include "modules/interface_manager.h"
#include "item_manage.h"

class ItemSystem : public InterfaceManager
{
    Q_OBJECT
public:
    ItemSystem();
    ~ItemSystem();
    int Init() override;

public slots:
    void SlotActionResponse(const QJsonObject& request_data) override;
    void SlotActionRequest(const QJsonObject& request_data) override;
    void SlotPubTopic(const QJsonObject& status) override;
private:
    ItemManage* item_obj_;
};

#endif //DESKXIUXINA_ITEM_SYSTEM_H

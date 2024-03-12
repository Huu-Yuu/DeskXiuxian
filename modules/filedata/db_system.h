//
// Created by hu on 2024/3/11.
//

#ifndef DESKXIUXINA_DB_SYSTEM_H
#define DESKXIUXINA_DB_SYSTEM_H
#include <QObject>
#include "modules/interface_manager.h"
#include "data_manage.h"

class DBSystem : public InterfaceManager
{
    Q_OBJECT
public:
    DBSystem();
    ~DBSystem();
    int Init() override;

public slots:
    void SlotActionResponse(const QJsonObject& request_data) override;
    void SlotActionRequest(const QJsonObject& request_data) override;
    void SlotPubTopic(const QJsonObject& status) override;
private:
    DataManage* data_obj_;
};

#endif //DESKXIUXINA_DB_SYSTEM_H

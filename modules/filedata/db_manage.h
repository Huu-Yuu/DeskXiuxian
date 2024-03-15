#ifndef DESKXIUXINA_DB_MANAGE_H
#define DESKXIUXINA_DB_MANAGE_H
#include <QObject>
#include "modules/interface_manager.h"
#include "data_service.h"

class DBManage : public InterfaceManager
{
    Q_OBJECT
public:
    DBManage();
    ~DBManage();
    int Init() override;

public slots:
    void SlotActionResponse(const QJsonObject& request_data) override;
    void SlotActionRequest(const QJsonObject& request_data) override;
    void SlotPubTopic(const QJsonObject& topic_data) override;
private:
    DataService* m_service_;
};

#endif //DESKXIUXINA_DB_MANAGE_H

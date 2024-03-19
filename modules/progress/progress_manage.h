//
// Created by hu on 2024/3/11.
//

#ifndef DESKXIUXINA_PROGRESS_MANAGE_H
#define DESKXIUXINA_PROGRESS_MANAGE_H
#include <QObject>
#include "modules/interface_manager.h"
#include "progress_service.h"

class ProgressManage : public InterfaceManager
{
    Q_OBJECT
public:
    ProgressManage();
    ~ProgressManage();
    int Init() override;

public slots:
    void SlotActionResponse(const QJsonObject& request_data) override;
    void SlotActionRequest(const QJsonObject& request_data) override;
    void SlotPubTopic(const QJsonObject& topic_data) override;
private:
    ProgressService* m_service_;
};

#endif //DESKXIUXINA_PROGRESS_MANAGE_H

//
// Created by hu on 2024/3/11.
//

#ifndef DESKXIUXINA_PROGRESS_MANAGE_H
#define DESKXIUXINA_PROGRESS_MANAGE_H
#include <QObject>
#include "modules/interface_manager.h"
#include "modules/progress/progress_service.h"

class ProgressManage : public InterfaceManager
{
    Q_OBJECT
public:
    ProgressManage();
    ~ProgressManage();
    int Init() override;
    typedef void (ProgressManage::*Function_Rsp)(const QJsonObject&) ;
public slots:
    void SlotActionResponse(const QJsonObject& response_data) override;
    void SlotActionRequest(const QJsonObject& request_data) override;
    void SlotPubTopic(const QJsonObject& topic_data) override;
private:
    void Do_Topic_StartFishing(const QJsonObject& request_data);
    void Do_Topic_StopFishing(const QJsonObject& request_data);
private:
    ProgressService* m_service_;
    QMap<QString, Function_Rsp> map_function_request_;
    QMap<QString, Function_Rsp> map_function_response_;
    QMap<QString, Function_Rsp> map_function_topic_;
};

#endif //DESKXIUXINA_PROGRESS_MANAGE_H

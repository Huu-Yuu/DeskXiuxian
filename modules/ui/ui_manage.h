#ifndef DESKXIUXINA_UI_MANAGE_H
#define DESKXIUXINA_UI_MANAGE_H
#include <QObject>
#include "modules/interface_manager.h"
#include "mainui.h"

class UIManage : public InterfaceManager
{
Q_OBJECT
public:
    UIManage();
    ~UIManage();
    int Init() override;

public slots:
    void SlotActionResponse(const QJsonObject& response_data) override;
    void SlotActionRequest(const QJsonObject& request_data) override;
    void SlotPubTopic(const QJsonObject& topic_data) override;

private:
    void UpdateUi(const QJsonObject& role_data);
    MainUI* m_service_;
};
#endif //DESKXIUXINA_UI_MANAGE_H

//
// Created by hu on 2024/3/11.
//

#ifndef DESKXIUXINA_PROGRESS_SYSTEM_H
#define DESKXIUXINA_PROGRESS_SYSTEM_H
#include <QObject>
#include "modules/interface_manager.h"
#include "game_progress.h"

class ProgressSystem : public InterfaceManager
{
    Q_OBJECT
public:
    ProgressSystem();
    ~ProgressSystem();
    int Init() override;

public slots:
    void SlotActionResponse(const QJsonObject& request_data) override;
    void SlotActionRequest(const QJsonObject& request_data) override;
    void SlotPubTopic(const QJsonObject& status) override;
private:
    GameProgress* game_pro_obj_;
};

#endif //DESKXIUXINA_PROGRESS_SYSTEM_H

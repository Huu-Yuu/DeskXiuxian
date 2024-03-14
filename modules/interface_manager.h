//
// Created by hu on 2024/3/11.
//

#ifndef DESKXIUXINA_INTERFACE_MANAGER_H
#define DESKXIUXINA_INTERFACE_MANAGER_H
#include <QObject>
#include "public/public_type.h"

class InterfaceManager : public QObject
{
    Q_OBJECT
public:
    InterfaceManager();
    virtual ~InterfaceManager();

    QString GetModuleName();
    virtual int Init() = 0;

signals:
    void SignalSubTopic(TopicSubActionType sub_type, const QStringList& topics);
    //请求外部动作
    void SignalActionRequest(const QJsonObject& request_data);
    //本模块动作执行结果抛给上一级
    void SignalActionResponse(const QJsonObject& request_data);
    //状态变化抛给上一级
    void SignalPubTopic(const QJsonObject& status);

public slots:
    virtual void SlotActionResponse(const QJsonObject& request_data) = 0;
    virtual void SlotActionRequest(const QJsonObject& request_data) = 0;
    virtual void SlotPubTopic(const QJsonObject& status) = 0;

protected:
    QString m_module_name = "unknown";
};


#endif //DESKXIUXINA_INTERFACE_MANAGER_H

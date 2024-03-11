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

    QString getModuleName();

signals:
    void signalSubTopic(TopicSubActionType sub_type, const QStringList& topics);
    //请求外部动作
    void signalActionRequest(const QJsonObject& request_data);
    //本模块动作执行结果抛给上一级
    void signalActionResponse(const QJsonObject& request_data);
    //状态变化抛给上一级
    void signalPubTopic(const QJsonObject& status);
public slots:
    virtual void slotActionResponse(const QJsonObject& request_data) = 0;
    virtual void slotActionRequest(const QJsonObject& request_data) = 0;
    virtual void slotPubTopic(const QJsonObject& status) = 0;
public:
    virtual int Init() = 0;
protected:
    QString m_module_name = "unknown";
};


#endif //DESKXIUXINA_INTERFACE_MANAGER_H
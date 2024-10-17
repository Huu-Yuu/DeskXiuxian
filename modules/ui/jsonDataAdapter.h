#ifndef JSONDATAADAPTER_H
#define JSONDATAADAPTER_H

#include <QString>
#include <QtCore>
#include <QMap>

//qml界面JSON数据转发到每个模块的接口
class JsonDataAdapter : public QObject
{
    Q_OBJECT
public:
    //json数据转发
    void jsonDataIn(const QJsonObject& obj)
    {
        emit emitJsonData(obj);
    }
    //json数据序列化
    QString jsonstringly(const QString& pageName, const QJsonObject& obj);
signals:
    void emitJsonData(const QJsonObject& obj);
};

#endif // JSONDATAADAPTER_H

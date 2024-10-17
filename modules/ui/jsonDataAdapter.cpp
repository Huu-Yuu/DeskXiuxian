#include "jsonDataAdapter.h"


QString JsonDataAdapter::jsonstringly(const QString& pageName, const QJsonObject& obj)
{
    QJsonObject json_obj;
    json_obj.insert("pageName", pageName);
    json_obj.insert("pageMsg", obj);
    return QJsonDocument(json_obj).toJson(QJsonDocument::Compact);
}

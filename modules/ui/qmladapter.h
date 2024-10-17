#ifndef QMLADAPTER_H
#define QMLADAPTER_H

#include <QtCore>
#include <QTimer>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QMap>
#include "jsonDataAdapter.h"

class QmlAdapter : public QObject
{
    Q_OBJECT
    //data2Qml变量是qml只读，自动调用本地getDataFromCpp()接口读取，
    //当data2Qml改变是会发送data2QmlChanged()信号
    Q_PROPERTY(QString data2Qml READ getDataFromCpp NOTIFY data2QmlChanged)
    //data2Cpp变量是qml只写，自动调用本地接口setDataToCpp()接口写入，
    //当data2Cpp变量改变时会发送data2CppChanged()信号
    Q_PROPERTY(QString data2Cpp READ getDataFromQml WRITE setDataToCpp NOTIFY data2CppChanged)

public:
    QmlAdapter(QObject* parent = nullptr);

    Q_INVOKABLE int stringSizeCount(QString src);
    void setRootObject(QQmlContext* root_context);
    QString getDataFromCpp() const;
    QString getDataFromQml() const;
    void setDataToCpp(const QString data);
    QQmlEngine* adapterEngine();
public slots:
    void onData2CppChanged();
    //外部模块发送json数据给qml，这里进行转发
    void onModelJsonData2Xml(const QString& data);
    //外部模块注册，当对应界面数据过来时可以自动转发到对应模块
    void onRegisterModel(const QString& pageName, QObject* obj);
signals:
    //xml<->C++交互数据触发信号
    void data2QmlChanged();
    void data2CppChanged();
private:
    void setData2Qml(const QString& data);
private:
    QQmlContext* root_context_;
    QString m_data2Qml_;
    QString m_data2Cpp_;
    QMap<QString, QObject*> models_;
    QQmlApplicationEngine engine;
};

#endif // QMLADAPTER_H

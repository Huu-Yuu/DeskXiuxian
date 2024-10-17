#include "qmladapter.h"
#include <QJsonObject>
#include <QDebug>
#include <QThread>
#include <QGuiApplication>
#include <QScreen>

int QmlAdapter::stringSizeCount(QString src)
{
    int i, size = src.size();
    float sum = 0;
    QChar check_char;
    for (i = 0; i < size; ++i)
    {
        check_char = src[i];
        //ASCII界线划分单字符和多字符
        if (check_char <= 170)
        {
            sum += 1;
        }
        else
        {
            sum += 1.75;
        }
    }
    sum /= 1.75;
    if (sum < float(0.00001))
    {
        return 1; //避免除0错误
    }

    //判断是否有小数
    int integer_part = int(sum);
    float decimal_part = sum - integer_part;
    if (decimal_part > 0)
    {
        return integer_part + 1;
    }

    return integer_part;
}

QmlAdapter::QmlAdapter(QObject* parent) : QObject (parent)
{
    setRootObject(engine.rootContext());

    connect(this, &QmlAdapter::data2CppChanged, this, &QmlAdapter::onData2CppChanged);
}

void QmlAdapter::setRootObject(QQmlContext* root_context)
{
    root_context_ = root_context;
}

QString QmlAdapter::getDataFromCpp() const
{
    return m_data2Qml_;
}

QString QmlAdapter::getDataFromQml() const
{
    return m_data2Cpp_;
}

void QmlAdapter::setDataToCpp(const QString data)
{
    if(m_data2Cpp_ != data)
    {
        m_data2Cpp_ = data;
        emit data2CppChanged();
        m_data2Cpp_.clear();
    }
}

QQmlEngine* QmlAdapter::adapterEngine()
{
    return &engine;
}

void QmlAdapter::onData2CppChanged()
{
    QJsonDocument json_doc = QJsonDocument::fromJson(m_data2Cpp_.toLocal8Bit().data());
    if(json_doc.isNull())
    {
        qDebug() << "string is null" << m_data2Cpp_;
        return;
    }
//    qDebug() << json_doc.object();
#if 1
    QJsonObject json_obj = json_doc.object();
    //初步解析是哪个页面发送的数据，然后根据注册的模块进行转发
    QString pageName = json_obj.value("pageName").toString();
    //qDebug() << "onData2CppChanged:" << pageName;
    QJsonObject json_obj_sub = json_obj.value("pageMsg").toObject();
    if(models_.contains(pageName))
        reinterpret_cast<JsonDataAdapter*>(models_[pageName])->jsonDataIn(json_obj_sub);
    else
        reinterpret_cast<JsonDataAdapter*>(models_["mainctrl"])->jsonDataIn(json_doc.object());
#else
    reinterpret_cast<JsonDataAdapter*>(models_["mainctrl"])->jsonDataIn(json_doc.object());
#endif
}

void QmlAdapter::onModelJsonData2Xml(const QString& data)
{
    setData2Qml(data);
}

void QmlAdapter::onRegisterModel(const QString& pageName, QObject* obj)
{
    models_[pageName] = obj;
}

void QmlAdapter::setData2Qml(const QString& data)
{
    if(data != m_data2Qml_)
    {
        m_data2Qml_ = data;
        emit data2QmlChanged();
        m_data2Qml_.clear();
    }
}

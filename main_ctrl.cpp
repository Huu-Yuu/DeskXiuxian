#include "main_ctrl.h"
#include "business/item_manage.h"
#include "business/db_manage.h"
#include "business/progress_manage.h"
#include "business/role_manage.h"
#include "business/ui_manage.h"
#include "modules/public/public_declare.h"

MainCtrl::MainCtrl(QObject* parent) : QObject(parent)
{
    //注册MessageHandler(注意要有日志文件夹)
//    qInstallMessageHandler(Logger::OutputMessageHandler);

    InitObj();
    InitConnect();
    InitFun();

}

MainCtrl::~MainCtrl()
{

}

void MainCtrl::ShowMainUi()
{
    onActionRequest(PublicFunc::PackageRequest(uiCmd::ShowMainUI,
                                               QJsonObject(),
                                               "",
                                               module_name::ui,
                                               module_name::main));
}

void MainCtrl::InitRoleInfo()
{
    QJsonObject data = PublicFunc::PackageRequest(mainCmd::InitLocalRoleInfo,
                                                  QJsonObject(),
                                                  "",
                                                  module_name::data,
                                                  module_name::main);
    onActionRequest(data);
}

void MainCtrl::InitRoleNetworkData()
{
    // 账号校验不通过，显示注册页面
    onActionRequest(PublicFunc::PackageRequest(uiCmd::ShowLoginWidget,
                                               QJsonObject(),
                                               "",
                                               module_name::ui,
                                               module_name::main));
    // 账号校验通过，显示运行界面
//    main_ui_obj_->ShowModifyNameWidget();
}

void MainCtrl::SlotDeviceResultDeal(int result, QJsonObject extra)
{
    qDebug() << "客户端信号错误处理函数，附加信息为：" << extra;
    int error_base = result & ERROR_BASE_MASK;
    switch (error_base)
    {
        case ERROR_NETWORK_BASE:
        {
            switch (result)
            {
                case ERROR_NETWORK_DISCONNECTED:
                {
                    qDebug() << "网络连接断开";
                    break;
                }
                case ERROR_NETWORK_COMMU_REFUSE:
                {
                    qDebug() << "服务器拒绝通信";
                    break;
                }
                case ERROR_NETWORK_REQUEST_REJECT:
                {
                    qDebug() << "服务器拒绝请求";
                    break;
                }
            }
            break;
        }
        default:
        {
            if (result != NO_ERROR)
            {
                qDebug() << Logger::GetErrorInfo(result, 2);
            }
        }
    }
}

void MainCtrl::InitObj() {
    QSharedPointer<InterfaceManager> interface_manager;
    interface_manager.reset(new ItemManage);
    RegisterInterfaceManager(interface_manager->GetModuleName(), interface_manager);
    interface_manager.reset(new DBManage);
    RegisterInterfaceManager(interface_manager->GetModuleName(), interface_manager);
    interface_manager.reset(new ProgressManage);
    RegisterInterfaceManager(interface_manager->GetModuleName(), interface_manager);
    interface_manager.reset(new RoleManage);
    RegisterInterfaceManager(interface_manager->GetModuleName(), interface_manager);
    interface_manager.reset(new UIManage);
    RegisterInterfaceManager(interface_manager->GetModuleName(), interface_manager);
}

void MainCtrl::RegisterInterfaceManager(QString type, QSharedPointer<InterfaceManager> inter_ptr) {
    if(m_manager_map.contains(type))
    {
        qDebug() << "已存在类型" << type << ",跳过注册请求";
    }
    else
    {
        qDebug() << "注册类型" << type << inter_ptr << "请求";
        m_manager_map.insert(type, inter_ptr);
    }
}

void MainCtrl::InitConnect() {
    QMapIterator < QString, QSharedPointer<InterfaceManager> > itor(m_manager_map);
    while(itor.hasNext())
    {
        itor.next();
        connect(itor.value().data(), &InterfaceManager::SignalActionRequest,
                this, &MainCtrl::onActionRequest);
        connect(itor.value().data(), &InterfaceManager::SignalActionResponse,
                this, &MainCtrl::onActionResponse);
        connect(itor.value().data(), &InterfaceManager::SignalSubTopic,
                this, &MainCtrl::onSubTopic);
        connect(itor.value().data(), &InterfaceManager::SignalPubTopic,
                this, &MainCtrl::onPubTopic);
        connect(this, &MainCtrl::SignalActionRequestResult,
                itor.value().data(), &InterfaceManager::SlotActionResponse);
    }
}

void MainCtrl::onPubTopic(const QJsonObject &request_data) {
    QString type = request_data.value("type").toString();
    QMap<QString, QStringList>::iterator it = m_cmd_topic_listen_list.begin();
    for(; it != m_cmd_topic_listen_list.end(); ++it)
    {
        if(it.value().contains(type) && m_manager_map.contains(it.key()))
        {
            m_manager_map[it.key()]->SlotPubTopic(request_data);
        }
    }
}

void MainCtrl::onSubTopic(TopicSubActionType action_type, const QStringList &topic_list) {
    InterfaceManager* psender = qobject_cast<InterfaceManager*>(sender());

    QString topic_msg;
    for(int i = 0; i < topic_list.size(); i++)
    {
        topic_msg += ("," + topic_list[i]);
    }
    QString debug_msg = "";
    if(action_type == TopicSubActionType::kSubType)
    {
        debug_msg = "注册";
    }
    else if(action_type == TopicSubActionType::kUnsubType)
    {
        debug_msg = "取消注册";
    }

    if(psender != nullptr)
    {
        QString module_name = psender->GetModuleName();
        if(action_type == TopicSubActionType::kSubType)
        {
            m_cmd_topic_listen_list[module_name].append(topic_list);
        }
        else if(action_type == TopicSubActionType::kUnsubType)
        {
            for(int i = 0; i < topic_list.size(); i++)
            {
                m_cmd_topic_listen_list[module_name].removeAll(topic_list.at(i));
            }
        }
    }
    else
    {
        LOG_INFO(kMainCtrl, QString("无法处理订阅请求:模块未初始化，%1主动上报消息：%2").arg(debug_msg).arg(topic_msg));
    }
}

void MainCtrl::InitFun() {
    QMapIterator < QString, QSharedPointer<InterfaceManager> > itor(m_manager_map);
    while(itor.hasNext())
    {
        itor.next();
        itor.value().data()->Init();
    }
}

void MainCtrl::onActionRequest(const QJsonObject &request_data) {
    QString type = request_data.value("type").toString();
    QString dest = request_data.value("dest").toString();
    QString ori = request_data.value("ori").toString();
    LOG_INFO(kMainCtrl, QString("主控类收到请求：%1 -> %2").arg(ori).arg(QJsonDocument(request_data).toJson(QJsonDocument::Compact).data()));
    if(m_manager_map.contains(dest))
    {
        m_manager_map[dest]->SlotActionRequest(request_data);
    }
    else
    {
        LOG_INFO(kMainCtrl, QString("[main] 无法处理请求：%1").arg(type));
    }
}

void MainCtrl::onActionResponse(const QJsonObject &request_data) {
    QString type = request_data.value("type").toString();
    QString dest = request_data.value("dest").toString();
    LOG_INFO(kMainCtrl, QString("中心回复请求：%1").arg(QJsonDocument(request_data).toJson(QJsonDocument::Compact).data()));
    if(m_manager_map.contains(dest))
    {
        m_manager_map[dest]->SlotActionResponse(request_data);
    }
    else
    {
        LOG_INFO(kMainCtrl, QString("[main] 无法处理回复：%1").arg(type));
    }
}

void MainCtrl::CheckAutoLogIn() {
    // 获取本地登录记录，检查是否可以自动登录
    onActionRequest(PublicFunc::PackageRequest(mainCmd::AutomaticLogin,
                                               QJsonObject(),
                                               "",
                                               module_name::data,
                                               module_name::ui));
}

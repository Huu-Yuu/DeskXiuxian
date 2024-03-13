#ifndef MAINCTRL_H
#define MAINCTRL_H

#include <QObject>
#include "modules/ui/mainui.h"
#include "modules/role/role_player.h"
#include "modules/logger/logger.h"
#include "modules/filedata/data_manage.h"
#include "modules/game_progress/game_progress.h"
#include "modules/item/item_manage.h"
#include "modules/server/tcp_client.h"

/**
 * @brief 主控程序
 */
class MainCtrl : public QObject
{
    Q_OBJECT
public:
    explicit MainCtrl(QObject* parent = nullptr);

    void StartFishing();

    ~MainCtrl();

    void ShowMainUi();  ///< 显示主界面

public slots:

    void SlotInitRoleData();    ///< 初始化角色信息
    void SlotStartFishing();    ///< 开始修仙
    void SlotStopFishing();     ///< 结束修仙

    /**
     * @brief 客户端信号错误处理函数
     * @param result：错误码
     * @return 无
     * @note：此函数用于综合处理通过信号发送的错误码。
     */
    void SlotDeviceResultDeal(int result, QJsonObject extra = QJsonObject());

signals:

    void SignalLogOut(QtMsgType type, const QMessageLogContext& context, const QString& message);   ///< 发送日志输出信号
    void SignalShowMsgToUI(QString msg);    ///< 发送消息到UI

private:

    void InitRoleInfo();    ///< 初始化角色信息（角色属性和角色UI），游戏上线后进行处理
    void InitRoleNetworkData(); ///< 初始化角色网络资料

    MainUI* main_ui_obj_;   ///< 角色UI类
    RolePlayer* role_obj_; ///< 角色系统对象
    Logger* logger_obj_;   ///< 日志管理器对象
    DataManage* data_file_;         ///< 文件管理对象
    GameProgress* game_obj_;    ///< 游戏进度控制对象
    ItemManage* role_item_;     ///< 角色道具
//    TcpClient* tcp_client_;

};

#endif // MAINCTRL_H

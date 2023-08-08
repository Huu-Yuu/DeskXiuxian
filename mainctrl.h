#ifndef MAINCTRL_H
#define MAINCTRL_H

#include <QObject>
#include "mainui.h"
#include "role/rolesystem.h"
#include "logger/logger.h"
#include "filedata/datamanage.h"
#include "game_progress/gameprogress.h"
#include "item/itemsystem.h"

/**
 * @brief 主控程序
 */
class MainCtrl : public QObject
{
    Q_OBJECT
public:
    explicit MainCtrl(QObject *parent = nullptr);

    void StartFishing();

    ~MainCtrl();

    /**
     * @brief 打印日志
     */
    void DebugOutToLog(QString msg);

    /**
     * @brief 显示主界面
     */
    void ShowMainUi();

signals:
    void SignalLogOut(QtMsgType type, const QMessageLogContext& context, const QString& message);

private:
    /**
     * @brief 初始化角色信息（角色属性和角色UI），游戏上线后进行处理
     */
    void InitRoleInfo();

    MainUI* ui_obj_;   // 角色UI类
    RoleSystem* role_obj_; // 角色系统对象
    Logger* logger_obj_;   // 日志管理器对象
    DataManage* data_file_;         // 文件管理对象
    GameProgress* game_obj_;    // 游戏进度控制对象
    ItemSystem* role_item_;     // 角色道具
};

#endif // MAINCTRL_H
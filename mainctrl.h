#ifndef MAINCTRL_H
#define MAINCTRL_H

#include <QObject>
#include "mainui.h"
#include "cultivation/cultivationsystem.h"
#include "role/rolesystem.h"
#include "logger/logger.h"
#include "filedata/datamanage.h"

/**
 * @brief 主控程序
 */
class MainCtrl : public QObject
{
    Q_OBJECT
public:
    explicit MainCtrl(QObject *parent = nullptr);

    void Init();

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
     * @brief 初始化角色信息
     */
    void InitRoleInfo();

    MainUI * ui_obj_;
    RoleSystem * role_obj_;
    Logger * logger_obj_;
    CultivationSystem * cul_obj_;
    DataManage *data_file_;
};

#endif // MAINCTRL_H

#ifndef CULTIVATIONSYSTEM_H
#define CULTIVATIONSYSTEM_H

#include <QObject>
#include "logger/logger.h"

/**
 * @brief 修为等级
 */
enum CultivationStage {
    LIANQI,
    ZHUJI,
    JIEDAN,
    YUANYING,
    HUASHEN,
    HETI,
    DACHENG,
    WUDAO,
    YUHUA,
    XIAN
};

/**
 * @brief 修为系统类
 */
class CultivationSystem
{

public:

    CultivationSystem();

    /**
     * @brief 设置修仙资质
     */
    void SetAptitude(int aptitude);

    /**
     * @brief 获取修仙资质
     */
    double GetAptitude();

    /**
     * @brief 生成减益事件
     */
    QString DebuffEvents(int rand, QString name, int money = 0, int exp = 0);

    /**
     * @brief 生成增益事件
     */
    QString BuffEvents(int rand, QString name, int money = 0, int exp = 0);

    /**
     * @brief EXP对应修仙等级
     */
    QString ExpToCulStage(int exp);

signals:

    void SignalLogOut(QtMsgType type, const QMessageLogContext& context, const QString& message);

public slots:

    /**
     * @brief Debuff随机事件生成槽函数
     */
    QString SlotDebuffRandomEvents(int rand, QString name, int money, int exp, int reputation);

    /**
     * @brief Buff随机事件生成槽函数
     */
    QString SlotBuffRandomEvents(int rand, QString name, int money, int exp, int reputation);

    /**
     * @brief 物品随机事件生成槽函数
     * @brief status 0-丢失， 1-获取
     */
    QString SlotObjectEvents(int rand, QString name, int status,int object);

private:
//    void DebugOutToLog(QString msg);
    double aptitude_;   // 修仙资质 0.01 ~ 1
    double need_epx_;   // 每次升级所需要的经验值
};

#endif // CULTIVATIONSYSTEM_H

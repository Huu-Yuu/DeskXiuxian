#include "cultivationsystem.h"

//CultivationSystem::CultivationSystem(QObject *parent) : QObject(parent)
//{
//    aptitude_ = 0;
//    need_epx_ = 300 * ( 1 - aptitude_);
//    logger_ = Logger::GetInstance();
//    QObject::connect(this, &CultivationSystem::SignalLogOut, logger_, &Logger::log);
//}

CultivationSystem::CultivationSystem()
{
    aptitude_ = 0;
    need_epx_ = 300 * ( 1 - aptitude_);
}

//void CultivationSystem::DebugOutToLog(QString msg)
//{
//    QString time_stamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm:ss");

//    QString display_text = time_stamp + "：" + msg;

    // 将消息记录到日志
//    emit SignalLogOut(QtDebugMsg, QMessageLogContext(), msg);
//}

void CultivationSystem::SetAptitude(int aptitude)
{
    aptitude_ = aptitude;
    QString msg = "当前资质为：" + QString::number(aptitude_);
    qDebug() << msg;
//    emit SignalLogOut(QtDebugMsg, QMessageLogContext(), msg);
}

double CultivationSystem::GetAptitude()
{
    return aptitude_;
}

QString CultivationSystem::DebuffEvents(int rand, QString name, int money, int exp)
{
    QString buff_tip,msg;
    if(money < 0)
    {
        buff_tip += "，灵石" + QString::number(money);
    }
    if(exp < 0)
    {
        buff_tip +="，经验值" + QString::number(exp);
    }
    switch (rand)
    {
    case 1:
    {
        msg = QString("%1惨遭恶人打劫%2").arg(name, buff_tip);
        break;
    }
    case 2:
    {
        msg = QString("%1闭关时候走火入魔%2").arg(name, buff_tip);
        break;
    }
    case 3:
    {
        msg = QString("%1探索秘境时遭遇了剧烈的毒雾%2").arg(name, buff_tip);
        break;
    }
    case 4:
    {
        msg = QString("%1被仇家施加了诅咒%2").arg(name, buff_tip);
        break;
    }
    case 5:
    {
        msg = QString("%1被恶劣天气影响，修炼出了岔子%2").arg(name, buff_tip);
        break;
    }
    case 6:
    {
        msg = QString("%1被仇家埋伏%2").arg(name, buff_tip);
        break;
    }
    case 7:
    {
        msg = QString("%1旁观道友渡劫时，被雷劫波及%2").arg(name, buff_tip);
        break;
    }
    case 8:
    {
        msg = QString("%1炼丹时炸炉%2").arg(name, buff_tip);
        break;
    }
    case 9:
    {
        msg = QString("%1被狐狸精吸走精气%2").arg(name, buff_tip);
        break;
    }
    case 10:
    {
        msg = QString("%1每日多次泄欲，纵欲过度%2").arg(name, buff_tip);
        break;
    }
    case 11:
    {
        msg = QString("%1购买丹药时遭遇诈骗%2").arg(name, buff_tip);
        break;
    }
    default:
    {
        msg = QString("%1疑似被作者修改数值%2").arg(name, buff_tip);
        break;
    }
    }
    return msg;
}

QString CultivationSystem::BuffEvents(int rand, QString name, int money, int exp)
{
    QString buff_tip,msg;
    if(money > 0)
    {
        buff_tip += "，灵石+" + QString::number(money);
    }
    if(exp > 0)
    {
        buff_tip +="，经验值+" + QString::number(exp);
    }
    switch (rand)
    {
    case 1:
    {
        msg = QString("%1得到了一本珍贵的秘籍，修为大增%2").arg(name,buff_tip);
        break;
    }
    case 2:
    {
        msg = QString("%1在山洞中发现了一块神秘的宝石，灵力大增%2").arg(name,buff_tip);
        break;
    }
    case 3:
    {
        msg = QString("%1参加武林大会，获得第一名%2").arg(name,buff_tip);
        break;
    }
    case 4:
    {
        msg = QString("%1参加武林大会，获得第一名%2").arg(name,buff_tip);
        break;
    }
    case 5:
    {
        msg = QString("%1遇到了一位神秘的长者，得到了一本传世武功秘笈，修为大幅提升%2").arg(name,buff_tip);
        break;
    }
    case 6:
    {
        msg = QString("%1在修炼中遇到了一位高人指点，修为突飞猛进%2").arg(name,buff_tip);
        break;
    }
    case 7:
    {
        msg = QString("%1在探险中发现了一座宝藏%2").arg(name,buff_tip);
        break;
    }
    case 8:
    {
        msg = QString("%1参与了一次激烈的战斗%2").arg(name,buff_tip);
        break;
    }
    case 9:
    {
        msg = QString("%1意外得到了一件传世宝物，实力大增%2").arg(name,buff_tip);
        break;
    }
    case 10:
    {
        msg = QString("%1遇到了仙人道场%2").arg(name,buff_tip);
        break;
    }
    case 11:
    {
        msg = QString("%1购买丹药时遇到诈骗团伙，成功出手制裁诈骗团伙%2").arg(name,buff_tip);
        break;
    }
    case 12:
    {
        msg = QString("%1购买丹药时遇到诈骗团伙，成功出手制裁诈骗团伙%2").arg(name,buff_tip);
        break;
    }
    case 13:
    {
        msg = QString("%1探索秘境，击杀妖兽%2").arg(name,buff_tip);
        break;
    }
    case 14:
    {
        msg = QString("%1完成悬赏任务%2").arg(name,buff_tip);
        break;
    }
    default:
    {
        msg = QString("%1疑似被作者修改数值%2").arg(name,buff_tip);
        break;
    }
    }
    return msg;
}

QString CultivationSystem::ExpToCulStage(int exp)
{
    need_epx_ = 300 * ( 1 - aptitude_);
    if(exp < 0)
    {
        return "凡人";
    }
    else if(exp > 0 && exp <= need_epx_ / 3)
    {
        return "练气期";
    }
    else if(exp > need_epx_ / 3 && exp <= need_epx_)
    {
        return "筑基期";
    }
    else if(exp > need_epx_ && exp <= 3 * need_epx_)
    {
        return "结丹期";
    }
    else if(exp > 3 * need_epx_ && exp <= 9 * need_epx_)
    {
        return "结丹期";
    }
    else if(exp > 9 * need_epx_ && exp <= 27 * need_epx_)
    {
        return "元婴期";
    }
    else if(exp > 27 * need_epx_ && exp <= 81 * need_epx_)
    {
        return "化神期";
    }
    else if(exp > 81 * need_epx_ && exp <= 3 * 81 * need_epx_)
    {
        return "合体期";
    }
    else if(exp > 3 * 81 * need_epx_ && exp <= 9 * 81 * need_epx_)
    {
        return "大乘期";
    }
    else if(exp > 9 * 81 * need_epx_ && exp <= 27 * 81 * need_epx_)
    {
        return "大乘期";
    }
    else if(exp > 27 * 81 * need_epx_ && exp <= 81 * 81 * need_epx_)
    {
        return "悟道期";
    }
    else if(exp > 81 * 81 * need_epx_ && exp <= 3 * 81 * 81 * need_epx_)
    {
        return "羽化期";
    }
    else if(exp > 3 * 81 * 81 * need_epx_ )
    {
        return "仙人";
    }
    else
    {
        return "BUG";
    }
}

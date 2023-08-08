#include "rolesystem.h"

QMutex RoleSystem::mutex;  // 初始化互斥锁对象
RoleSystem* RoleSystem::instance = nullptr;  // 初始化单例对象指针

RoleSystem* RoleSystem:: GetInstance()
{
    if (instance == nullptr)
    {
        QMutexLocker locker(&mutex);  // 加锁
        if (instance == nullptr)
        {
            instance = new RoleSystem; // 静态局部变量确保只创建一个实例
        }
    }
    return instance;
}

RoleSystem::RoleSystem()
{
    // 设置修仙资质
    aptitude_ = 0;
    need_epx_ = 300 * ( 1 - aptitude_);

    role_item_ = ItemSystem::GetInstance();
}

void RoleSystem::run()
{
    // 创建一个事件循环对象
    QEventLoop eventLoop;

    // 在事件循环中执行线程逻辑
    while (!m_stopRequested) {

        eventLoop.exec();
    }

    // 线程停止后执行清理工作
    // ...
    m_stopRequested = false;
}

QVariant RoleSystem::GetRoleTargetProperties(RoleUI tar_name)
{
    switch (tar_name)
    {
    case kUnknown:
        return "未知";
    case kRoleName:          // 昵称
        return role_name_;
    case kRoleLife:          // 寿命
        return role_life_;
    case kRolePrestige:      // 声望
        return role_prestige_;
    case kRoleCultivation:   // 修为
        return role_cultivation_;
    case kRoleExp:           // 经验值
        return role_exp_;
    case kRoleAgg:           // 攻击力
        return  role_agg_;
    case kRoleDef:           // 防御力
        return role_def_;
    case kRoleHp:            // 血量
        return role_hp_;
    case kAttMetal:          // 金
        return att_metal_;
    case kAttWood:           // 木
        return att_wood_;
    case kAttWater:          // 水
        return att_water_;
    case kAttFire:           // 火
        return att_fire_;
    case kAttEarth:          // 土
        return att_earth_;
    case kEquipWeapon:       // 武器
        return equip_weapon_;
    case kEquipMagic:        // 法宝
        return equip_magic_;
    case kEquipHelmet:       // 头盔
        return equip_helmet_;
    case kEquipClothing:     // 上衣
        return equip_clothing_;
    case kEquipBritches:     // 裤子
        return equip_britches_;
    case kEquipShoe:         // 鞋子
        return equip_shoe_;
    case kEquipJewelrt:      // 首饰
        return equip_jewelry_;
    }
    return 0;
}

QString RoleSystem::GetRoleName() const
{
    return role_name_;
}

void RoleSystem::SetRoleName(const QString& name)
{
    role_name_ = name;
}

double RoleSystem::GetRoleLife() const
{
    return role_life_;
}

void RoleSystem::SetRoleLife(double life)
{
    role_life_ = life;
}

int RoleSystem::GetRolePrestige() const
{
    return role_prestige_;
}

void RoleSystem::SetRolePrestige(int prestige)
{
    role_prestige_ = prestige;
}

QString RoleSystem::GetRoleCultivation() const
{
    return role_cultivation_;
}

void RoleSystem::SetRoleCultivation(const QString& cultivation)
{
    role_cultivation_ = cultivation;
}

int RoleSystem::GetRoleExp() const
{
    return role_exp_;
}

void RoleSystem::SetRoleExp(int exp)
{
    role_exp_ = exp;
}

int RoleSystem::GetRoleAgg() const
{
    return role_agg_;
}

void RoleSystem::SetRoleAgg(int agg)
{
    role_agg_ = agg;
}

int RoleSystem::GetRoleDef() const
{
    return role_def_;
}

void RoleSystem::SetRoleDef(int def)
{
    role_def_ = def;
}

int RoleSystem::GetRoleHp() const
{
    return role_hp_;
}

void RoleSystem::SetRoleHp(int hp)
{
    role_hp_ = hp;
}

int RoleSystem::GetAttMetal() const
{
    return att_metal_;
}

void RoleSystem::SetAttMetal(int metal)
{
    att_metal_ = metal;
}

int RoleSystem::GetAttWood() const
{
    return att_wood_;
}

void RoleSystem::SetAttWood(int wood)
{
    att_wood_ = wood;
}

int RoleSystem::GetAttWater() const
{
    return att_water_;
}

void RoleSystem::SetAttWater(int water)
{
    att_water_ = water;
}

int RoleSystem::GetAttFire() const
{
    return att_fire_;
}

void RoleSystem::SetAttFire(int fire)
{
    att_fire_ = fire;
}

int RoleSystem::GetAttEarth() const
{
    return att_earth_;
}

void RoleSystem::SetAttEarth(int earth)
{
    att_earth_ = earth;
}

QString RoleSystem::GetEquipWeapon() const
{
    return equip_weapon_;
}

void RoleSystem::SetEquipWeapon(const QString& weapon)
{
    equip_weapon_ = weapon;
}

QString RoleSystem::GetEquipMagic() const
{
    return equip_magic_;
}

void RoleSystem::SetEquipMagic(const QString& magic)
{
    equip_magic_ = magic;
}

QString RoleSystem::GetEquipHelmet() const
{
    return equip_helmet_;
}

void RoleSystem::SetEquipHelmet(const QString& helmet)
{
    equip_helmet_ = helmet;
}

QString RoleSystem::GetEquipClothing() const
{
    return equip_clothing_;
}

void RoleSystem::SetEquipClothing(const QString& clothing)
{
    equip_clothing_ = clothing;
}

QString RoleSystem::GetEquipBritches() const
{
    return equip_britches_;
}

void RoleSystem::SetEquipBritches(const QString& britches)
{
    equip_britches_ = britches;
}

QString RoleSystem::GetEquipShoe() const
{
    return equip_shoe_;
}

void RoleSystem::SetEquipShoe(const QString& shoe)
{
    equip_shoe_ = shoe;
}

QString RoleSystem::GetEquipJewelry() const
{
    return equip_jewelry_;
}

void RoleSystem::SetEquipJewelry(const QString& jewelry)
{
    equip_jewelry_ = jewelry;
}

void RoleSystem::stopThread()
{
    m_stopRequested = true;
}

void RoleSystem::SetAptitude(int aptitude)
{
    aptitude_ = aptitude;
    QString msg = "当前资质为：" + QString::number(aptitude_);
    qDebug() << msg;
    emit SignalShowMsgToUI(msg);
}

double RoleSystem::GetAptitude()
{
    return aptitude_;
}

QString RoleSystem::DebuffEvents(int rand, QString name, int money, int exp)
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

QString RoleSystem::BuffEvents(int rand, QString name, int money, int exp)
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

QString RoleSystem::ExpToCulStage(int exp)
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

void RoleSystem::SlotCyclicCultivation()
{
    int cur_event_probability = QRandomGenerator::global()->bounded(100);

    // 随机经验值，随机货币
    int money = 0;
    int exp = 0;
    QString msg ="";

    // 随机时间概率
    if(cur_event_probability <= 30)
    {
        // 减益事件
        money = QRandomGenerator::global()->bounded(-99,-1);
        exp = QRandomGenerator::global()->bounded(-10,-1);
        msg = DebuffEvents(QRandomGenerator::global()->bounded(15), role_name_, money, exp);
    }
    else if(cur_event_probability > 30 && cur_event_probability <= 100)
    {
        money = QRandomGenerator::global()->bounded(1,99);
        exp = QRandomGenerator::global()->bounded(1,10);
        msg = BuffEvents(QRandomGenerator::global()->bounded(20), role_name_, money, exp);
    }
    // 更新角色 经验值，货币
    role_exp_ += exp;
    role_item_->SetItemMoney(role_item_->GetItemMoney() + money);

    // 打包角色基本属性
    QJsonObject role_info_data;
    role_info_data.insert("roleName",role_name_);
    role_info_data.insert("roleLife",role_life_);
    role_info_data.insert("rolePrestige",role_prestige_);
    role_info_data.insert("roleCultivation",role_cultivation_);
    role_info_data.insert("roleExp",role_exp_);
    role_info_data.insert("roleAgg",role_agg_);
    role_info_data.insert("roleDef",role_def_);
    role_info_data.insert("roleHp",role_hp_);

    // 打包角色道具
    QJsonObject role_item_data;
    role_item_data.insert("roleName",role_name_);
    role_item_data.insert("roleMoney",role_item_->GetItemMoney());
    role_item_data.insert("renameCard",role_item_->GetItemRenameCard());

    // 发送信号，更新UI、数据库
    emit SignalShowMsgToUI(msg);
    emit SignalUpdateRoleInfoDatabase(role_info_data);
    emit SignalUpdateUI(kRoleExp, QString::number(role_exp_));
    emit SignalUpdateRoleItemDatabase(role_item_data);
}

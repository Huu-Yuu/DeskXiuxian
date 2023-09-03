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
    next_need_epx_ = 300 * ( 1 - aptitude_);

    // 设置渡劫概率加成
    RC_SurviveDisaster = 0;
    role_item_ = ItemSystem::GetInstance();
}

void RoleSystem::run()
{
    // 创建一个事件循环对象
    QEventLoop eventLoop;

    // 在事件循环中执行线程逻辑
    while (!m_stopRequested)
    {

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
            return role_LV_;
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
        case kEquipeMount:      // 坐骑
            return equip_mount_;
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

double RoleSystem::GetMaxRoleLife() const
{
    return role_max_life_;
}

void RoleSystem::UpdataMaxRoleLife()
{
    role_max_life_ = static_cast<int>(role_LV_) * 100 + ((static_cast<int>(role_LV_) + 1) ^ 3 ) / 2;
}

int RoleSystem::GetRolePrestige() const
{
    return role_prestige_;
}

void RoleSystem::SetRolePrestige(int prestige)
{
    role_prestige_ = prestige;
}

CultivationStage RoleSystem::GetRoleCultivation() const
{
    return role_LV_;
}

void RoleSystem::SetRoleCultivation(CultivationStage cultivation)
{
    role_LV_ = cultivation;
}

int RoleSystem::GetRoleExp() const
{
    return role_exp_;
}

void RoleSystem::SetRoleExp(int exp)
{
    role_exp_ = exp;
}

int RoleSystem::GetCurRoleExp()
{
    return role_cur_exp_;
}

void RoleSystem::SetCurRoleExp(int exp)
{
    role_cur_exp_ = exp;
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

void RoleSystem::SetLifeCoefficient(int life_coefficient)
{
    RC_Life_ = life_coefficient;
}

void RoleSystem::SetSurviveDisaster(int rc_survive_disaster)
{
    RC_SurviveDisaster = rc_survive_disaster;
}

int RoleSystem::GetLifeCoefficient()
{
    return RC_Life_;
}

QString RoleSystem::DebuffEvents(int rand, QString name, int money, int exp)
{
    QString buff_tip, msg;
    if(money < 0)
    {
        buff_tip += "，灵石" + QString::number(money);
    }
    if(exp < 0)
    {
        buff_tip += "，经验值" + QString::number(exp);
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
    QString buff_tip, msg;
    if(money > 0)
    {
        buff_tip += "，灵石+" + QString::number(money);
    }
    if(exp > 0)
    {
        buff_tip += "，经验值+" + QString::number(exp);
    }
    switch (rand)
    {
        case 1:
        {
            msg = QString("%1得到了一本珍贵的秘籍，修为大增%2").arg(name, buff_tip);
            break;
        }
        case 2:
        {
            msg = QString("%1在山洞中发现了一块神秘的宝石，灵力大增%2").arg(name, buff_tip);
            break;
        }
        case 3:
        {
            msg = QString("%1参加武林大会，获得第一名%2").arg(name, buff_tip);
            break;
        }
        case 4:
        {
            msg = QString("%1参加武林大会，获得第一名%2").arg(name, buff_tip);
            break;
        }
        case 5:
        {
            msg = QString("%1遇到了一位神秘的长者，得到了一本传世武功秘笈，修为大幅提升%2").arg(name, buff_tip);
            break;
        }
        case 6:
        {
            msg = QString("%1在修炼中遇到了一位高人指点，修为突飞猛进%2").arg(name, buff_tip);
            break;
        }
        case 7:
        {
            msg = QString("%1在探险中发现了一座宝藏%2").arg(name, buff_tip);
            break;
        }
        case 8:
        {
            msg = QString("%1参与了一次激烈的战斗%2").arg(name, buff_tip);
            break;
        }
        case 9:
        {
            msg = QString("%1意外得到了一件传世宝物，实力大增%2").arg(name, buff_tip);
            break;
        }
        case 10:
        {
            msg = QString("%1遇到了仙人道场%2").arg(name, buff_tip);
            break;
        }
        case 11:
        {
            msg = QString("%1购买丹药时遇到诈骗团伙，成功出手制裁诈骗团伙%2").arg(name, buff_tip);
            break;
        }
        case 12:
        {
            msg = QString("%1购买丹药时遇到诈骗团伙，成功出手制裁诈骗团伙%2").arg(name, buff_tip);
            break;
        }
        case 13:
        {
            msg = QString("%1探索秘境，击杀妖兽%2").arg(name, buff_tip);
            break;
        }
        case 14:
        {
            msg = QString("%1完成悬赏任务%2").arg(name, buff_tip);
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

QString RoleSystem::DebuffEvents3Att(int rand, QString name, int agg, int def, int hp)
{
    QString buff_tip;
    if(agg < 0)
    {
        buff_tip += "，攻击力" + QString::number(agg);
    }
    if(def < 0)
    {
        buff_tip += "，防御力" + QString::number(def);
    }
    if(hp < 0)
    {
        buff_tip += "，血量" + QString::number(hp);
    }
    switch (rand)
    {
        case 1:
            return  QString("%1闭关时候走火入魔%2").arg(name, buff_tip);
        case 2:
            return  QString("%1遭遇了仇人的诅咒%2").arg(name, buff_tip);
        case 3:
            return  QString("%1遭人暗算%2").arg(name, buff_tip);
        case 4:
            return  QString("%1寻宝时遇袭击%2").arg(name, buff_tip);
        case 5:
            return  QString("%1被徒弟殴打%2").arg(name, buff_tip);
        case 6:
            return  QString("%1挖人墓穴后，阴德受损%2").arg(name, buff_tip);
        case 7:
            return  QString("%1被道友告知，自己竟是沸羊羊%2").arg(name, buff_tip);
        case 8:
            return  QString("%1发现自己狂添的女神竟是土豪的玩物，如遭雷击%2").arg(name, buff_tip);
        case 9:
            return  QString("%1吃错了药%2").arg(name, buff_tip);
        case 10:
            return  QString("%1被道侣无情的抛弃，心情悲愤，狂吐鲜血%2").arg(name, buff_tip);
        default:
            return  QString("%1惨遭作者削弱%2").arg(name, buff_tip);
    }
}

QString RoleSystem::BuffEvents3Att(int rand, QString name, int agg, int def, int hp)
{
    QString buff_tip;
    if(agg > 0)
    {
        buff_tip += "，攻击力+" + QString::number(agg);
    }
    if(def > 0)
    {
        buff_tip += "，防御力+" + QString::number(def);
    }
    if(hp > 0)
    {
        buff_tip += "，血量+" + QString::number(hp);
    }
    switch (rand)
    {
        case 1:
            return  QString("%1救下神兽幼崽，被神兽长辈祝福%2").arg(name, buff_tip);
        case 2:
            return  QString("%1被道侣抛弃，内心更加坚定%2").arg(name, buff_tip);
        case 3:
            return  QString("%1狂舔女神，最终得逞%2").arg(name, buff_tip);
        case 4:
            return  QString("%1突然意识到自己是喜羊羊，心情大好%2").arg(name, buff_tip);
        case 5:
            return  QString("%1修炼的神功又进一步%2").arg(name, buff_tip);
        case 6:
            return  QString("%1随手完成了一桩宗门任务%2").arg(name, buff_tip);
        case 7:
            return  QString("%1挖人墓穴时获得墓主的残魂的指点%2").arg(name, buff_tip);
        case 8:
            return  QString("%1误入仙人秘境，心境获得提升%2").arg(name, buff_tip);
        case 9:
            return  QString("%1阅读典籍时顿悟%2").arg(name, buff_tip);
        case 10:
            return  QString("%1解救被盗贼包围的商队，获得商队赠礼%2").arg(name, buff_tip);
        default:
            return  QString("%1受到作者的青睐%2").arg(name, buff_tip);
    }
}

QString RoleSystem::GrowthEvents3Att(int rand, QString name, int agg, int def, int hp)
{
    QString buff_tip;
    if(agg > 0)
    {
        buff_tip += "，攻击力+" + QString::number(agg);
    }
    else if (agg < 0)
    {
        buff_tip += "，攻击力" + QString::number(agg);
    }

    if(def > 0)
    {
        buff_tip += "，防御力+" + QString::number(def);
    }
    else if(def < 0)
    {
        buff_tip += "，防御力" + QString::number(def);
    }
    if(hp > 0)
    {
        buff_tip += "，血量+" + QString::number(hp);
    }
    else if(hp < 0)
    {
        buff_tip += "，血量" + QString::number(hp);
    }
    switch (rand)
    {
        case 1:
            return QString("%1修炼了非本门功法%2").arg(name, buff_tip);
        case 2:
            return QString("%1探索了神秘道场%2").arg(name, buff_tip);
        case 3:
            return QString("%1听了一场高人讲道%2").arg(name, buff_tip);
        case 4:
            return QString("%1与道友论道%2").arg(name, buff_tip);
        case 5:
            return QString("%1与道侣双修%2").arg(name, buff_tip);
        case 6:
            return QString("%1心有所感%2").arg(name, buff_tip);
        case 7:
            return QString("%1服用了一颗没有说明书的丹药%2").arg(name, buff_tip);
        case 8:
            return QString("%1平时修炼懈怠，再次进入修炼状态时闪了腰%2").arg(name, buff_tip);
        case 9:
            return QString("%1跑路时被敌人追上%2").arg(name, buff_tip);
        case 10:
            return QString("%1与仇人大战三百回合未分胜负%2").arg(name, buff_tip);
        default:
            return QString("%1被作者淡淡的扫了一眼%2").arg(name, buff_tip);
    }

}

QString RoleSystem::GetCultivationName(CultivationStage cur_lv)
{
    switch (cur_lv)
    {
        case FANREN:
            return "凡人";
        case LIANQI:
            return "练气";
        case ZHUJI:
            return "筑基";
        case JIEDAN:
            return "结丹";
        case YUANYING:
            return "元婴";
        case HUASHEN:
            return "化神";
        case HETI:
            return "合体";
        case DACHENG:
            return "大乘";
        case WUDAO:
            return "悟道";
        case YUHUA:
            return "羽化";
        case XIAN:
            return "仙";
    }
    return "";
}

QString RoleSystem::GetCultivationName(int cur_lv)
{
    CultivationStage lv = static_cast<CultivationStage>(cur_lv);
    return  GetCultivationName(lv);
}

void RoleSystem::UpdateEextGradeEXP()
{
    // 获取经验值基数
    double exp_base = 3 * (static_cast<int>(role_LV_));
    // 算入角色资质得出下一次升级所需经验
    next_need_epx_ = exp_base * (1 - aptitude_) * 100 ;
}

bool RoleSystem::CheckExpIsUpgrade()
{
    if(role_LV_ == XIAN)
    {
        emit SignalShowMsgToUI("仙界大能已到世间修为尽头，无法继续突破");
        return false;
    }
    // 判断当前经验值是否满足下一级的条件
    if( role_cur_exp_ >= next_need_epx_)
    {
        emit SignalActivateCultivaUpButton();
        return true;
    }
    return false;
}

void RoleSystem::GetBreakthroughReward()
{
    // 判断角色当前的修为，当前修为越高获得的突破奖励就越高
    int agg = role_agg_;
    int def = role_def_;
    int hp = role_hp_;
    int prestige = role_prestige_;
    switch (role_LV_)
    {
        case FANREN:
        {
            role_agg_ < 50 ? role_agg_ = 50 :  role_agg_ += 20;
            role_def_ < 50 ? role_def_ = 50 :  role_def_ += 15;
            role_hp_ < 300 ? role_hp_ = 300 :  role_hp_ += 300;
            role_prestige_ < 50 ? role_prestige_ = 50 : role_prestige_ += 20;
            role_item_->GetItemMoney() < 50 ? role_item_->SetItemMoney(50) :  role_item_->SetItemMoney(100);
            emit SignalShowMsgToUI("恭喜道友渡劫成功！属性获得提升，灵石初始化为 100");
            return;;
        }
        case LIANQI:
        {
            role_agg_ < 100 ? role_agg_ = 100 :  role_agg_ += 50;
            role_def_ < 100 ? role_def_ = 100 :  role_def_ += 45;
            role_hp_ < 600 ? role_hp_ = 600 :  role_hp_ += 500;
            role_prestige_ < 50 ? role_prestige_ = 50 : role_prestige_ += 20;
            break;
        }
        case ZHUJI:
        {
            role_agg_ < 200 ? role_agg_ = 200 :  role_agg_ += 110;
            role_def_ < 200 ? role_def_ = 200 :  role_def_ += 90;
            role_hp_ < 1200 ? role_hp_ = 1200 :  role_hp_ += 1000;
            role_prestige_ += 60;
            break;
        }
        case JIEDAN:
        {
            role_agg_ < 600 ? role_agg_ = 600 :  role_agg_ += 440;
            role_def_ < 600 ? role_def_ = 600 :  role_def_ += 400;
            role_hp_ < 2550 ? role_hp_ = 2550 :  role_hp_ += 2700;
            role_prestige_ += 180;
            break;
        }
        case YUANYING:
        {
            role_agg_ < 1500 ? role_agg_ = 1500 :  role_agg_ += 1100;
            role_def_ < 1500 ? role_def_ = 1500 :  role_def_ += 1000;
            role_hp_ < 7000 ? role_hp_ = 7000 :  role_hp_ += 4000;
            role_prestige_ += 540;
            break;
        }
        case HUASHEN:
        {
            role_agg_ < 4000 ? role_agg_ = 4000 :  role_agg_ += 3400;
            role_def_ < 4000 ? role_def_ = 4000 :  role_def_ += 3000;
            role_hp_ < 22000 ? role_hp_ = 22000 :  role_hp_ += 12000;
            role_prestige_ += 1620;
            break;
        }
        case HETI:
        {
            role_agg_ < 10000 ? role_agg_ = 10000 :  role_agg_ += 9000;
            role_def_ < 10000 ? role_def_ = 10000 :  role_def_ += 8400;
            role_hp_ < 55000 ? role_hp_ = 55000 :  role_hp_ += 35000;
            role_prestige_ += 4860;
            break;
        }
        case DACHENG:
        {
            role_agg_ < 28000 ? role_agg_ = 28000 :  role_agg_ += 20000;
            role_def_ < 28000 ? role_def_ = 28000 :  role_def_ += 16000;
            role_hp_ < 80000 ? role_hp_ = 80000 :  role_hp_ += 50000;
            role_prestige_ += 14580;
            break;
        }
        case WUDAO:
        {
            role_agg_ < 70000 ? role_agg_ = 70000 :  role_agg_ += 55500;
            role_def_ < 70000 ? role_def_ = 70000 :  role_def_ += 48000;
            role_hp_ < 255000 ? role_hp_ = 255000 :  role_hp_ += 200000;
            role_prestige_ += 43740;
            break;
        }
        case YUHUA:
        {
            role_agg_ < 200000 ? role_agg_ = 200000 :  role_agg_ += 139200;
            role_def_ < 200000 ? role_def_ = 200000 :  role_def_ += 110200;
            role_hp_ < 800000 ? role_hp_ = 800000 :  role_hp_ += 700000;
            role_prestige_ += 131220;
            break;
        }
        case XIAN:
        default:
            emit SignalShowMsgToUI("突破出现错误，不改变属性值");
    }

    QString msg = "，攻击力+" + QString::number(role_agg_ - agg) + "，防御力+" +
                  QString::number(role_def_ - def) + "，血量+" + QString::number(role_hp_ - hp) + "，声望+" + QString::number(role_prestige_ - prestige);
    emit SignalShowMsgToUI("恭喜道友渡劫成功！属性获得大量提升" + msg);
    // 更新角色相关UI面板
    emit SignalUpdateUI(kRoleAgg, QString::number(role_agg_));
    emit SignalUpdateUI(kRoleDef, QString::number(role_def_));
    emit SignalUpdateUI(kRoleHp, QString::number(role_hp_));
    emit SignalUpdateUI(kRolePrestige, QString::number(role_prestige_));
}

void RoleSystem::GetBreakthroughPenalty()
{
    // 损失的属性
    int loss_agg = 0;
    int loss_def = 0;
    int loss_hp = 0;
    int loss_exp = 0;
    switch (role_LV_)
    {
        case FANREN:
        {
            loss_agg = QRandomGenerator::global()->bounded(10) + 1;
            loss_def = QRandomGenerator::global()->bounded(10) + 1;
            loss_hp = QRandomGenerator::global()->bounded(20) + 1;
            loss_exp = QRandomGenerator::global()->bounded(static_cast<int>(next_need_epx_ / 6) , static_cast<int>(next_need_epx_ / 5)) + 1;
            break;
        }
        case LIANQI:
        {
            loss_agg = QRandomGenerator::global()->bounded(20) + 1;
            loss_def = QRandomGenerator::global()->bounded(20) + 1;
            loss_hp = QRandomGenerator::global()->bounded(100) + 1;
            loss_exp = QRandomGenerator::global()->bounded(static_cast<int>(next_need_epx_ / 5.5) , static_cast<int>(next_need_epx_ / 4)) + 1;
            break;
        }
        case ZHUJI:
        {
            loss_agg = QRandomGenerator::global()->bounded(50) + 1;
            loss_def = QRandomGenerator::global()->bounded(50) + 1;
            loss_hp = QRandomGenerator::global()->bounded(400) + 1;
            loss_exp = QRandomGenerator::global()->bounded(static_cast<int>(next_need_epx_ / 5) , static_cast<int>(next_need_epx_ / 4)) + 1;
            break;
        }
        case JIEDAN:
        {
            loss_agg = QRandomGenerator::global()->bounded(110) + 1;
            loss_def = QRandomGenerator::global()->bounded(110) + 1;
            loss_hp = QRandomGenerator::global()->bounded(1000) + 1;
            loss_exp = QRandomGenerator::global()->bounded(static_cast<int>(next_need_epx_ / 4.5) , static_cast<int>(next_need_epx_ / 3)) + 1;
            break;
        }
        case YUANYING:
        {
            loss_agg = QRandomGenerator::global()->bounded(300) + 1;
            loss_def = QRandomGenerator::global()->bounded(290) + 1;
            loss_hp = QRandomGenerator::global()->bounded(1500) + 1;
            loss_exp = QRandomGenerator::global()->bounded(static_cast<int>(next_need_epx_ / 4) , static_cast<int>(next_need_epx_ / 3)) + 1;
            break;
        }
        case HUASHEN:
        {
            loss_agg = QRandomGenerator::global()->bounded(990) + 1;
            loss_def = QRandomGenerator::global()->bounded(990) + 1;
            loss_hp = QRandomGenerator::global()->bounded(2200) + 1;
            loss_exp = QRandomGenerator::global()->bounded(static_cast<int>(next_need_epx_ / 4) , static_cast<int>(next_need_epx_ / 2.5)) + 1;
            break;
        }
        case HETI:
        {
            loss_agg = QRandomGenerator::global()->bounded(2000) + 1;
            loss_def = QRandomGenerator::global()->bounded(2000) + 1;
            loss_hp = QRandomGenerator::global()->bounded(5500) + 1;
            loss_exp = QRandomGenerator::global()->bounded(static_cast<int>(next_need_epx_ / 3.5) , static_cast<int>(next_need_epx_ / 2.5)) + 1;
            break;
        }
        case DACHENG:
        {
            loss_agg = QRandomGenerator::global()->bounded(5000) + 1;
            loss_def = QRandomGenerator::global()->bounded(5000) + 1;
            loss_hp = QRandomGenerator::global()->bounded(8500) + 1;
            loss_exp = QRandomGenerator::global()->bounded(static_cast<int>(next_need_epx_ / 3.2) , static_cast<int>(next_need_epx_ / 2.5)) + 1;
            break;
        }
        case WUDAO:
        {
            loss_agg = QRandomGenerator::global()->bounded(9000) + 1;
            loss_def = QRandomGenerator::global()->bounded(9000) + 1;
            loss_hp = QRandomGenerator::global()->bounded(15500) + 1;
            loss_exp = QRandomGenerator::global()->bounded(static_cast<int>(next_need_epx_ / 3) , static_cast<int>(next_need_epx_ / 2.5)) + 1;
            break;
        }
        case YUHUA:
        {
            loss_agg = QRandomGenerator::global()->bounded(11000) + 1;
            loss_def = QRandomGenerator::global()->bounded(11000) + 1;
            loss_hp = QRandomGenerator::global()->bounded(25500) + 1;
            loss_exp = QRandomGenerator::global()->bounded(static_cast<int>(next_need_epx_ / 2.5) , static_cast<int>(next_need_epx_ / 2)) + 1;
            break;
        }
        case XIAN:
        default:
            emit SignalShowMsgToUI("突破出现错误，不改变属性值");
            break;
    }
    role_agg_ -= loss_agg;
    role_def_ -= loss_def;
    role_hp_ -= loss_hp;
    role_cur_exp_ -= loss_exp;
    QString msg = "，攻击力-" + QString::number(loss_agg) + "，防御力-" +
                  QString::number(loss_def) + "，血量-" + QString::number(loss_hp) + "，经验值-"  +  QString::number(loss_exp);
    emit SignalShowMsgToUI("道友渡劫失败，被雷劫击伤，身体被重创" + msg);
    // 更新角色相关UI面板
    emit SignalUpdateUI(kRoleAgg, QString::number(role_agg_));
    emit SignalUpdateUI(kRoleDef, QString::number(role_def_));
    emit SignalUpdateUI(kRoleHp, QString::number(role_hp_));
}

bool RoleSystem::SurviveDisaster()
{
    // 根据当前修为不同，突破成功率不同
    int rc = QRandomGenerator::global()->bounded(100) + 1;
    switch (role_LV_)
    {
        case FANREN:
        {
            if(rc <= 99 + RC_SurviveDisaster)
                return true;
            else
                return false;
        }
        case LIANQI:
        {
            if(rc <= 95 + RC_SurviveDisaster)
                return true;
            else
                return false;
        }
        case ZHUJI:
        {
            if(rc <= 85 + RC_SurviveDisaster)
                return true;
            else
                return false;
        }
        case JIEDAN:
        {
            if(rc <= 80 + RC_SurviveDisaster)
                return true;
            else
                return false;
        }
        case YUANYING:
        {
            if(rc <= 70 + RC_SurviveDisaster)
                return true;
            else
                return false;
        }
        case HUASHEN:
        {
            if(rc <= 60 + RC_SurviveDisaster)
                return true;
            else
                return false;
        }
        case HETI:
        {
            if(rc <= 50 + RC_SurviveDisaster)
                return true;
            else
                return false;
        }
        case DACHENG:
        {
            if(rc <= 40 + RC_SurviveDisaster)
                return true;
            else
                return false;
        }
        case WUDAO:
        {
            if(rc <= 30 + RC_SurviveDisaster)
                return true;
            else
                return false;
        }
        case YUHUA:
        {
            if(rc <= 20 + RC_SurviveDisaster)
                return true;
            else
                return false;
        }
        case XIAN:
        {
            if(rc <= 10 + RC_SurviveDisaster)
                return true;
            else
                return false;
        }
        default:
            return false;
    }
    return false;
}

void RoleSystem::UpdateAllUI()
{
    emit SignalUpdateUI(kRoleName, role_name_);
    emit SignalUpdateUI(kRoleLife, QString::number(role_life_));
    emit SignalUpdateUI(kRoleCultivation, GetCultivationName(role_LV_));
    emit SignalUpdateUI(kRoleExp, QString::number(role_cur_exp_));
    emit SignalUpdateUI(kRoleAgg, QString::number(role_agg_));
    emit SignalUpdateUI(kRoleDef, QString::number(role_def_));
    emit SignalUpdateUI(kRoleHp, QString::number(role_hp_));
    emit SignalUpdateUI(kRolePrestige, QString::number(role_prestige_));
}

void RoleSystem::SaveRoleInfo()
{
    // 打包角色基本属性
    QJsonObject role_info_data;
    role_info_data.insert("roleName", role_name_);
    role_info_data.insert("roleLife", role_life_);
    role_info_data.insert("rolePrestige", role_prestige_);
    role_info_data.insert("roleLv", static_cast<int>(role_LV_));
    role_info_data.insert("roleCurExp", role_cur_exp_);
    role_info_data.insert("roleExp", role_exp_);
    role_info_data.insert("roleAgg", role_agg_);
    role_info_data.insert("roleDef", role_def_);
    role_info_data.insert("roleHp", role_hp_);
    // 发送更新数据库信号
    emit SignalUpdateRoleInfoDatabase(role_info_data);
}

void RoleSystem::SaveRoleItem()
{
    // 打包角色道具
    QJsonObject role_item_data;
    role_item_data.insert("roleName", role_name_);
    role_item_data.insert("roleMoney", role_item_->GetItemMoney());
    role_item_data.insert("renameCard", role_item_->GetItemRenameCard());
    // 发送更新角色道具数据库信号
    emit SignalUpdateRoleItemDatabase(role_item_data);
}

void RoleSystem::SaveCoefficient()
{
    // 打包角色属性系数
    QJsonObject role_coefficient_data;
    role_coefficient_data.insert("roleName", role_name_);
    role_coefficient_data.insert("RCLife", RC_Life_);
    role_coefficient_data.insert("RCBasicEvent", 1);
    role_coefficient_data.insert("RCAttEvent", 1);
    role_coefficient_data.insert("RCSurviveDisaster", RC_SurviveDisaster);
    role_coefficient_data.insert("RCPrestigeEvent", 1);
    role_coefficient_data.insert("RCSpecialEvent", 1);
    role_coefficient_data.insert("roleAptitude", 1);
    // 发送更新角色属性系数数据库信号
    emit SignalUpdateRoleCoefficientDatabase(role_coefficient_data);
}

void RoleSystem::SlotLifeUpdata()
{
    RC_Life_++;
    if(RC_Life_ >= 7200)
    {
        RC_Life_ -= 7200;
        role_life_ ++;
        emit SignalUpdateUI(kRoleLife, QString::number(role_life_));
        if(role_life_ >= role_max_life_ - 4)
        {
            emit SignalShowMsgToUI(QString("%1道友大限将至，请抓紧突破以增加寿命！").arg(role_name_));
            return;
        }
        if(role_life_ >= role_max_life_)
        {
            emit SignalShowMsgToUI(QString("%1道友大限已至享龄%2岁，让我们怀念与他共度的美好时光，他的存在将永远在我们心中闪耀！").arg(role_name_, static_cast<int>(role_life_)));
            return;
        }
    }
}

void RoleSystem::SlotUpgradeLevel()
{
    QString msg;
    if(!SurviveDisaster())
    {
        // 渡劫失败 处罚
        GetBreakthroughPenalty();
        RC_SurviveDisaster ++;
        msg = "很遗憾，" + role_name_ + "道友渡劫失败，望道友厚积薄发再渡天劫！下次突破成功率加1";
    }
    else
    {
        // 渡劫成功
        RC_SurviveDisaster = 0;
        int next_lv = static_cast<int>(role_LV_);
        next_lv++;
        role_LV_ = static_cast<CultivationStage>(next_lv);
        role_cur_exp_ -= next_need_epx_;
        // 获得突破奖励
        GetBreakthroughReward();
        msg = "恭喜" + role_name_ + "道友渡过雷劫，世间又多一位" + GetCultivationName(role_LV_) + "大能";
    }
    UpdateEextGradeEXP();
    UpdateAllUI();
    SaveRoleInfo();
    SaveRoleItem();
    SaveCoefficient();
    emit SignalShowMsgToUI(msg);
    emit SignalDisableCultivaUpButton();

    // 判断经验值是否还满足升级条件
    if(!CheckExpIsUpgrade())
    {
        emit SignalDisableCultivaUpButton();
    }
}

void RoleSystem::SlotCyclicCultivation()
{
    // 当前事件随机数
    int cur_event_probability = QRandomGenerator::global()->bounded(100);

    // 随机经验值，随机货币
    int money = 0;
    int exp = 0;
    QString msg = "";

    // 随机时间概率
    if(cur_event_probability <= 30)
    {
        // 减益事件
        money = QRandomGenerator::global()->bounded(-99, -1);
        exp = QRandomGenerator::global()->bounded(-10, -1);
        msg = DebuffEvents(QRandomGenerator::global()->bounded(15), role_name_, money, exp);
    }
    else if(cur_event_probability > 30 && cur_event_probability <= 100)
    {
        money = QRandomGenerator::global()->bounded(1, 99);
        exp = QRandomGenerator::global()->bounded(1, 10);
        msg = BuffEvents(QRandomGenerator::global()->bounded(20), role_name_, money, exp);
    }

    // 更新角色 经验值，货币
    role_exp_ += exp;
    role_cur_exp_ += exp;
    if(role_cur_exp_ < 0)
    {
        role_cur_exp_ = 0;
    }
    CheckExpIsUpgrade();

    // 更新角色道具
    role_item_->SetItemMoney(role_item_->GetItemMoney() + money);

    // 更新角色基本信息数据库
    SaveRoleInfo();

    // 更新角色道具数据库
    SaveRoleItem();

    // 更新角色属性系数数据库
    SaveCoefficient();

    // 发送信号，发送事件信息，更新UI、数据库
    emit SignalShowMsgToUI(msg);

    emit SignalUpdateUI(kRoleExp, QString::number(role_cur_exp_));
}

void RoleSystem::SlotCyclicEnhanceAtt()
{
    // 当前事件随机数
    int cur_event_probability = QRandomGenerator::global()->bounded(100) + 1 ;

    // 随机攻击力、防御力、HP
    int agg = 0;
    int def = 0;
    int hp = 0;
    QString msg = "";

    // 随机时间概率
    if(cur_event_probability <= 1)
    {
        // 超级减益事件   三属性同时下降
        agg = QRandomGenerator::global()->bounded(-99, -2);
        def = QRandomGenerator::global()->bounded(-90, -2);
        hp = QRandomGenerator::global()->bounded(-200, -2);
        msg = DebuffEvents3Att(QRandomGenerator::global()->bounded(15), role_name_, agg, def, hp);
    }
    else if(cur_event_probability > 1 && cur_event_probability <= 3)
    {
        // 超级增益事件   三属性同时提升
        agg = QRandomGenerator::global()->bounded(5, 99);
        def = QRandomGenerator::global()->bounded(2, 99);
        hp = QRandomGenerator::global()->bounded(30, 200);
        msg = BuffEvents3Att(QRandomGenerator::global()->bounded(15), role_name_, agg, def, hp);
    }
    else if(cur_event_probability > 3 && cur_event_probability <= 8)
    {
        // 减益事件
        agg = QRandomGenerator::global()->bounded(-50, -10);
        def = QRandomGenerator::global()->bounded(-50, -10);
        hp = QRandomGenerator::global()->bounded(-100, -30);
        msg = DebuffEvents3Att(QRandomGenerator::global()->bounded(15), role_name_, agg, def, hp);
    }
    else if(cur_event_probability > 8 && cur_event_probability <= 15)
    {
        // 增益事件
        agg = QRandomGenerator::global()->bounded(15, 60);
        def = QRandomGenerator::global()->bounded(15, 60);
        hp = QRandomGenerator::global()->bounded(35, 110);
        msg = BuffEvents3Att(QRandomGenerator::global()->bounded(15), role_name_, agg, def, hp);
    }
    else if(cur_event_probability > 15 && cur_event_probability <= 60)
    {
        // 稍减益
        agg = QRandomGenerator::global()->bounded(-20, 35);
        def = QRandomGenerator::global()->bounded(-20, 35);
        hp = QRandomGenerator::global()->bounded(-40, 70);
        msg = GrowthEvents3Att(QRandomGenerator::global()->bounded(15), role_name_, agg, def, hp);
    }
    else if(cur_event_probability > 60 && cur_event_probability <= 75)
    {
        // 单独减益事件
        if(cur_event_probability % 3 == 0)
        {
            agg = QRandomGenerator::global()->bounded(-20, -3);
        }
        else if(cur_event_probability % 3 == 1)
        {
            def = QRandomGenerator::global()->bounded(-20, -3);
        }
        else
        {
            hp = QRandomGenerator::global()->bounded(-70, -10);
        }
        msg = DebuffEvents3Att(QRandomGenerator::global()->bounded(15), role_name_, agg, def, hp);
    }
    else if(cur_event_probability > 75 && cur_event_probability <= 100)
    {
        // 单独增益事件
        if(cur_event_probability % 3 == 0)
        {
            agg = QRandomGenerator::global()->bounded(3, 30);
        }
        else if(cur_event_probability % 3 == 1)
        {
            def = QRandomGenerator::global()->bounded(3, 30);
        }
        else
        {
            hp = QRandomGenerator::global()->bounded(20, 80);
        }
        msg = BuffEvents3Att(QRandomGenerator::global()->bounded(15), role_name_, agg, def, hp);
    }

    // 计算属性 防止属性变为负数
    role_agg_ += agg;
    role_def_ += def;
    role_hp_ += hp;
    if(role_agg_ <= 0)
    {
        role_agg_ = 0;
    }
    if(role_def_ <= 0)
    {
        role_def_ = 0;
    }
    if(role_hp_ <= 0)
    {
        role_hp_ = 0;
    }

    // 更新数据库
    SaveRoleInfo();
    // 发送信号，发送事件信息，更新UI
    emit SignalShowMsgToUI(msg);
    emit SignalUpdateUI(kRoleAgg, QString::number(role_agg_));
    emit SignalUpdateUI(kRoleDef, QString::number(role_def_));
    emit SignalUpdateUI(kRoleHp, QString::number(role_hp_));
}

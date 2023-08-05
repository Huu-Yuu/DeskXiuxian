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

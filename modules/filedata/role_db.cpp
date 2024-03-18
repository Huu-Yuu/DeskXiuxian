#include "role_db.h"

RoleInfoTable::RoleInfoTable() {

}

RoleInfoTable::~RoleInfoTable() {

}

RoleInfoTable::RoleInfoTable(const RoleInfoTable &other) {
    this->role_name = other.role_name;
    this->role_life = other.role_life;
    this->role_prestige = other.role_prestige;
    this->role_exp = other.role_exp;
    this->role_cur_exp = other.role_cur_exp;
    this->role_agg = other.role_agg;
    this->role_def = other.role_def;
    this->role_hp = other.role_hp;
    this->role_lv = other.role_lv;
}

QJsonObject RoleInfoTable::ToJson() const {
    QJsonObject result;
    result.insert("role_name", role_name);
    result.insert("role_life", role_life);
    result.insert("role_prestige", role_prestige);
    result.insert("role_exp", role_exp);
    result.insert("role_cur_exp", role_cur_exp);
    result.insert("role_agg", role_agg);
    result.insert("role_def", role_def);
    result.insert("role_hp", role_hp);
    result.insert("role_lv", role_lv);
    return result;
}

void RoleInfoTable::FromJson(const QJsonObject &task_obj) {
    role_name = task_obj.value("role_name").toString();
    role_life = task_obj.value("role_life").toString();
    role_prestige = task_obj.value("role_prestige").toString();
    role_exp = task_obj.value("role_exp").toString();
    role_cur_exp = task_obj.value("role_cur_exp").toString();
    role_agg = task_obj.value("role_agg").toString();
    role_def = task_obj.value("role_def").toString();
    role_hp = task_obj.value("role_hp").toString();
    role_lv = task_obj.value("role_lv").toString();
}

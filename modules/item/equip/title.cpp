#include "title.h"

Title_LSHS::Title_LSHS()
{
    item_index_ = kTitleLeShanHaoShi;
    item_name_ = "乐善好施";
    item_explain_ = "每天捐款的大好人";
    item_type_ = kItemEquip;
    item_price_ = 100;
    area = kTitleArea;
    def_ = 5;
    hp_ = 20;
    prestige_ = 5;
}

Title_CJCE::Title_CJCE() {
    item_index_ = kTitleChengJianChuE;
    item_name_ = "惩奸除恶";
    item_explain_ = "每天清理一遍盗贼";
    item_type_ = kItemEquip;
    item_price_ = 100;
    area = kTitleArea;
    def_ = 7;
    hp_ = 30;
    prestige_ = 7;
}

bool Title_CJCE::CanUpgrade() {
    if(Title_LSHS::getInstance()->GetItemNum() > 0)
    {
        return true;
    }
    return false;
}

void Title_CJCE::EquipUpgrade() {
    if(CanUpgrade())
    {
        Title_LSHS::getInstance()->IncrementItem(-1);
        this->IncrementItem(-1);
        Title_CEYS::getInstance()->ItemNumCharge(1, kSyntEquip);
    }
}

Title_CEYS::Title_CEYS() {
    item_index_ = kTitleChengEYangShan;
    item_name_ = "惩恶扬善";
    item_explain_ = "每天清理一遍盗贼和捐款";
    item_type_ = kItemEquip;
    item_price_ = 200;
    area = kTitleArea;
    def_ = 12;
    hp_ = 50;
    prestige_ = 12;
}

#ifndef DESKXIUXINA_TITLE_H
#define DESKXIUXINA_TITLE_H
#include "common/singleton.h"
#include "../itembase.h"
#include <QObject>

class Title_LSHS : public ItemBase
{
    Q_OBJECT
    SINGLETON(Title_LSHS);
public:
    Title_LSHS();
};

class Title_CJCE : public ItemBase
{
    Q_OBJECT
    SINGLETON(Title_CJCE);
public:
    Title_CJCE();
    bool CanUpgrade() override;
    void EquipUpgrade() override;
};

// 惩恶扬善 = 惩奸除恶 + 乐善好施
class Title_CEYS : public  ItemBase
{
    Q_OBJECT
    SINGLETON(Title_CEYS);
public:
    Title_CEYS();
};

#endif //DESKXIUXINA_TITLE_H

#ifndef DESKXIUXINA_PROP_RENAME_CARD_H
#define DESKXIUXINA_PROP_RENAME_CARD_H
#include <QObject>
#include "common/singleton.h"
#include "modules/item/itembase.h"

class RenameCard : public ItemBase
{
    Q_OBJECT
public:
    SINGLETON(RenameCard);
    RenameCard();
    ~RenameCard();

private:

};
#endif //DESKXIUXINA_PROP_RENAME_CARD_H

#ifndef DESKXIUXINA_PROP_YANSHOUDAN10_H
#define DESKXIUXINA_PROP_YANSHOUDAN10_H
#include <QObject>
#include "common/singleton.h"
#include "../itembase.h"
class YanshouDan10 : public ItemBase
{
    Q_OBJECT
public:
    SINGLETON(YanshouDan10);
    YanshouDan10();
    ~YanshouDan10();
protected:

private:
};


#endif //DESKXIUXINA_PROP_YANSHOUDAN10_H

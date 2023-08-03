#ifndef CULTIVATIONSYSTEM_H
#define CULTIVATIONSYSTEM_H

#include <QObject>

enum CultivationStage {
    LIANQI,
    ZHUJI,
    JIEDAN,
    YUANYING,
    HUASHEN,
    HETI,
    DACHENG,
    WUDAO,
    YUNHUA,
    XIAN
};

/**
 * @brief 修为系统类
 */
class CultivationSystem
{

public:
    CultivationSystem();
};

#endif // CULTIVATIONSYSTEM_H

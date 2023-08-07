#ifndef ITEMSYSTEM_H
#define ITEMSYSTEM_H

#include <QObject>


/**
 * @brief 物品系统类
 */
class ItemSystem : public QObject
{
    Q_OBJECT
public:
    explicit ItemSystem(QObject *parent = nullptr);

signals:

};

#endif // ITEMSYSTEM_H

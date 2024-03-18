#ifndef DESKXIUXINA_BASETABLE_H
#define DESKXIUXINA_BASETABLE_H
#include <QSqlDatabase>
#include "common/singleton.h"
#include "3rdparty/include/QxOrm/include/QxPrecompiled.h"
#include "3rdparty/include/QxOrm/include/QxOrm.h"
#include "3rdparty/include/QxOrm/include/QxRegister/QxRegister.h"
#include "3rdparty/include/QxOrm/include/QxTraits/get_base_class.h"

class BaseTable
{
public:
    BaseTable();
    BaseTable(const BaseTable& other);
    BaseTable& operator= (const BaseTable& other);
    virtual ~BaseTable();

    void onBeforeInsert(qx::dao::detail::IxDao_Helper* dao);
    void onBeforeUpdate(qx::dao::detail::IxDao_Helper* dao);

    QString getUpdate_time() const
    {
        return update_time;
    }
    QString getCreate_time() const
    {
        return create_time;
    }
    void setUpdate_time(const QString& s)
    {
        update_time = s;
    }
    void setCreate_time(const QString& s)
    {
        create_time = s;
    }
public:
    QString update_time;
    QString create_time;
};

//QX_REGISTER_PRIMARY_KEY(BaseTable, QString)
QX_REGISTER_ABSTRACT_CLASS(BaseClassTrigger);
QX_REGISTER_HPP_IMPORT_DLL(BaseTable, qx::trait::no_base_class_defined, 1);


namespace qx
{
    namespace dao
    {
        namespace detail
        {

            template <>
            struct QxDao_Trigger<BaseTable>
            {

                static inline void onBeforeInsert(BaseTable* t, qx::dao::detail::IxDao_Helper* dao)
                {
                    if(t)
                    {
                        t->onBeforeInsert(dao);
                    }
                }
                static inline void onBeforeUpdate(BaseTable* t, qx::dao::detail::IxDao_Helper* dao)
                {
                    if(t)
                    {
                        t->onBeforeUpdate(dao);
                    }
                }
                static inline void onBeforeDelete(BaseTable* t, qx::dao::detail::IxDao_Helper* dao)
                {
                    Q_UNUSED(t);
                    Q_UNUSED(dao);
                }
                static inline void onBeforeFetch(BaseTable* t, qx::dao::detail::IxDao_Helper* dao)
                {
                    Q_UNUSED(t);
                    Q_UNUSED(dao);
                }
                static inline void onAfterInsert(BaseTable* t, qx::dao::detail::IxDao_Helper* dao)
                {
                    Q_UNUSED(t);
                    Q_UNUSED(dao);
                }
                static inline void onAfterUpdate(BaseTable* t, qx::dao::detail::IxDao_Helper* dao)
                {
                    Q_UNUSED(t);
                    Q_UNUSED(dao);
                }
                static inline void onAfterDelete(BaseTable* t, qx::dao::detail::IxDao_Helper* dao)
                {
                    Q_UNUSED(t);
                    Q_UNUSED(dao);
                }
                static inline void onAfterFetch(BaseTable* t, qx::dao::detail::IxDao_Helper* dao)
                {
                    Q_UNUSED(t);
                    Q_UNUSED(dao);
                }

            };

        } // namespace detail
    } // namespace dao
} // namespace qx


#endif //DESKXIUXINA_BASETABLE_H

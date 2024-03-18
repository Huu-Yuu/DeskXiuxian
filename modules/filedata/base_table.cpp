//#include "base_table.h"
//QX_REGISTER_CPP_IMPORT_DLL(BaseTable)
//
//
//namespace qx
//{
//    template <> void register_class(QxClass<BaseTable>& t)
//    {
//        t.data(&BaseTable::update_time, "update_time");
//        t.data(&BaseTable::create_time, "create_time");
//    }
//}
//
//BaseTable::BaseTable()
//{
//
//}
//
//BaseTable::BaseTable(const BaseTable& other)
//{
//    this->update_time = other.update_time;
//    this->create_time = other.create_time;
//}
//
//BaseTable& BaseTable::operator=(const BaseTable& other)
//{
//    this->update_time = other.update_time;
//    this->create_time = other.create_time;
//    return *this;
//}
//
//BaseTable::~BaseTable()
//{
//
//}
//
//void BaseTable::onBeforeInsert(qx::dao::detail::IxDao_Helper* dao)
//{
//    Q_UNUSED(dao);
//    update_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
//    create_time = update_time;
//}
//
//void BaseTable::onBeforeUpdate(qx::dao::detail::IxDao_Helper* dao)
//{
//    Q_UNUSED(dao);
//
//    update_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
//    create_time = this->create_time;
//}
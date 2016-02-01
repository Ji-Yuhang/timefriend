#include "eventtimemodel.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
class EventTimeModelPrivate {
public:
    EventTimeModelPrivate(){}
    virtual ~EventTimeModelPrivate(){}
    virtual int                                 add(EventTimeModel::Data data) = 0;
    virtual int                                 del(QString uuid) = 0;
    virtual int                                 update(QString uuid, EventTimeModel::Data data) = 0;
    virtual QMap<QString, EventTimeModel::Data> selectAll() = 0;
protected:
    QMap<QString, EventTimeModel::Data> data_;
};

class SqliteDatabase : public EventTimeModelPrivate {
public:
    SqliteDatabase();
    ~SqliteDatabase();
    virtual int                                 add(EventTimeModel::Data data);
    virtual int                                 del(QString uuid);
    virtual int                                 update(QString uuid, EventTimeModel::Data data);
    virtual QMap<QString, EventTimeModel::Data> selectAll();
private:
    bool initDB();
    QSqlDatabase db_;
};

SqliteDatabase::SqliteDatabase()
{
    if (!initDB()) {
        qDebug() << "cannot read data from sqlite database";
    }
}

SqliteDatabase::~SqliteDatabase()
{

}

bool SqliteDatabase::initDB()
{
    data_.clear();
    db_ = QSqlDatabase::addDatabase("QSQLITE","local_timefriend");
    db_.setDatabaseName("timefriend.db");
    if (db_.open()) {
        QString sql = "select * from eventtime;";
        QSqlQuery query(db_);
        if (query.exec(sql) ) {
            while (query.next()) {
                EventTimeModel::Data data;
                data.uuid = query.value("eventtimeid").toString();
                data.userID = query.value("userid").toInt();
                data.beginTime = query.value("begintime").toDateTime();
                data.endTime = query.value("endtime").toDateTime();
                data.length = query.value("timelength").toInt();
                data.typeUuid = query.value("typeid").toString();
                data.tag = query.value("tag").toString();
                data.text = query.value("text").toString();
                data.addTime = query.value("addtime").toDateTime();
                data.updateTime = query.value("updatetime").toDateTime();
                data_.insert(data.uuid, data);
            }

            return true;
        } else {
            qDebug() <<"sql error:"<<query.lastError().text();
            return false;
        }
    } else {
        return false;
    }
    return false;
}

int SqliteDatabase::add(EventTimeModel::Data data)
{
    return 0;
}

int SqliteDatabase::del(QString uuid)
{
    return 0;
}

int SqliteDatabase::update(QString uuid, EventTimeModel::Data data)
{
    return 0;
}

QMap<QString, EventTimeModel::Data> SqliteDatabase::selectAll()
{
    return data_;
}



EventTimeModel::EventTimeModel() :
    p_(new SqliteDatabase)
{

}

EventTimeModel::~EventTimeModel()
{
    delete p_;
}

int EventTimeModel::add(EventTimeModel::Data data)
{
    return p_->add(data);
}

int EventTimeModel::del(QString uuid)
{
    return p_->del(uuid);
}

int EventTimeModel::update(QString uuid, EventTimeModel::Data data)
{
    return p_->update(uuid, data);
}

QMap<QString, EventTimeModel::Data> EventTimeModel::selectAll()
{
    return p_->selectAll();
}


#include "eventtimemodel.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include "uuid.h"
#include <assert.h>
class EventTimeModelPrivate {
public:
    EventTimeModelPrivate(){}
    virtual ~EventTimeModelPrivate(){}
    virtual bool                                add(const EventTimeModel::Data& data) = 0;
    virtual bool                                del(QString uuid) = 0;
    virtual bool                                update(QString uuid, const EventTimeModel::Data& data) = 0;
    virtual QMap<QString, EventTimeModel::Data> selectAll() = 0;
protected:
    QMap<QString, EventTimeModel::Data> data_;
};

class EventTimeSqliteDatabase : public EventTimeModelPrivate {
public:
    EventTimeSqliteDatabase();
    ~EventTimeSqliteDatabase();
    virtual bool                                add(const EventTimeModel::Data& data);
    virtual bool                                del(QString uuid);
    virtual bool                                update(QString uuid, const EventTimeModel::Data& data);
    virtual QMap<QString, EventTimeModel::Data> selectAll();
private:
    bool initDB();
    QSqlDatabase db_;
};

EventTimeSqliteDatabase::EventTimeSqliteDatabase()
{
    if (!initDB()) {
        qDebug() << "cannot read data from sqlite database";
    }
}

EventTimeSqliteDatabase::~EventTimeSqliteDatabase()
{

}

bool EventTimeSqliteDatabase::initDB()
{
    db_ = QSqlDatabase::addDatabase("QSQLITE","local_timefriend_for_event_time");
    db_.setDatabaseName("timefriend.db");
    if (db_.open()) {
        selectAll();
        return true;
    } else {
        return false;
    }
    return false;
}

bool EventTimeSqliteDatabase::add(const EventTimeModel::Data&  data)
{
    if (db_.isOpen()) {
        QString sql = "insert into eventtime "
                      "(eventtimeid, userid, begintime, endtime, timelength, typeid, tag, text, addtime, updatetime)"
                      "values (:eventtimeid, :userid, :begintime, :endtime, :timelength, :typeid, :tag, :text, :addtime, :updatetime);";
        QSqlQuery query(db_);
        if (!query.prepare(sql)) {
            qDebug() << "prepare sql error:" << sql;
            return false;
        }
        QString uuid = Uuid::generate();
        int userid(0); // TODO: how to get userid?
        query.bindValue(":eventtimeid", data.uuid);
        query.bindValue(":userid", data.userID);
        query.bindValue(":begintime", data.beginTime);
        query.bindValue(":endtime", data.endTime);
        query.bindValue(":timelength", data.length);
        query.bindValue(":typeid", data.typeUuid);
        query.bindValue(":tag", data.tag);
        query.bindValue(":text", data.text);
        query.bindValue(":addtime", data.addTime);
        query.bindValue(":updatetime", data.updateTime);

        if (query.exec() ) {
            return true;
        } else {
            qDebug() <<"add sql error:"<<query.lastError().text();
            return false;
        }
    }
    return false;
}

bool EventTimeSqliteDatabase::del(QString uuid)
{
    return false;
}

bool EventTimeSqliteDatabase::update(QString uuid, const EventTimeModel::Data& data)
{
    return false;
}

QMap<QString, EventTimeModel::Data> EventTimeSqliteDatabase::selectAll()
{
    data_.clear();
    if (db_.isOpen()) {
        QString sql = "select * from eventtime;";
        QSqlQuery query(db_);
        if (query.exec(sql) ) {
            while (query.next()) {
                EventTimeModel::Data data;
                data.uuid = query.value("eventtimeid").toString();
                data.userID = query.value("userid").toString();
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
        } else {
            qDebug() <<"selectAll sql error:"<<query.lastError().text();
        }
    }
    return data_;
}



EventTimeModel::EventTimeModel() :
    d_(new EventTimeSqliteDatabase)
{

}

EventTimeModel::~EventTimeModel()
{
    delete d_;
}
bool eventTimeModelLessThan(const EventTimeModel::Data &d1, const EventTimeModel::Data &d2)
{
    return d1.beginTime  < d2.beginTime;
}
QList<EventTimeModel::Data> EventTimeModel::sort(const QMap<QString, EventTimeModel::Data> &map)
{
    QList<EventTimeModel::Data> list = map.values();
    qSort(list.begin(), list.end(), eventTimeModelLessThan);
    return list;
}

bool EventTimeModel::add(const EventTimeModel::Data& data)
{
    return d_->add(data);
}

bool EventTimeModel::del(QString uuid)
{
    return d_->del(uuid);
}

bool EventTimeModel::update(QString uuid, const EventTimeModel::Data& data)
{
    return d_->update(uuid, data);
}

QMap<QString, EventTimeModel::Data> EventTimeModel::selectAll()
{
    return d_->selectAll();
}


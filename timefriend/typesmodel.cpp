#include "typesmodel.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include "uuid.h"
#include <assert.h>
class TypesModelPrivate {
public:
    TypesModelPrivate(){}
    virtual ~TypesModelPrivate(){}
    virtual bool                                 add(const TypesModel::Data& data) = 0;
    virtual bool                                 del(QString uuid) = 0;
    virtual bool                                 update(QString uuid, const TypesModel::Data& data) = 0;
    virtual QMap<QString, TypesModel::Data> selectAll() = 0;
protected:
    QMap<QString, TypesModel::Data> data_;
};

class TypesSqliteDatabase : public TypesModelPrivate {
public:
    TypesSqliteDatabase();
    ~TypesSqliteDatabase();
    virtual bool                                 add(const TypesModel::Data& data);
    virtual bool                                 del(QString uuid);
    virtual bool                                 update(QString uuid, const TypesModel::Data& data);
    virtual QMap<QString, TypesModel::Data> selectAll();
private:
    bool initDB();
    QSqlDatabase db_;
};

TypesSqliteDatabase::TypesSqliteDatabase()
{
    if (!initDB()) {
        qDebug() << "cannot read data from sqlite database";
    }
}

TypesSqliteDatabase::~TypesSqliteDatabase()
{

}

bool TypesSqliteDatabase::initDB()
{
    db_ = QSqlDatabase::addDatabase("QSQLITE","local_timefriend_for_types");
    db_.setDatabaseName("timefriend.db");
    if (db_.open()) {
        selectAll();
        return true;
    } else {
        return false;
    }
    return false;
}

bool TypesSqliteDatabase::add(const TypesModel::Data&  data)
{
    if (db_.isOpen()) {
        QString sql = "insert into types "
                      "(typeid, userid, typename, addtime, updatetime)"
                      "values (:typeid, :userid, :typename, :addtime, :updatetime);";
        QSqlQuery query(db_);
        if (!query.prepare(sql)) {
            qDebug() << "prepare sql error:" << sql;
            return false;
        }
        QString uuid = Uuid::generate();
        int userid(0); // TODO: how to get userid?
        query.bindValue(":typeid", data.typeUuid);
        query.bindValue(":userid", data.userID);
        query.bindValue(":typename", data.typeName);
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

bool TypesSqliteDatabase::del(QString uuid)
{
    return false;
}

bool TypesSqliteDatabase::update(QString uuid, const TypesModel::Data& data)
{
    return false;
}

QMap<QString, TypesModel::Data> TypesSqliteDatabase::selectAll()
{
    data_.clear();
    if (db_.isOpen()) {
        QString sql = "select * from types;";
        QSqlQuery query(db_);
        if (query.exec(sql) ) {
            while (query.next()) {
                TypesModel::Data data;
                data.userID = query.value("userid").toString();
                data.typeUuid = query.value("typeid").toString();
                data.typeName = query.value("typename").toString();
                data.addTime = query.value("addtime").toDateTime();
                data.updateTime = query.value("updatetime").toDateTime();
                data_.insert(data.typeUuid, data);
            }
        } else {
            qDebug() <<"selectAll sql error:"<<query.lastError().text();
        }
    }
    return data_;
}



TypesModel::TypesModel() :
    d_(new TypesSqliteDatabase)
{

}

TypesModel::~TypesModel()
{
    delete d_;
}

bool TypesModel::add(const TypesModel::Data& data)
{
    return d_->add(data);
}

bool TypesModel::del(QString uuid)
{
    return d_->del(uuid);
}

bool TypesModel::update(QString uuid, const TypesModel::Data& data)
{
    return d_->update(uuid, data);
}

QMap<QString, TypesModel::Data> TypesModel::selectAll()
{
    return d_->selectAll();
}

QString TypesModel::typeName(const QString &typeUuid)
{
    QMap<QString, TypesModel::Data> map = d_->selectAll();
    return map.value(typeUuid).typeName;
}


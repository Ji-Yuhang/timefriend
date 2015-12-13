#include "database.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

DataBase *DataBase::instance()
{
    static DataBase db;
    return &db;
}

void DataBase::init()
{
    db_ = QSqlDatabase::addDatabase("QMYSQL","timefriend");
    db_.setHostName("rds1m2iqskhitpx6nmx7u.mysql.rds.aliyuncs.com");
    db_.setUserName("jiyuhang");
    db_.setPassword("jiyuhang8757871");
    db_.setDatabaseName("timefriend");
    if (!db_.open()) {
        QSqlError error = db_.lastError();
        qDebug() << "aliyuncs timefriend Open Mysql ERROR : "<<error.text();
    }
}

void DataBase::select(int userid, const QDateTime &begainTime, const QDateTime &endTime, int type)
{
//    User::UserInfo empty;
//    QString sql = QString("select * from users where account=':account' and password=':password'");
//    QSqlQuery query(db_);
//    if (!query.prepare(sql)) {
//        qDebug() << "cannot prepare sql : "<< sql;
//        return empty;
//    }
//    query.bindValue(":account", account);
//    query.bindValue(":password",password);
//    if (query.exec()) {
//        while (query.next()) {
//            empty.userid = query.value("userid").toInt();
//            empty.account = query.value("account").toString();
//            empty.password = query.value("password").toString();
//            empty.uuid = query.value("uuid").toString();
//            empty.realname = query.value("name").toString();
//            empty.createtime = query.value("createtime").toDateTime();
//            empty.userid = query.value("userid").toInt();
//        }
//        qDebug() << "sql select users Success:";
//    } else {
//        qDebug() << "sql select users ERROR:" << query.lastError().text();
//    }
//    return empty;
}


void DataBase::add(const QDateTime &begainTime, const QDateTime &endTime, const QString &type, const QString &text)
{
    qint64 seconds(0);
    if (endTime > begainTime)
        seconds = begainTime.secsTo(endTime);
    int length = seconds / 60;
    QString sql = QString("insert into timefriend (begintime,endtime,timelength,type,text) values('%1','%2',%3,'%4','%5')").arg(begainTime.toString("yyyy-MM-dd hh:mm:ss")).arg(endTime.toString("yyyy-MM-dd hh:mm:ss")).arg(length).arg(type).arg(text);
    QSqlQuery query(db_);
    if (query.exec(sql)) {

        qDebug() << "sql insert Success:";

    } else {
        qDebug() << "sql insert ERROR:" << query.lastError().text();
    }
}

User::UserInfo DataBase::login(const QString &account, const QString &password)
{
    User::UserInfo empty;
    QString sql = QString("select * from users where account=':account' and password=':password'");
    QSqlQuery query(db_);
    if (!query.prepare(sql)) {
        qDebug() << "cannot prepare sql : "<< sql;
        return empty;
    }
    query.bindValue(":account", account);
    query.bindValue(":password",password);
    if (query.exec()) {
        while (query.next()) {
            empty.userid = query.value("userid").toInt();
            empty.account = query.value("account").toString();
            empty.password = query.value("password").toString();
            empty.uuid = query.value("uuid").toString();
            empty.realname = query.value("name").toString();
            empty.createtime = query.value("createtime").toDateTime();
            empty.userid = query.value("userid").toInt();
        }
        qDebug() << "sql select users Success:";
    } else {
        qDebug() << "sql select users ERROR:" << query.lastError().text();
    }
    return empty;
}

//Table::Table(DataBase *db)
//    :db_(db)
//{
//}

//T Table::select()
//{
//    QSqlDatabase db;
//    QString sql = QString("select * from %1 where %");
//    QSqlQuery query;
//    query.prepare(sql);
//}

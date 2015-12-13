#include "test.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QDebug>
#include <QTableView>
#include <QSqlRelationalDelegate>
#include <QSqlError>
#include "database.h"
Test::Test(QObject *parent) : QObject(parent)
{

}

void Test::test()
{
    DataBase* db = DB;
    db->init();

    //! [0]
    //!
//    QSqlDatabase realdb = db->db();
    QSqlDatabase realdb = QSqlDatabase::addDatabase("QMYSQL","timefriendtest");
    realdb.setHostName("rds1m2iqskhitpx6nmx7u.mysql.rds.aliyuncs.com");
    realdb.setUserName("jiyuhang");
    realdb.setPassword("jiyuhang8757871");
    realdb.setDatabaseName("timefriend");
    if (!realdb.open()) {
        QSqlError error = realdb.lastError();
        qDebug() << "aliyuncs timefriend Open Mysql ERROR : "<<error.text();
    }
    realdb.open();
    model_ = new QSqlRelationalTableModel(0,realdb);
    model_->setTable("users");//timeevent
    //! [0]

    model_->setEditStrategy(QSqlTableModel::OnFieldChange);// OnManualSubmit
    //! [1]
//    model_->setRelation(2, QSqlRelation("city", "id", "name"));
    //! [1] //! [2]
//    model_->setRelation(3, QSqlRelation("country", "id", "name"));
    //! [2]

    //! [3]
//    model_->setHeaderData(0, Qt::Horizontal, QObject::tr("typeid"));
//    model_->setHeaderData(1, Qt::Horizontal, QObject::tr("text"));
//    model_->setHeaderData(2, Qt::Horizontal, QObject::tr("begintime"));
//    model_->setHeaderData(3, Qt::Horizontal, QObject::tr("endtime"));
    //! [3]

    model_->select();
    QTableView *view = new QTableView;
    view->setModel(model_);

    view->setItemDelegate(new QSqlRelationalDelegate(view));
    view->setAlternatingRowColors(true);
//    view->setEditTriggers();
//! [4]
    view->setWindowTitle("TimeFriend");
    view->show();
    model_->select();
//    view->update
//    model_
#if 0
    socket_.connectToHost("localhost",5200);
    socket_.waitForConnected(3000);
    QJsonDocument doc;
    QJsonObject login;

    login["controller"] = "user";
    login["action"] = "login";
    login["account"] = "jiyuhang110";
    login["password"] = "jiyuhang8757871";

    doc.setObject(login);


    socket_.write(doc.toJson().toBase64()+"\n");
    socket_.waitForReadyRead();
    QByteArray data = socket_.readAll();
    qDebug() << data<<endl<<QByteArray::fromBase64(data);
#endif
}


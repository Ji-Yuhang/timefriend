#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QDateTime>
#include <QString>
#include "user.h"
class DataBase : public QObject
{
    Q_OBJECT
private:
    explicit DataBase(QObject *parent = 0);
public:

    static DataBase* instance();
    QSqlDatabase db() {return db_;}

    void init();
    void select(int userid, const QDateTime &begainTime, const QDateTime &endTime, int type);

    void add(const QDateTime &begainTime, const QDateTime &endTime, const QString &type, const QString &text);
    User::UserInfo login(const QString& account, const QString& password);


signals:

public slots:
private:
    QSqlDatabase db_;
};
#define DB DataBase::instance()
//template<class T>
//class Table : public DataBase
//{
//public:
//    Table(DataBase* db);

//    T select();
//    bool insert(const T& t);
//    bool update(const T& t);
//    bool del(const T& t);

//    DataBase* db_;
//};


#endif // DATABASE_H

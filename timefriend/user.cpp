#include "user.h"
#include "database.h"
User::User(QObject *parent) : QObject(parent)
{

}

User::UserInfo User::login(const QString &account, const QString &password)
{
    DataBase* db = DB;
    User::UserInfo info = db->login(account,password);
    return info;
}


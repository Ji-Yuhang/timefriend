#ifndef USER_H
#define USER_H

#include <QDateTime>
#include <QObject>



class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QObject *parent = 0);
    struct UserInfo {
        int userid;
        QString account;
        QString password;
        QString uuid;
        QString realname;
        QDateTime createtime;
        UserInfo():userid(0){}
    };

    UserInfo login(const QString& account, const QString& password);

signals:

public slots:
};

#endif // USER_H

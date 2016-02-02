#include "uuid.h"
#include <QUuid>
#include <assert.h>
#include <QDebug>
#include <QDateTime>
QString Uuid::generate()
{
//    qsrand(QDateTime::currentMSecsSinceEpoch());
//    QUuid key = QUuid("{c29daf60-ab6c-0133-d1f0-7788cc3c17ed}");
//    QString nameBase = "time-friend";
//    assert(!key.isNull());
//    QString uuid = QUuid::createUuidV5(key, nameBase).toString();
    QString uuid = QUuid::createUuid().toString();
    QString formatUuid = uuid.mid(1,36);
    qDebug() << "generate uuid" << formatUuid;
    return formatUuid;
}

Uuid::Uuid()
{

}


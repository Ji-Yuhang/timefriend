#ifndef EVENTTIMEMODEL_H
#define EVENTTIMEMODEL_H

#include <QDateTime>
#include <QObject>
#include "uuid.h"
class EventTimeModelPrivate;
class EventTimeModel : public QObject
{
    Q_OBJECT
public:
    explicit EventTimeModel();
    ~EventTimeModel();

    struct Data {
        QString uuid;
        int userID;
        QDateTime beginTime;
        QDateTime endTime;
        int length; // second
        QString typeUuid;
        QString tag;
        QString text;
        QDateTime addTime;
        QDateTime updateTime;
        Data() : userID(-1), length(0){}
    };

    int                                 add(EventTimeModel::Data data);
    int                                 del(QString uuid);
    int                                 update(QString uuid, EventTimeModel::Data data);
    QMap<QString, EventTimeModel::Data> selectAll();

    EventTimeModelPrivate* p_;
};

#endif // EVENTTIMEMODEL_H

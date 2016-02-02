#ifndef EventTimeModel_H
#define EventTimeModel_H

#include <QDateTime>
#include <QObject>
class EventTimeModelPrivate;
class EventTimeModel : public QObject
{
    Q_OBJECT
public:
    explicit EventTimeModel();
    ~EventTimeModel();

    struct Data {
        QString uuid;
        QString userID;
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

    bool                                 add(const EventTimeModel::Data& data);
    bool                                 del(QString uuid);
    bool                                 update(QString uuid, const EventTimeModel::Data& data);
    QMap<QString, EventTimeModel::Data>  selectAll();

    EventTimeModelPrivate* d_;
};

#endif // EventTimeModel_H

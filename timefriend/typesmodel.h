#ifndef TYPESMODEL_H
#define TYPESMODEL_H

#include <QDateTime>
#include <QObject>
class TypesModelPrivate;
class TypesModel : public QObject
{
    Q_OBJECT
public:
    explicit TypesModel();
    ~TypesModel();

    struct Data {
        QString typeUuid;
        QString userID;
        QString typeName;
        QDateTime addTime;
        QDateTime updateTime;
        Data() : userID(-1){}
    };

    bool                                 add(const TypesModel::Data& data);
    bool                                 del(QString uuid);
    bool                                 update(QString uuid, const TypesModel::Data& data);
    QMap<QString, TypesModel::Data> selectAll();
    QString typeName(const QString& typeUuid);

    TypesModelPrivate* d_;
};

#endif // TYPESMODEL_H

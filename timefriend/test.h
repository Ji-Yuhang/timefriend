#ifndef TEST_H
#define TEST_H

#include <QObject>
#include <QTcpSocket>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>

class Test : public QObject
{
    Q_OBJECT
public:
    explicit Test(QObject *parent = 0);
    void test();

signals:

public slots:
private:
    QTcpSocket socket_;
    QSqlRelationalTableModel* model_;
};

#endif // TEST_H

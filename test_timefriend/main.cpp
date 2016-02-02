#include "mainwindow.h"
#include <QApplication>
#include "../timefriend/uuid.h"
#include "../timefriend/uuid.cpp"
#include "../timefriend/eventtimemodel.h"
#include "../timefriend/eventtimemodel.cpp"
#include "E:\git\timefriend\build\build-timefriend-Desktop_Qt_5_5_1_MinGW_32bit-Debug\debug\moc_eventtimemodel.cpp"
#include "../timefriend/typesmodel.h"
#include "../timefriend/typesmodel.cpp"
#include "E:\git\timefriend\build\build-timefriend-Desktop_Qt_5_5_1_MinGW_32bit-Debug\debug\moc_typesmodel.cpp"
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    for (int i = 0; i < 1; ++i) {
        QString uuid = Uuid::generate();
    }
    EventTimeModel model;
    EventTimeModel::Data data;
    data.uuid = Uuid::generate();
    data.userID = Uuid::generate();
    data.beginTime = QDateTime::currentDateTime();
    data.endTime = QDateTime::currentDateTime();
    data.length = 0;
    data.typeUuid = Uuid::generate();
    data.tag = "tag";
    data.text = "W.C.";

    data.addTime = QDateTime::currentDateTime();
    data.updateTime = QDateTime::currentDateTime();
//    model.add(data);
    QMap<QString, EventTimeModel::Data> map = model.selectAll();

    TypesModel typeModel;
    QString userid = "e6b46f50-17e0-4f42-851e-f4dc02fb50c5"; //Uuid::generate();

    QStringList types;
    types << QStringLiteral("工作")
          << QStringLiteral("读书")
          << QStringLiteral("学习")
          << QStringLiteral("家务")
          << QStringLiteral("运动")
          << QStringLiteral("睡觉")
          << QStringLiteral("交通")
          << QStringLiteral("饮食")
          << QStringLiteral("电视")
          << QStringLiteral("上网")
          << QStringLiteral("游戏")
          << QStringLiteral("其他");
    for (int i = 0; i < types.size(); ++i) {

        TypesModel::Data data1;
        data1.typeUuid = Uuid::generate();
        data1.userID = userid;
        data1.typeName = types.at(i);
        data1.addTime = QDateTime::currentDateTime();
        data1.updateTime = QDateTime::currentDateTime();
//        typeModel.add(data1);
    }
    QMap<QString, TypesModel::Data> map1 = typeModel.selectAll();

    return a.exec();
}

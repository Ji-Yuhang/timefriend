#include <QApplication>
#include "mainwindow.hxx"
#include <QDebug>
#include "tomato.hxx"
#include "test.h"
#include "eventtimemodel.h"
#include "typesmodel.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setQuitOnLastWindowClosed(false);

    MainWindow w;
    w.show();
    Test test;
//    test.test();
//    Tomate tomato;
//    tomato.show();

//    TypesModel typemodel;
//    EventTimeModel etmodel_;
//    EventTimeView view_;
//    view_.setEventTimeModel(&etmodel_);
//    view_.setTypesModel(&typemodel);
//    view_.show();
//    view_.refresh();

    return app.exec();
}

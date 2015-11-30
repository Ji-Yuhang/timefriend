#include <QApplication>
//#include <QQmlApplicationEngine>
#include "mainwindow.hxx"
#include <QDebug>
#include "tomato.hxx"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setQuitOnLastWindowClosed(false);

    MainWindow w;
    w.show();
//    Tomate tomato;
//    tomato.show();


    return app.exec();
}

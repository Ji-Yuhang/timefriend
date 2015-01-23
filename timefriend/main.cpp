#include <QApplication>
//#include <QQmlApplicationEngine>
#include "mainwindow.hxx"
#include <QDebug>
#include "tomate.hxx"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setQuitOnLastWindowClosed(false);
<<<<<<< HEAD
=======
//    QString path = qApp->applicationDirPath() + "/../../..
//    qDebug() << "path" <<path;
>>>>>>> FETCH_HEAD

    MainWindow w;
    w.show();
//    Tomate tomato;
//    tomato.show();


    return app.exec();
}

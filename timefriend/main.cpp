#include <QApplication>
//#include <QQmlApplicationEngine>
#include "mainwindow.hxx"
#include <QDebug>
#include "tomate.hxx"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
<<<<<<< HEAD
    QString path = qApp->applicationDirPath();
#ifdef Q_OS_MAC
    path += "/../../..";
#endif
//    qApp->addLibraryPath(path);
//    qApp->addLibraryPath("/Users/jiyuhang/Qt5.4.0/5.4/clang_64/plugins");
//    qApp->addLibraryPath("/Users/jiyuhang/Qt5.4.0/5.4/clang_64/plugins/sqldrivers");
=======
    QApplication::setQuitOnLastWindowClosed(false);
//    QString path = qApp->applicationDirPath() + "/../../..
//    qDebug() << "path" <<path;
>>>>>>> FETCH_HEAD

    MainWindow w;
    w.show();
//    Tomate tomato;
//    tomato.show();


    return app.exec();
}

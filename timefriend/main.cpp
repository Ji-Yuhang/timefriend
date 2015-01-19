#include <QApplication>
//#include <QQmlApplicationEngine>
#include "mainwindow.hxx"
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QString path = qApp->applicationDirPath();
#ifdef Q_OS_MAC
    path += "/../../..";
#endif
//    qApp->addLibraryPath(path);
//    qApp->addLibraryPath("/Users/jiyuhang/Qt5.4.0/5.4/clang_64/plugins");
//    qApp->addLibraryPath("/Users/jiyuhang/Qt5.4.0/5.4/clang_64/plugins/sqldrivers");

    qDebug() << "path" <<path;
//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    MainWindow w;
    w.show();

    return app.exec();
}

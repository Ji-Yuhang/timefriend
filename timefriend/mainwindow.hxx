#ifndef MAINWINDOW_HXX
#define MAINWINDOW_HXX

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSystemTrayIcon>
#include "ui_mainwindow.h"
#include <QTimer>
#include "tomato.hxx"
#include "backtomain.h"
#include "typesmodel.h"
#include "user.h"
#include "eventtimeview.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static MainWindow* instance();
private:
    Ui::MainWindow ui_;
    QSqlDatabase db_;
    QTimer timer_;
    QDateTime startTime_;
    bool isWaitStop_;
    static MainWindow* g_mainwindow_;
    Tomato tomato_;
    QSystemTrayIcon trayIcon_;
    BackToMain backtoMain_;

//    EventTimeModel model_;
//    EventTimeView view_;
    User user_;
Q_SIGNALS:

public Q_SLOTS:
    void onAddClicked();
    void onStartClicked();
    void onStopClicke();
    void onTimeout();
    void showTomato();
    void getTodayList();
    void insertTimeEvent(const QDateTime& begainTime, const QDateTime& endTime, const QString& type, const QString& text );

};
#define qMainWindow MainWindow::instance()
#define qSize MainWindow::instance()->size()
#define qWidth MainWindow::instance()->size().width()
#define qHeight MainWindow::instance()->size().height()

#endif // MAINWINDOW_HXX

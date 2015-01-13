#ifndef MAINWINDOW_HXX
#define MAINWINDOW_HXX

#include <QMainWindow>
#include <QSqlDatabase>
#include "ui_mainwindow.h"
#include <QTimer>
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow ui_;
    QSqlDatabase db_;
    QTimer timer_;
    QDateTime startTime_;
    bool isWaitStop_;

signals:

public slots:
    void onAddClicked();
    void onStartClicked();
    void onStopClicke();
    void onTimeout();
    void getTodayList();
    void insertTimeEvent(const QDateTime& begainTime, const QDateTime& endTime, const QString& type, const QString& text );
};

#endif // MAINWINDOW_HXX

#include "mainwindow.hxx"

#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QApplication>
#include <QSqlQuery>
#include <QTimer>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    isWaitStop_(false)
{
    ui_.setupUi(this);
    connect(&timer_, SIGNAL(timeout()), this, SLOT(onTimeout()));
    connect(ui_.addTime, SIGNAL(clicked()), this, SLOT(onAddClicked()));
    connect(ui_.start, SIGNAL(clicked()), this, SLOT(onStartClicked()));
    connect(ui_.stop, SIGNAL(clicked()), this, SLOT(onStopClicke()));
    ui_.stop->hide();
    ui_.timeLabel->hide();

    QDateTime now = QDateTime::currentDateTime();
    ui_.begainTime->setDateTime(now);
    ui_.endTime->setDateTime(now);

    db_ = QSqlDatabase::addDatabase("QMYSQL","mysql");
    db_.setHostName("116.251.208.100");
    db_.setUserName("root");
    db_.setPassword("jiyuhang8757871");
    db_.setDatabaseName("timefriend");
    if (!db_.open()) {
        QSqlError error = db_.lastError();
        qDebug() << "Open Mysql ERROR : "<<error.text();
        QMessageBox::warning(0,"sql open error",error.text());
    }
    getTodayList();
}

MainWindow::~MainWindow()
{

}

void MainWindow::onAddClicked()
{
    QDateTime beginTime = ui_.begainTime->dateTime();
    QDateTime endTime = ui_.endTime->dateTime();
    QString type = ui_.type->currentText();
    QString text = ui_.text->toPlainText();

    insertTimeEvent(beginTime,endTime,type,text);

}

void MainWindow::onStartClicked()
{
    QDateTime now = QDateTime::currentDateTime();
    if (!isWaitStop_) {
        timer_.start();
        // timer is stopped,
        startTime_ = now;
        //hh:mm:ss
        qint64 seconds = startTime_.secsTo(now);
        int ss = seconds % 60;
        int mm = seconds / 60;
        int hh = mm / 60;
        mm = mm % 60;
        QString timeStr = QString("%1:%2:%3").arg(hh).arg(mm).arg(ss);
        ui_.timeLabel->setText(timeStr);


        ui_.start->setText("停止计时");
        ui_.begainTime->setDateTime(startTime_);
        ui_.endTime->setDateTime(startTime_);

        ui_.timeLabel->show();

        isWaitStop_ = true;
    } else {
        timer_.stop();
        isWaitStop_ = false;

        ui_.begainTime->setDateTime(startTime_);
        ui_.endTime->setDateTime(now);
        ui_.start->setText("开始计时");
        ui_.timeLabel->hide();


        // timer is runing, until click stop
    }



}

void MainWindow::onStopClicke()
{

}
void MainWindow::onTimeout()
{
    QDateTime now = QDateTime::currentDateTime();
    QString nowStr = now.toString("yyyy-MM-dd hh:mm:ss");
    ui_.statusbar->showMessage(nowStr);

    if (isWaitStop_ && startTime_.isValid()) {
        // timer is runing, until click stop

        //hh:mm:ss
        qint64 seconds = startTime_.secsTo(now);
        int ss = seconds % 60;
        int mm = seconds / 60;
        int hh = mm / 60;
        mm = mm % 60;
        QString timeStr = QString("%1:%2:%3").arg(hh).arg(mm).arg(ss);
        ui_.timeLabel->setText(timeStr);

    }
}
void MainWindow::getTodayList()
{
//    return;
    QString sql = "select * from timefriend";
    QSqlQuery query(db_);
    if (query.exec(sql)) {
        int size = query.size();
//        ui_.tableWidget->clearContents();
//        ui_.tableWidget->clear();
        while (ui_.tableWidget->rowCount() > 0) {
            ui_.tableWidget->removeRow(0);
        }
        ui_.tableWidget->setRowCount(size);
        int index = 0;
        while (query.next()) {
            int id = query.value("id").toInt();;
            QDateTime begintime = query.value("begintime").toDateTime();
            QDateTime endtime = query.value("endtime").toDateTime();
            int length = query.value("timelength").toInt();;
            QString type = query.value("type").toString();
            QString text = query.value("text").toString();
            qDebug() << begintime << endtime << type << text;

            QTableWidgetItem* item1 = new QTableWidgetItem(begintime.toString("yyyy-MM-dd hh:mm:ss"));
            QTableWidgetItem* item2 = new QTableWidgetItem(endtime.toString("yyyy-MM-dd hh:mm:ss"));
            QTableWidgetItem* item3 = new QTableWidgetItem(QString::number(length) + QString("分"));

            QTableWidgetItem* item4 = new QTableWidgetItem(type);
            QTableWidgetItem* item5 = new QTableWidgetItem(text);

            ui_.tableWidget->setItem(index,0, item1);
            ui_.tableWidget->setItem(index,1, item2);
            ui_.tableWidget->setItem(index,2, item3);
            ui_.tableWidget->setItem(index,3, item4);
            ui_.tableWidget->setItem(index,4, item5);


            index++;

        }
        ui_.tableWidget->resizeColumnsToContents();

    } else {
        qDebug() << "sql select ERROR:" << query.lastError().text();
    }

    ui_.tableWidget->update();
}

void MainWindow::insertTimeEvent(const QDateTime &begainTime, const QDateTime &endTime, const QString &type, const QString &text)
{
    qint64 seconds(0);
    if (endTime > begainTime)
        seconds = begainTime.secsTo(endTime);
    int length = seconds / 60;
    QString sql = QString("insert into timefriend (begintime,endtime,timelength,type,text) values('%1','%2',%3,'%4','%5')").arg(begainTime.toString("yyyy-MM-dd hh:mm:ss")).arg(endTime.toString("yyyy-MM-dd hh:mm:ss")).arg(length).arg(type).arg(text);
    QSqlQuery query(db_);
    if (query.exec(sql)) {

        qDebug() << "sql insert Success:";
        QTimer::singleShot(0, this, SLOT(getTodayList()));

    } else {
        qDebug() << "sql insert ERROR:" << query.lastError().text();
    }
}


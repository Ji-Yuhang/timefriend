#include "tomate.hxx"
#include "ui_tomate.h"

Tomate::Tomate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tomate)
{
    ui->setupUi(this);
    connect(&timer_, SIGNAL(timeout()), this, SLOT(onTimeout()));
    onTimeout();
    timer_.start(1000);
}

Tomate::~Tomate()
{
    delete ui;
}
void Tomate::onTimeout()
{
    QDateTime now = QDateTime::currentDateTime();
    ui->currentTime->setText(now.toString("yyyy-MM-dd hh:mm:ss"));
    if (beginTime_.isValid()) {
        //hh:mm:ss
        qint64 seconds = beginTime_.secsTo(now);
        int ss = seconds % 60;
        int mm = seconds / 60;
        QString timeStr = QString("%2:%3").arg(mm).arg(ss);
        ui->beginTime->setText(timeStr);

        qint64 remainSeconds = 20*60 - seconds;
        int rss = remainSeconds % 60;
        int rmm = remainSeconds / 60;
        QString rtimeStr = QString("%2:%3").arg(rmm).arg(rss);
        ui->remainTime->setText(rtimeStr);
    }
}
void Tomate::on_pushButton_clicked()
{
    beginTime_ = QDateTime::currentDateTime();
}

void Tomate::on_pushButton_stop_clicked()
{
    beginTime_ = QDateTime();
}

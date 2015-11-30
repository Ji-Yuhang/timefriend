#include "tomato.hxx"
#include "ui_tomate.h"

#include <QMessageBox>

Tomato::Tomato(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tomate)
{
    ui->setupUi(this);
    connect(&timer_, SIGNAL(timeout()), this, SLOT(onTimeout()));
    onTimeout();
    timer_.start(500);
}

Tomato::~Tomato()
{
    delete ui;
}
void Tomato::onTimeout()
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

        if (seconds <= 0) {
            QMessageBox::information(0,"20 minutens over",QString::fromUtf8("\x32\x30\xE5\x88\x86\xE9\x92\x9F\xE5\x88\xB0\xE4\xBA\x86"));
        }
    }
}
void Tomato::on_pushButton_clicked()
{
    beginTime_ = QDateTime::currentDateTime();
}

void Tomato::on_pushButton_stop_clicked()
{
    beginTime_ = QDateTime();
}

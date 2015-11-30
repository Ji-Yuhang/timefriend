#include "remind.hxx"
#include "ui_remind.h"

#include <QDateTime>

Remind::Remind(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Remind)
{
    ui->setupUi(this);
    connect(&timer_, SIGNAL(timeout()), this, SLOT(onTimeout()));
    timer_.start(500);
}

Remind::~Remind()
{
    delete ui;
}

void Remind::onTimeout()
{
    QDateTime now = QDateTime::currentDateTime();
    ui->currentTime->setText(now.toString("yyyy-MM-dd hh:mm:ss"));
}

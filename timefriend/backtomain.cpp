#include "backtomain.h"
#include "ui_backtomain.h"

BackToMain::BackToMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BackToMain)
{
    ui->setupUi(this);
    connect(&timer_, &QTimer::timeout, this, &BackToMain::onTimeout);
    int oneMinute = 60000;
    timer_.start(20*oneMinute);
}

BackToMain::~BackToMain()
{
    delete ui;
}

void BackToMain::onTimeout()
{
    this->showFullScreen();
}

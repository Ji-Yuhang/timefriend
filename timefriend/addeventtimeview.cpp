#include "addeventtimeview.h"
#include "ui_addeventtimeview.h"
#include "eventtimemodel.h"
#include "typesmodel.h"
#include "uuid.h"

#include <QMessageBox>
#include <QDebug>
AddEventTimeView::AddEventTimeView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddEventTimeView),
    eventTimemodel_(0),
    typesModel_(0)
{
    ui->setupUi(this);
    connect(ui->add, &QPushButton::clicked, this, &AddEventTimeView::onAddClicked);
    connect(ui->cancel, &QPushButton::clicked, this, &AddEventTimeView::onCancelCicked);

}

AddEventTimeView::~AddEventTimeView()
{
    delete ui;
}
void AddEventTimeView::setEventTimeModel(EventTimeModel *model)
{
    eventTimemodel_ = model;
}

void AddEventTimeView::setTypesModel(TypesModel *typesModel)
{
    typesModel_ = typesModel;
    refreshModelData();
}

void AddEventTimeView::refreshModelData()
{
    if (!typesModel_) return;
    ui->comboBox->clear();
    QMap<QString, TypesModel::Data> map = typesModel_->selectAll();
    QList<TypesModel::Data> sortedList = TypesModel::sort(map);
    Q_FOREACH(const TypesModel::Data& data, sortedList) {
        ui->comboBox->addItem(data.typeName, data.typeUuid);
    }

    ui->beginTime->setDateTime(QDateTime::currentDateTime());
    ui->endTime->setDateTime(QDateTime::currentDateTime());

}
void AddEventTimeView::onAddClicked()
{
    if (!eventTimemodel_) return;
    EventTimeModel::Data data;
    data.uuid = Uuid::generate();
    data.userID = "e6b46f50-17e0-4f42-851e-f4dc02fb50c5";
    data.beginTime = ui->beginTime->dateTime();
    data.endTime = ui->endTime->dateTime();
    data.length = data.beginTime.secsTo(data.endTime);
    if (data.length <= 0) {
        qDebug() << "incorrect datetime" << data.beginTime << data.endTime;
        QMessageBox::warning(0, "incorrect datetime", "incorrect datetime from" + data.beginTime.toString("yyyy-MM-dd hh:mm:ss") + " to " + data.endTime.toString("yyyy-MM-dd hh:mm:ss"));
        return;
    }
    data.typeUuid = ui->comboBox->currentData().toString();
    data.tag = ui->lineEdit->text();
    data.text = ui->plainTextEdit->toPlainText();

    data.addTime = QDateTime::currentDateTime();
    data.updateTime = QDateTime::currentDateTime();
    if (eventTimemodel_->add(data)) {
        qDebug() << "add event time data Success!";
        ui->lineEdit->clear();
        ui->plainTextEdit->clear();
        this->close();
        Q_EMIT addSuccess();
    }


}

void AddEventTimeView::onCancelCicked()
{
    ui->lineEdit->clear();
    ui->plainTextEdit->clear();
    this->close();
}

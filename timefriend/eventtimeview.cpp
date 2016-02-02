#include "eventtimeview.h"
#include "ui_eventtimeview.h"
#include "eventtimemodel.h"
#include "typesmodel.h"
EventTimeView::EventTimeView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EventTimeView),
    eventTimemodel_(0),
    typesModel_(0)
{
    ui->setupUi(this);
}

EventTimeView::~EventTimeView()
{
    delete ui;
}

void EventTimeView::setEventTimeModel(EventTimeModel *model)
{
    eventTimemodel_ = model;
    if (isVisible()) refresh();
}

void EventTimeView::setTypesModel(TypesModel *typesModel)
{
    typesModel_ = typesModel;
}

void EventTimeView::refresh()
{
    if (!eventTimemodel_) return;
    QTableWidget* table = ui->tableWidget;
    table->clearContents();
    QMap<QString, EventTimeModel::Data> map = eventTimemodel_->selectAll();
    table->setRowCount(map.size());
    QMap<QString, EventTimeModel::Data>::iterator it = map.begin();
    for (int row = 0; it != map.end(); ++it) {
        EventTimeModel::Data& data = it.value();

        QTableWidgetItem* item1 = new QTableWidgetItem(data.beginTime.toString("yyyy-MM-dd hh:mm:ss"));
        QTableWidgetItem* item2 = new QTableWidgetItem(data.endTime.toString("yyyy-MM-dd hh:mm:ss"));
        QTableWidgetItem* item3 = new QTableWidgetItem(QString::number(data.length) + QStringLiteral(" 秒"));

        QString typeName;
        if (typesModel_) {
            typeName = typesModel_->typeName(data.typeUuid);
        }
        QTableWidgetItem* item4 = new QTableWidgetItem(typeName);
        QTableWidgetItem* item5 = new QTableWidgetItem(data.text);

        table->setItem(row,0, item1);
        table->setItem(row,1, item2);
        table->setItem(row,2, item3);
        table->setItem(row,3, item4);
        table->setItem(row,4, item5);

        ++row;
    }
    table->resizeColumnsToContents();





}

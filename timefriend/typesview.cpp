#include "typesview.h"
#include "ui_typesview.h"
#include "typesmodel.h"
#include "uuid.h"

#include <QMessageBox>
#include <QDebug>
TypesView::TypesView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TypesView),
    typesModel_(0)
{
    ui->setupUi(this);
    connect(ui->add, &QPushButton::clicked, this, &TypesView::onAddClicked);
    connect(ui->refresh, &QPushButton::clicked, this, &TypesView::onRefresh);
    connect(ui->reInput, &QPushButton::clicked, this, &TypesView::onReInput);
    connect(ui->del, &QPushButton::clicked, this, &TypesView::onDelete);
    connect(ui->update, &QPushButton::clicked, this, &TypesView::onUpdate);
    connect(ui->treeWidget, &QTreeWidget::currentItemChanged, this, &TypesView::onCurrentItemChanged);
}

TypesView::~TypesView()
{
    delete ui;
}

void TypesView::setTypesModel(TypesModel *typesModel)
{
    typesModel_ = typesModel;
    onRefresh();
}

void TypesView::onCurrentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    if (!current) {
        currentUuid_.clear();
        ui->currentType->setText("");
        ui->update->setEnabled(false);
        ui->del->setEnabled(false);
        return;
    }
    QString uuid = current->data(0, Qt::UserRole).toString();
    QMap<QString, TypesModel::Data> map = typesModel_->selectAll();
    TypesModel::Data data = map.value(uuid);
    ui->currentType->setText(data.typeName);
    bool vaild = !data.typeUuid.isEmpty();
    ui->update->setEnabled(vaild);
    ui->del->setEnabled(vaild);
    currentUuid_ = uuid;
    if (current && previous)
        qDebug() << "current type from"<< previous->text(0) <<"to"<<current->text(0);
}

void TypesView::onAddClicked()
{
    QString userid = "e6b46f50-17e0-4f42-851e-f4dc02fb50c5"; //Uuid::generate();

    TypesModel::Data data;
    data.typeUuid = Uuid::generate();
    data.userID = userid;
    data.typeName = ui->addTypeName->text();
    data.addTime = QDateTime::currentDateTime();
    data.updateTime = QDateTime::currentDateTime();
    if (typesModel_->add(data)) {
        onRefresh();
    }
}

void TypesView::onRefresh()
{
    if (!typesModel_) return;
    ui->treeWidget->clear();
    QMap<QString, TypesModel::Data> map = typesModel_->selectAll();
    QList<TypesModel::Data> sortedList = TypesModel::sort(map);
    Q_FOREACH(const TypesModel::Data& data, sortedList) {
        QTreeWidgetItem* item = new QTreeWidgetItem;
        item->setText(0, data.typeName);
        item->setData(0, Qt::UserRole, data.typeUuid);
        ui->treeWidget->addTopLevelItem(item);
    }

    Q_EMIT dataChanged();
}

void TypesView::onReInput()
{
    ui->addTypeName->clear();
}

void TypesView::onDelete()
{
    if (currentUuid_.isEmpty()) return;
    if (typesModel_->del(currentUuid_)) {
        onRefresh();
    }
}

void TypesView::onUpdate()
{

}

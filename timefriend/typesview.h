#ifndef TYPESVIEW_H
#define TYPESVIEW_H

#include <QWidget>

namespace Ui {
class TypesView;
}
class TypesModel;
class QTreeWidgetItem;
class TypesView : public QWidget
{
    Q_OBJECT

public:
    explicit TypesView(QWidget *parent = 0);
    ~TypesView();
    void setTypesModel(TypesModel* typesModel);
Q_SIGNALS:
    void dataChanged();
public Q_SLOTS:
    void onCurrentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    void onAddClicked();
    void onRefresh();
    void onReInput();
    void onDelete();
    void onUpdate();

private:
    Ui::TypesView *ui;
    TypesModel* typesModel_;
    QString currentUuid_;

};

#endif // TYPESVIEW_H

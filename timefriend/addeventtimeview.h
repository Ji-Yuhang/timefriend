#ifndef ADDEVENTTIMEVIEW_H
#define ADDEVENTTIMEVIEW_H

#include <QWidget>

namespace Ui {
class AddEventTimeView;
}
class EventTimeModel;
class TypesModel;
class AddEventTimeView : public QWidget
{
    Q_OBJECT

public:
    explicit AddEventTimeView(QWidget *parent = 0);
    ~AddEventTimeView();
    void setEventTimeModel(EventTimeModel* model);
    void setTypesModel(TypesModel* typesModel);

Q_SIGNALS:
    void addSuccess();
public Q_SLOTS:
    void refreshModelData();
    void onAddClicked();
    void onCancelCicked();


private:
    Ui::AddEventTimeView *ui;
    EventTimeModel* eventTimemodel_;
    TypesModel* typesModel_;
};

#endif // ADDEVENTTIMEVIEW_H

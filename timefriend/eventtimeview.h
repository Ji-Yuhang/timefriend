#ifndef EVENTTIMEVIEW_H
#define EVENTTIMEVIEW_H

#include <QWidget>

namespace Ui {
class EventTimeView;
}
class EventTimeModel;
class TypesModel;
class EventTimeView : public QWidget
{
    Q_OBJECT

public:
    explicit EventTimeView(QWidget *parent = 0);
    ~EventTimeView();
    void setEventTimeModel(EventTimeModel* model);
    void setTypesModel(TypesModel* typesModel);
public Q_SLOTS:
    void refresh();

private:
    Ui::EventTimeView *ui;
    EventTimeModel* eventTimemodel_;
    TypesModel* typesModel_;
};

#endif // EVENTTIMEVIEW_H

#ifndef REMIND_HXX
#define REMIND_HXX

#include <QTimer>
#include <QWidget>

namespace Ui {
class Remind;
}

class Remind : public QWidget
{
    Q_OBJECT

public:
    explicit Remind(QWidget *parent = 0);
    ~Remind();
    QTimer timer_;

private:
    Ui::Remind *ui;
public Q_SLOTS:
    void onTimeout();

};

#endif // REMIND_HXX

#ifndef BACKTOMAIN_H
#define BACKTOMAIN_H

#include <QTimer>
#include <QWidget>

namespace Ui {
class BackToMain;
}

class BackToMain : public QWidget
{
    Q_OBJECT

public:
    explicit BackToMain(QWidget *parent = 0);
    ~BackToMain();
private Q_SLOTS:
    void onTimeout();

private:
    Ui::BackToMain *ui;
    QTimer timer_;
};

#endif // BACKTOMAIN_H

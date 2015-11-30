#ifndef TOMATE_HXX
#define TOMATE_HXX

#include <QWidget>
#include <QTimer>
#include <QDateTime>
namespace Ui {
class Tomate;
}

class Tomato : public QWidget
{
    Q_OBJECT

public:
    explicit Tomato(QWidget *parent = 0);
    ~Tomato();
    QDateTime beginTime_;
    QTimer timer_;
public Q_SLOTS:
    void onTimeout();
    void on_pushButton_clicked();

private slots:
    void on_pushButton_stop_clicked();

private:
    Ui::Tomate *ui;
};

#endif // TOMATE_HXX

#ifndef INTERPS_H
#define INTERPS_H

#include <QMainWindow>

namespace Ui {
class interps;
}

class interps : public QMainWindow
{
    Q_OBJECT

public:
    explicit interps(QWidget *parent = nullptr);
    ~interps();

    void display_value(uint psId,QVariant data);

private slots:
    void on_tabWidget_currentChanged(int index);

private:
    Ui::interps *ui;
};

#endif // INTERPS_H

#ifndef INTERBD_H
#define INTERBD_H

#include <QMainWindow>
#include <accelerater.h>

namespace Ui {
class interBD;
}

class interBD : public QMainWindow
{
    Q_OBJECT

public:
    explicit interBD(QWidget *parent = nullptr);
    ~interBD();

private:
    accelerater* accelerater_;
    Ui::interBD *ui;
};

#endif // INTERBD_H

#ifndef INTERBD_H
#define INTERBD_H

#include <QMainWindow>
#include <accelerater.h>
#include "backend.h"

namespace Ui {
class interBD;
}

class interBD : public QMainWindow
{
    Q_OBJECT

public:
    explicit interBD(Backend* myBackend_,QWidget *parent = nullptr);
    ~interBD();
    void showBDsubInterface(QString activeBDname);

private:
    accelerater* accelerater_;
    Ui::interBD *ui;
    //后端采集线程
    Backend* myBackend;
};

#endif // INTERBD_H

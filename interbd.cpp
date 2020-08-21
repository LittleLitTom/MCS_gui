#include "interbd.h"
#include "ui_interbd.h"

interBD::interBD(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::interBD)
{
    ui->setupUi(this);
    accelerater_ = new accelerater;
    ui->scrollArea->setWidget(accelerater_);
}

interBD::~interBD()
{
    delete ui;
}


void interBD::setmagnet(int n)
{
        accelerater_->changeMe(n);
}

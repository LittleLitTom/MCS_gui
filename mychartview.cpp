#include "mychartview.h"
#include "ui_mychartview.h"

MyChartView::MyChartView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyChartView)
{
    ui->setupUi(this);
}

MyChartView::~MyChartView()
{
    delete ui;
}

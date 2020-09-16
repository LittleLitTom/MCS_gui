#include "interbd.h"
#include "ui_interbd.h"
#include "dbdetails.h"

interBD::interBD(Backend* myBackend_,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::interBD)
{
    ui->setupUi(this);

    //子对象初始化
    accelerater_ = new accelerater(this);
    myBackend = myBackend_;

    ui->scrollArea->setWidget(accelerater_);

    connect(accelerater_,&accelerater::aNewSubInterface,this,&interBD::showBDsubInterface);
}

interBD::~interBD()
{
    delete ui;
}

void interBD::showBDsubInterface(QString activeBDname)
{
    //新建束测子界面
    auto DBDetails_ = new DBDetails(this, activeBDname);

    //束测子界面与后端采集线程连接
    connect(myBackend, &Backend::dataChange, DBDetails_, &DBDetails::display_value);

    connect(DBDetails_, &DBDetails::writeNodes, myBackend, &Backend::writeNodes);
    connect(DBDetails_, &DBDetails::readNodes, myBackend, &Backend::readNodes);
    connect(myBackend, &Backend::writeNodesResults, DBDetails_, &DBDetails::process_write_results);
    connect(myBackend, &Backend::readNodesResults, DBDetails_, &DBDetails::process_read_results);
    //界面初始化
    DBDetails_->initialDBDetails();
    //界面显示
    DBDetails_->show();
}


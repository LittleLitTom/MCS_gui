#include "interbd.h"
#include "ui_interbd.h"
#include "dbdetails.h"

interBD::interBD(Backend* myBackend_,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::interBD)
{
    ui->setupUi(this);

    //�Ӷ����ʼ��
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
    //�½������ӽ���
    auto DBDetails_ = new DBDetails(this, activeBDname);

    //�����ӽ������˲ɼ��߳�����
    connect(myBackend, &Backend::dataChange, DBDetails_, &DBDetails::display_value);

    connect(DBDetails_, &DBDetails::writeNodes, myBackend, &Backend::writeNodes);
    connect(DBDetails_, &DBDetails::readNodes, myBackend, &Backend::readNodes);
    connect(myBackend, &Backend::writeNodesResults, DBDetails_, &DBDetails::process_write_results);
    connect(myBackend, &Backend::readNodesResults, DBDetails_, &DBDetails::process_read_results);
    //�����ʼ��
    DBDetails_->initialDBDetails();
    //������ʾ
    DBDetails_->show();
}


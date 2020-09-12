#include "dbdetails.h"
#include "ui_dbdetails.h"

#include <QtCharts/QChartView>
#include <QtCharts/QChart>

//束测器件id格式：MN-XA-BC-DE-FG
//MN：子系统代号，XA：束测器件类型，BC：区域段编号，DE：某区域段束测器件序号，FG：控制变量
//对于束测子系统其子系统代号为：02
//XA(束测器件类型)：01:FC，02:SC，03:IC
//例如对于SC1E，其Id号为：0202010100
//对于控制变量属性：
//[SC_Mode 01,SC_Trigger 02,SC_Frequency 03,SC_PositionSet 04,SC_Pushout 05,SC_Pushin 06,SC_BeamPosition 07,SC_PositionMean 08,SC_BeamProfile 09,SC_BeamFWHM 10,SC_Samplingpoints 11]

DBDetails::DBDetails(QWidget *parent, QString DBname) :
    QMainWindow(parent),
    ui(new Ui::DBDetails),
    DBname(DBname)
{
    ui->setupUi(this);
    ui->label->setText("荧光屏：    "+DBname);
    //设置这个属性后，页面关闭，其代表的对象会被删除
    setAttribute (Qt::WA_DeleteOnClose);
    //新建Button Group,将check Box放入组中
    daqModeGroup = new QButtonGroup(this);
    daqModeGroup->addButton(ui->manualDAQ);
    daqModeGroup->addButton(ui->automaticDAQ);
    motionGroup = new QButtonGroup(this);
    motionGroup->addButton(ui->PutIn);
    motionGroup->addButton(ui->PullOff);
    //新建图
    myChartX = new QChart();
    myChartY = new QChart();
    //xWaveView = new QChartView(new QChart(),this);
    //ui->xWaveBox->set
}

DBDetails::~DBDetails()
{
    delete ui;
}


void DBDetails::display_value(uint dbId, QVariant data)
{
    
}

void DBDetails::process_read_results(QList<uint> ids, QList<QVariant> datas, QList<int> results)
{

}

void DBDetails::process_write_results(QList<uint> ids, QList<int> results)
{

}
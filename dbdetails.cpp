#include "dbdetails.h"
#include "ui_dbdetails.h"

#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>

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
    ui->bdIdentifier->setText("荧光屏：    "+DBname);
    //设置这个属性后，页面关闭，其代表的对象会被删除
    setAttribute(Qt::WA_DeleteOnClose);
    //由DB name获取DB Id,DB name和DB Id都是DBDatails类的重要属性
    DBId = utilities::scIdToNum(DBname);

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
    myChartXseries = new QLineSeries(myChartX);
    myChartYseries = new QLineSeries(myChartY);
    myChartX->addSeries(myChartXseries);
    myChartY->addSeries(myChartYseries);
    auto myChartXview = new QChartView(myChartX, this);
    auto myChartYview = new QChartView(myChartY, this);
    myChartX->createDefaultAxes();
    myChartY->createDefaultAxes();
    QGridLayout* myChartXlayout = new QGridLayout(this);
    QGridLayout* myChartYlayout = new QGridLayout(this);
    myChartXlayout->addWidget(myChartXview);
    myChartYlayout->addWidget(myChartYview);
    ui->xProfileBox->setLayout(myChartXlayout);
    ui->yProfileBox->setLayout(myChartYlayout);

    //信号与槽
    connect(this , );
}

DBDetails::~DBDetails()
{
    delete ui;
}


void DBDetails::display_value(uint dbId, QVariant data)
{
    //如果不是束测子系统，直接返回
    if (dbId / 100000000 != 2)
    {
        return;
    }

    //束测控制变量
    int psProperty = dbId % 100;
    //束测Id
    uint psIdentify = dbId / 100 * 100;
    //如果不是本界面的束测ID，直接退出
    if (psIdentify != DBId)
    {
        return;
    }

    switch (psProperty)
    {
    case 1://SC_Mode

        break;
    case 2://SC_Trigger

        break;
    case 3://SC_PositionSet

        break;
    case 4://SC_Pushin_status
    {
        if (data.toBool())
        {
            ui->Pushin_status->setStyleSheet("QLabel{background-color: rgb(0, 170, 0)};");//绿色灯亮
        }
        {
            ui->Pushin_status->setStyleSheet("QLabel{background-color: rgb(255, 0, 0)};");//红色灯亮
        }
    }
        break;
    case 5://SC_Pullout_status
        if (data.toBool())
        {
            ui->Pullout_status->setStyleSheet("QLabel{background-color: rgb(0, 170, 0)};");//绿色灯亮
        }
        {
            ui->Pullout_status->setStyleSheet("QLabel{background-color: rgb(255, 0, 0)};");//红色灯亮
        }
        break;
    case 6://SC_Frequency

        break;
    case 7://SC_Samplingpoints

        break;
    case 8://SC_BeamPosition_x
        ui->BeamPosition_x->setText(QString::number(data.toDouble(),'g',3));
        break;
    case 9://SC_BeamPosition_y
        ui->BeamPosition_y->setText(QString::number(data.toDouble(), 'g', 3));
        break;
    case 10://SC_PositionMean_x
        ui->PositionMean_x->setText(QString::number(data.toDouble(), 'g', 3));
        break;
    case 11://SC_PositionMean_y
        ui->PositionMean_y->setText(QString::number(data.toDouble(), 'g', 3));
        break;
    case 12://SC_BeamFWHM_x
        ui->BeamFWHM_x->setText(QString::number(data.toDouble(), 'g', 3));
        break;
    case 13://SC_BeamFWHM_y
        ui->BeamFWHM_y->setText(QString::number(data.toDouble(), 'g', 3));
        break;
    case 14://SC_FWHMMean_x
        ui->FWHMMean_x->setText(QString::number(data.toDouble(), 'g', 3));
        break;
    case 15://SC_FWHMMean_y
        ui->FWHMMean_y->setText(QString::number(data.toDouble(), 'g', 3));
        break;
    case 16://SC_BeamProfile_x
    {
        auto datalist = data.toList();
        QList<QPointF> myPointDataList;
        for (auto datai : datalist)
        {
            datalist.indexOf(datai);
            myPointDataList.append(QPointF(datalist.indexOf(datai), datai.toDouble()));
        }
        myChartXseries->replace(myPointDataList);
    }
        break;
    case 17://SC_BeamProfile_y
    {
        auto datalist = data.toList();
        QList<QPointF> myPointDataList;
        for (auto datai : datalist)
        {  datalist.indexOf(datai);
            myPointDataList.append(QPointF(datalist.indexOf(datai), datai.toDouble()));
        }
        myChartYseries->replace(myPointDataList);
    }
        break;
    }   
}

void DBDetails::process_read_results(QList<uint> ids, QList<QVariant> datas, QList<int> results)
{

}

void DBDetails::process_write_results(QList<uint> ids, QList<int> results)
{

}
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

    //新建Button Group,将check Box放入组中,并连接信号槽
    daqModeGroup = new QButtonGroup(this);
    daqModeGroup->addButton(ui->manualDAQ,1);//1为手动采集的CkeckId
    daqModeGroup->addButton(ui->automaticDAQ,0);//0为自动采集的CkeckId
    motionGroup = new QButtonGroup(this);
    motionGroup->addButton(ui->PutIn,1);//1为放入束测原件
    motionGroup->addButton(ui->PullOff,0);//0为拔出束测原件
    connect(daqModeGroup, &QButtonGroup::idClicked, this, &DBDetails::ON_daqModeGroup_clicked);
    connect(motionGroup, &QButtonGroup::idClicked, this, &DBDetails::ON_motionGroup_clicked);

    //新建图
    myChartX = new QChart();
    myChartY = new QChart();
    myChartXseries = new QLineSeries();
    myChartYseries = new QLineSeries();
    myChartX->addSeries(myChartXseries);
    myChartY->addSeries(myChartYseries);
    auto myChartXview = new QChartView(myChartX, this);
    auto myChartYview = new QChartView(myChartY, this);
    myChartX->createDefaultAxes();
    myChartY->createDefaultAxes();
    QGridLayout* myChartXlayout = new QGridLayout(ui->xProfileBox);
    QGridLayout* myChartYlayout = new QGridLayout(ui->yProfileBox);
    myChartXlayout->addWidget(myChartXview);
    myChartYlayout->addWidget(myChartYview);
}

DBDetails::~DBDetails()
{
    delete ui;
}

void DBDetails::initialDBDetails()
{
    QList<uint> ids;
    for (uint i = 1; i <= 17; i++)
    {
        ids.append(i + DBId);
    }
    emit readNodes(ids);
}



void DBDetails::display_value(uint dbId, QVariant data)
{
    //束测控制变量
    int psProperty = dbId % 100;
    //束测Id
    uint psIdentify = dbId / 100 * 100;
    //如果不是本子界面的束测OPC UA变量的ID，直接退出
    if (psIdentify != DBId)
    {
        return;
    }

    switch (psProperty)
    {
    case 1://SC_Mode
    {
        daqModeGroup->button(data.toBool())->setChecked(true);
    }
        break;
    case 2://SC_Trigger
        //...
        break;
    case 3://SC_PositionSet
    {
        motionGroup->button(data.toBool())->setChecked(true);
    }
        break;
    case 4://SC_Pushin_status
    {//switch()-{case:}语句中的判断语句一定要位于大括号中
        if (data.toBool())
        {
            ui->Pushin_status->setStyleSheet("QLabel{background-color: rgb(0, 170, 0)};");//绿色灯亮
        }
        else
        {
            ui->Pushin_status->setStyleSheet("QLabel{background-color: rgb(255, 0, 0)};");//红色灯亮
        }
    }
        break;
    case 5://SC_Pullout_status
    {
        if (data.toBool())
        {
            ui->Pullout_status->setStyleSheet("QLabel{background-color: rgb(0, 170, 0)};");//绿色灯亮
        }
        else
        {
            ui->Pullout_status->setStyleSheet("QLabel{background-color: rgb(255, 0, 0)};");//红色灯亮
        }
    }
        break;
    case 6://SC_Frequency
    {
        ui->frequency->setValue(data.toInt());
    }
        break;
    case 7://SC_Samplingpoints
    {
        ui->samplingPoints->setValue(data.toInt());
    }
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
        double i = 0,min = 0,max = 0;
        for (auto datai : datalist)
        {
            min = (min < datai.toDouble()) ? min : datai.toDouble();
            max = (max > datai.toDouble()) ? max : datai.toDouble();
            myPointDataList.append(QPointF(i, datai.toDouble()));
            i++;
        }
        myChartXseries->replace(myPointDataList);
        myChartX->axisX()->setRange(0,myChartXseries->count());
        myChartX->axisY()->setRange(min, max);
    }
        break;
    case 17://SC_BeamProfile_y
    {
        auto datalist = data.toList();
        QList<QPointF> myPointDataList;
        double i = 0,min=0,max=0;

        for (auto datai : datalist)
        {
            min = (min< datai.toDouble()) ? min : datai.toDouble();
            max = (max > datai.toDouble()) ? max : datai.toDouble();
            myPointDataList.append(QPointF(i, datai.toDouble()));
            i++;
        }
        myChartYseries->replace(myPointDataList);
        myChartY->axisX()->setRange(0,myChartYseries->count());
        myChartY->axisY()->setRange(min,max);
    }
        break;
    }   
}

void DBDetails::process_read_results(QList<uint> ids, QList<QVariant> datas, QList<int> results)
{
    int i = 0;
    for (auto data : datas)
    {
        display_value(ids[i], data);
        i++;
    }
}

void DBDetails::process_write_results(QList<uint> ids, QList<int> results)
{

}

void DBDetails::on_Trigger_clicked()//触发采样
{
    uint id = DBId+2;
    QVariant data(true);
    QList<uint> ids;
    QList<QVariant> datas;
    ids.append(id);
    datas.append(data);
    emit writeNodes(ids,datas);
}

void DBDetails::on_frequencySet_clicked()//采样频率设置
{
    uint id = DBId + 6;
    QVariant data(ui->frequency->value());
    QList<uint> ids;
    QList<QVariant> datas;
    ids.append(id);
    datas.append(data);
    emit writeNodes(ids, datas);
}

void DBDetails::on_frequencyGet_clicked()//获取采样频率
{
    uint id = DBId + 6;
    QList<uint> ids;
    ids.append(id);
    emit readNodes(ids);
}

void DBDetails::on_samplingPointsSet_clicked()//平均数设置
{
    uint id = DBId + 7;
    QVariant data(ui->samplingPoints->value());
    QList<uint> ids;
    QList<QVariant> datas;
    ids.append(id);
    datas.append(data);
    emit writeNodes(ids, datas);
}

void DBDetails::on_samplingPointsGet_clicked()//获取平均数
{
    uint id = DBId + 7;
    QList<uint> ids;
    ids.append(id);
    emit readNodes(ids);
}

void DBDetails::ON_daqModeGroup_clicked(int Check_id)//采样模式设置
{
    printf("checkId %d", Check_id);
    uint id = DBId + 1;
    QVariant data(static_cast<bool>(Check_id));
    QList<uint> ids;
    QList<QVariant> datas;
    ids.append(id);
    datas.append(data);
    emit writeNodes(ids, datas);
}

void DBDetails::ON_motionGroup_clicked(int Check_id)//启动控制设置
{
    printf("checkId %d", Check_id);
    uint id = DBId + 3;
    QVariant data(static_cast<bool>(Check_id));
    QList<uint> ids;
    QList<QVariant> datas;
    ids.append(id);
    datas.append(data);
    emit writeNodes(ids, datas);
}

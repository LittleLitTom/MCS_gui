#include "interps.h"
#include "ui_interps.h"
#include <bitset>
#include "utilities.h"

//PS id格式：MN-XA-BC-DE-FG
//MN：子系统代号，XA：磁铁类型，BC：磁铁区域段编号，DE：磁铁序号，FG：控制变量
//磁铁子系统：01，子系统数 < 20
//XA:(1)Q铁 (2)B铁 (3)STX (4)STY

interps::interps(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::interps)
{
    ui->setupUi(this);

    //界面初始化时,默认选中电源Q1E
    currentPsName = "Q1E";
    currentPsId = utilities::psIdToNum(currentPsName);
    ui->PSId->setText("电源编号: " + currentPsName + "    Id: " + QString::number(currentPsId));
    

    //为树型目录的元素加入选择框，并设置为不可选状态
    QTreeWidgetItemIterator it(ui->treeWidget);
    while (*it)
    {
        //将电源item文本存入自定义数据中(后续可能会更新电源item文本)
        //自定义数据是QStringList,包含三个Qstring,[1]为电源名称，[2]为电源电流，[3]为电源电压；他们都将在树形目录的item中显示
        QStringList Tem;
        Tem << (*it)->text(0) << " " << " ";
        myPsData[utilities::psIdToNum((*it)->text(0))] = Tem;

        (*it)->setCheckState(0,Qt::Unchecked);
        (*it)->setFlags(Qt::ItemIsAutoTristate|Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsEnabled);
        it++;
    }
    //信号与槽：用于树形目电源条目的选择
    connect(ui->treeWidget, &QTreeWidget::itemActivated,this,&interps::onTreeItemActive);
}

interps::~interps()
{
    delete ui;
}

void interps::display_value(uint psId, QVariant data)
{
    //电源项
    //根目录: itemAt(0,0),  磁铁编号: psId / 100 % 100 -1, 磁铁区域: psId / 10000 % 100 -1,  磁铁类型: psId / 1000000 % 100 -1
    auto item = ui->treeWidget->itemAt(0, 0)->child(psId / 10000 % 100-1)->child(psId / 1000000 % 100-1)->child(psId / 100 % 100 - 1);
    
    //电源控制变量
    int psProperty = psId % 100;
    //电源Id
    uint psIdentify = psId / 100 * 100;

    //switch
    if (psProperty == 1)
    {

    }
    //current
    else if (psProperty == 2)
    {
        float current = data.toFloat();

        //显示在电源监控界面的左侧条目上
        myPsData[psIdentify][1] = "Current: " + QString::number(current, 10, 3) + "A";
        item->setText(0, myPsData[psIdentify][0] + "  " + myPsData[psIdentify][1] + "  " + myPsData[psIdentify][2]);
    }
    //voltage
    else if (psProperty == 3)
    {
        float voltage = data.toFloat();

        //显示在电源监控界面的左侧条目上
        myPsData[psIdentify][2] = "Voltage: " + QString::number(voltage, 10, 3) + "V";
        item->setText(0, myPsData[psIdentify][0] + "  " + myPsData[psIdentify][1] + "  " + myPsData[psIdentify][2]);
    }
    //reset
    else if (psProperty == 4)
    {

    }
    //mode
    else if (psProperty == 5)
    {

    }
    //status
    //status状态位：
    //Bit0:工作状态(0:ok,1:error)
    //Bit1:开关状态(0:关,1:开)；
    //Bit2:连锁状态状态(0:关,1:开)；
    //......各种故障状态；
    //Bit13:操作优先级(1:远控,0:本控)；
    //Bit14、15:电源工作模式(00:直接,01:列表,10:Cycle,11:等待)；
    else if (psProperty == 6)
    {
        std::bitset<16> status(data.toUInt());

        //显示在电源监控界面的左侧条目上
        QString statusIcon;
        if (status[0] == 0) // 电源状态正常
        {
            if (status[1] == 0) //电源开
            {
                statusIcon = ":/Resources/light_on.png";
            }
            else  //电源关
            {
                statusIcon = ":/Resources/light_off.png";
            }
        }
        else  //电源故障
        {
            statusIcon = ":/Resources/light_off.png";
        }
        item->setIcon(0, QIcon(statusIcon));
    }
    //currentMaxSet
    else if (psProperty == 7)
    {

    }
    //controlMode
    else if (psProperty == 8)
    {

    }
    //currentSet
    else if (psProperty == 9)
    {

    }
    //listStart
    else if (psProperty == 10)
    {

    }
    //ListTrigger
    else if (psProperty == 11)
    {

    }
    //ListPoint
    else if (psProperty == 12)
    {

    }
    //ListSet
    else if (psProperty == 13)
    {

    }
    //ListFlat
    else if (psProperty == 14)
    {

    }
    //CycleUp
    else if (psProperty == 15)
    {

    }
    //CycleDown
    else if (psProperty == 16)
    {

    }
    //CycleFlat
    else if (psProperty == 17)
    {

    }
    //CycleCount
    else if (psProperty == 18)
    {

    }
    //CycleStart
    else if (psProperty == 19)
    {

    }
    //CycleDownFlat
    else if (psProperty == 20)
    {

    }
    //CycleFlatCurrent
    else if (psProperty == 21)
    {

    }
    //CycleSave
    else if (psProperty == 22)
    {

    }
    //StandBy
    else if (psProperty == 23)
    {

    }
}

//回收信号(read结果),并在右端界面显示
void interps::process_read_results(QList<uint>ids, QList<QVariant>datas, QList<int>results)
{
    int i = 0;
    for (auto id : ids)
    {
        if (id == currentPsId + 7)//currentMax
        {
            ui->CurrentMax->setValue(datas.at(i).toDouble());
        }
        else if (id = currentPsId + 9)//current
        {
            ui->Current->setValue(datas.at(i).toDouble());
        }
        i++;
    }
}

//回收信号(write结果)，并处理
void interps::process_write_results(QList<uint> ids, QList<int> results)
{
    //......
}

//树形目切换电源
void interps::onTreeItemActive(QTreeWidgetItem* item, int column)
{
    //使用split函数以" "符将QString切分，得PSname
    auto name = item->text(column).split(" ")[0];
    auto id = utilities::psIdToNum(name);
    currentPsName = id ? name : currentPsName;
    currentPsId = id ? id : currentPsId;

    ui->PSId->setText("电源编号: " + currentPsName + "    Id: " + QString::number(currentPsId));
}


void interps::on_tabWidget_currentChanged(int index)
{
    if(index == 3)//此时位Tab位于批量设置，复选框可选
    {
        QTreeWidgetItemIterator it(ui->treeWidget);
        while (*it)
        {
            (*it)->setFlags(Qt::ItemIsAutoTristate|Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
            it++;
        }
    }
    else//此时Tab不位于批量设置，复选框不可选
    {
        QTreeWidgetItemIterator it(ui->treeWidget);
        while (*it)
        {
            (*it)->setFlags(Qt::ItemIsAutoTristate|Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsEnabled);
            it++;
        }
    }
}

//设置电流
void interps::on_CurrentSet_clicked()
{
    QList<uint> ids;
    QList<QVariant> datas;
    //currentSet的偏移量为9，偏移量定义详见电源文档或identifierGenerator工程
    ids.append(currentPsId + 9);
    datas.append(QVariant(float(ui->Current->value())));
    emit writeNodes(ids,datas);
}
//回读电流设置值
void interps::on_CurrentGet_clicked()
{
    QList<uint> ids;
    ids.append(currentPsId + 9);
    emit readNodes(ids);
}
//设置电流最大值
void interps::on_CurrentMaxSet_clicked()
{
    QList<uint> ids;
    QList<QVariant> datas;
    //currentMax的偏移量为7，偏移量定义详见电源文档或identifierGenerator工程
    ids.append(currentPsId + 7);
    datas.append(QVariant(float(ui->Current->value())));
    emit writeNodes(ids, datas);
}
//回读电流最大值设置值
void interps::on_CurrentMaxGet_clicked()
{
    QList<uint> ids;
    ids.append(currentPsId + 9);
    emit readNodes(ids);
}

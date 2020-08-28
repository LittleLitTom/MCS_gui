#include "interps.h"
#include "ui_interps.h"

#include <bitset>

//PS id格式：A-BC-DE-FG
//A：磁铁类型；BC：磁铁区域段编号；DE：磁铁序号；FG：控制变量
//A:(1)Q铁 (2)B铁 (3)STX (4)STY

interps::interps(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::interps)
{
    ui->setupUi(this);

    //为树型目录的元素加入选择框，并设置为不可选状态
    QTreeWidgetItemIterator it(ui->treeWidget);
    while (*it)
    {
        //将电源item文本存入自定义数据中(后续可能会更新电源item文本)
        (*it)->setData(0, Qt::UserRole,(*it)->text(0));
        (*it)->setCheckState(0,Qt::Unchecked);
        (*it)->setFlags(Qt::ItemIsAutoTristate|Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsEnabled);
        it++;
    }
}

interps::~interps()
{
    delete ui;
}

void interps::display_value(int psId, uint data)
{
    //电源项
    //itemAt(0,0):根目录；psId / 100 % 100：磁铁编号；psId / 1000000 % 100：磁铁类型；psId / 10000 % 100：磁铁区域
    auto item = ui->treeWidget->itemAt(0, 0)->child(psId / 10000 % 100)->child(psId / 1000000 % 100)->child(psId / 100 % 100);

    //电源控制变量
    int psProperty = psId % 100;

    //switch
    if (psProperty == 1)
    {

    }
    //current
    else if (psProperty == 2)
    {
        float current = data;
        item->setText(0,"ee");
    }
    //voltage
    else if (psProperty == 3)
    {

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
        std::bitset<16> status(data);
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

#include "accelerater.h"
#include "ui_accelerater.h"


accelerater::accelerater(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::accelerater)
{
    ui->setupUi(this);

    //对加速器部件进行初始化
    acceleratorInitialize();
    //为Accelerator界面中的所有控件加上ToolTip和StatusTip
    auto objectList = ui->frame->children();
    for(int i=0;i<objectList.length();i++)
    {
        auto o = objectList.at(i);
        if (o->inherits("QPushButton")) {
        QPushButton* b = qobject_cast<QPushButton*>(o);
        b->setToolTip(b->objectName());
        b->setStatusTip(b->objectName());
        }
    }
    //信号与槽(束线状态指示灯)
    this->connect(this,&accelerater::beamStateChanged,this,&accelerater::changeWidgetStyle);
    //初始化束线状态(无束流)
    m_beamState = 0;
}


accelerater::~accelerater()
{
    delete ui;
}

//与束线状态量"m_beamState"绑定,改变束线状态
void accelerater::changeWidgetStyle()
{
    QString image = "QFrame{background-image: url(:/Resources/line_";
    ui->frame->setStyleSheet(image + QString::number(m_beamState)+".png);}");
}


void accelerater::acceleratorInitialize()
{
    //kicker
    ui->Kicker->setProperty("type",0);ui->Kicker->setProperty("location",1);ui->Kicker->setProperty("state",false);

    //magnet
    //q
    ui->Q1E->setProperty("type",1);ui->Q1E->setProperty("location",1);ui->Q1E->setProperty("state",false);
    ui->Q2E->setProperty("type",1);ui->Q2E->setProperty("location",1);ui->Q2E->setProperty("state",false);
    ui->Q3E->setProperty("type",1);ui->Q3E->setProperty("location",1);ui->Q3E->setProperty("state",false);
    ui->Q4E->setProperty("type",1);ui->Q4E->setProperty("location",1);ui->Q4E->setProperty("state",false);
    ui->Q5E->setProperty("type",1);ui->Q5E->setProperty("location",1);ui->Q5E->setProperty("state",false);

    ui->Q6E->setProperty("type",1);ui->Q6E->setProperty("location",2);ui->Q6E->setProperty("state",false);
    ui->Q7E->setProperty("type",1);ui->Q7E->setProperty("location",2);ui->Q7E->setProperty("state",false);
    ui->Q8E->setProperty("type",1);ui->Q8E->setProperty("location",2);ui->Q8E->setProperty("state",false);
    ui->Q9E->setProperty("type",1);ui->Q9E->setProperty("location",2);ui->Q9E->setProperty("state",false);

    ui->Q10E->setProperty("type",1);ui->Q10E->setProperty("location",3);ui->Q10E->setProperty("state",false);
    ui->Q11E->setProperty("type",1);ui->Q11E->setProperty("location",3);ui->Q11E->setProperty("state",false);
    ui->Q1S1->setProperty("type",1);ui->Q1S1->setProperty("location",3);ui->Q1S1->setProperty("state",false);
    ui->Q2S1->setProperty("type",1);ui->Q2S1->setProperty("location",3);ui->Q2S1->setProperty("state",false);

    ui->Q3S1->setProperty("type",1);ui->Q3S1->setProperty("location",4);ui->Q3S1->setProperty("state",false);
    ui->Q4S1->setProperty("type",1);ui->Q4S1->setProperty("location",4);ui->Q4S1->setProperty("state",false);
    ui->Q5S1->setProperty("type",1);ui->Q5S1->setProperty("location",4);ui->Q5S1->setProperty("state",false);

    ui->Q6S1->setProperty("type",1);ui->Q6S1->setProperty("location",1);ui->Q6S1->setProperty("state",false);
    ui->Q7S1->setProperty("type",1);ui->Q7S1->setProperty("location",1);ui->Q7S1->setProperty("state",false);
    ui->Q1F1->setProperty("type",1);ui->Q1F1->setProperty("location",1);ui->Q1F1->setProperty("state",false);
    ui->Q2F1->setProperty("type",1);ui->Q2F1->setProperty("location",1);ui->Q2F1->setProperty("state",false);
    ui->Q3F1->setProperty("type",1);ui->Q3F1->setProperty("location",1);ui->Q3F1->setProperty("state",false);

    ui->Q1P2->setProperty("type",1);ui->Q1P2->setProperty("location",3);ui->Q1P2->setProperty("state",false);
    ui->Q2P2->setProperty("type",1);ui->Q2P2->setProperty("location",3);ui->Q2P2->setProperty("state",false);
    ui->Q3P2->setProperty("type",1);ui->Q3P2->setProperty("location",3);ui->Q3P2->setProperty("state",false);
    ui->Q4P2->setProperty("type",1);ui->Q4P2->setProperty("location",3);ui->Q4P2->setProperty("state",false);
    ui->Q5P2->setProperty("type",1);ui->Q5P2->setProperty("location",3);ui->Q5P2->setProperty("state",false);
    ui->Q6P2->setProperty("type",1);ui->Q6P2->setProperty("location",3);ui->Q6P2->setProperty("state",false);
    ui->Q1S2->setProperty("type",1);ui->Q1S2->setProperty("location",3);ui->Q1S2->setProperty("state",false);
    ui->Q2S2->setProperty("type",1);ui->Q2S2->setProperty("location",3);ui->Q2S2->setProperty("state",false);

    ui->Q3S2->setProperty("type",1);ui->Q3S2->setProperty("location",4);ui->Q3S2->setProperty("state",false);
    ui->Q4S2->setProperty("type",1);ui->Q4S2->setProperty("location",4);ui->Q4S2->setProperty("state",false);
    ui->Q5S2->setProperty("type",1);ui->Q5S2->setProperty("location",4);ui->Q5S2->setProperty("state",false);

    ui->Q6S2->setProperty("type",1);ui->Q6S2->setProperty("location",1);ui->Q6S2->setProperty("state",false);
    ui->Q7S2->setProperty("type",1);ui->Q7S2->setProperty("location",1);ui->Q7S2->setProperty("state",false);
    ui->Q1G2->setProperty("type",1);ui->Q1G2->setProperty("location",1);ui->Q1G2->setProperty("state",false);

    ui->Q2G2->setProperty("type",1);ui->Q2G2->setProperty("location",3);ui->Q2G2->setProperty("state",false);
    ui->Q3G2->setProperty("type",1);ui->Q3G2->setProperty("location",3);ui->Q3G2->setProperty("state",false);
    ui->Q4G2->setProperty("type",1);ui->Q4G2->setProperty("location",3);ui->Q4G2->setProperty("state",false);
    ui->Q5G2->setProperty("type",1);ui->Q5G2->setProperty("location",3);ui->Q5G2->setProperty("state",false);
    ui->Q6G2->setProperty("type",1);ui->Q6G2->setProperty("location",3);ui->Q6G2->setProperty("state",false);

    ui->Q1P3->setProperty("type",1);ui->Q1P3->setProperty("location",3);ui->Q1P3->setProperty("state",false);
    ui->Q2P3->setProperty("type",1);ui->Q2P3->setProperty("location",3);ui->Q2P3->setProperty("state",false);
    ui->Q3P3->setProperty("type",1);ui->Q3P3->setProperty("location",3);ui->Q3P3->setProperty("state",false);
    ui->Q4P3->setProperty("type",1);ui->Q4P3->setProperty("location",3);ui->Q4P3->setProperty("state",false);
    ui->Q5P3->setProperty("type",1);ui->Q5P3->setProperty("location",3);ui->Q5P3->setProperty("state",false);
    ui->Q6P3->setProperty("type",1);ui->Q6P3->setProperty("location",3);ui->Q6P3->setProperty("state",false);
    ui->Q1S3->setProperty("type",1);ui->Q1S3->setProperty("location",3);ui->Q1S3->setProperty("state",false);
    ui->Q2S3->setProperty("type",1);ui->Q2S3->setProperty("location",3);ui->Q2S3->setProperty("state",false);

    ui->Q3S3->setProperty("type",1);ui->Q3S3->setProperty("location",4);ui->Q3S3->setProperty("state",false);
    ui->Q4S3->setProperty("type",1);ui->Q4S3->setProperty("location",4);ui->Q4S3->setProperty("state",false);
    ui->Q5S3->setProperty("type",1);ui->Q5S3->setProperty("location",4);ui->Q5S3->setProperty("state",false);

    ui->Q6S3->setProperty("type",1);ui->Q6S3->setProperty("location",1);ui->Q6S3->setProperty("state",false);
    ui->Q7S3->setProperty("type",1);ui->Q7S3->setProperty("location",1);ui->Q7S3->setProperty("state",false);
    ui->Q1G3->setProperty("type",1);ui->Q1G3->setProperty("location",1);ui->Q1G3->setProperty("state",false);

    ui->Q2G3->setProperty("type",1);ui->Q2G3->setProperty("location",3);ui->Q2G3->setProperty("state",false);
    ui->Q3G3->setProperty("type",1);ui->Q3G3->setProperty("location",3);ui->Q3G3->setProperty("state",false);
    ui->Q4G3->setProperty("type",1);ui->Q4G3->setProperty("location",3);ui->Q4G3->setProperty("state",false);
    ui->Q5G3->setProperty("type",1);ui->Q5G3->setProperty("location",3);ui->Q5G3->setProperty("state",false);
    ui->Q6G3->setProperty("type",1);ui->Q6G3->setProperty("location",3);ui->Q6G3->setProperty("state",false);

    //B
    ui->B1E->setProperty("type",2);ui->B1E->setProperty("location",1);ui->B1E->setProperty("state",false);
    ui->B2E->setProperty("type",2);ui->B2E->setProperty("location",2);ui->B2E->setProperty("state",false);
    ui->B1S1->setProperty("type",2);ui->B1S1->setProperty("location",3);ui->B1S1->setProperty("state",false);
    ui->B2S1->setProperty("type",2);ui->B2S1->setProperty("location",4);ui->B2S1->setProperty("state",false);
    ui->B1S2->setProperty("type",2);ui->B1S2->setProperty("location",3);ui->B1S2->setProperty("state",false);
    ui->B2S2->setProperty("type",2);ui->B2S2->setProperty("location",4);ui->B2S2->setProperty("state",false);
    ui->B1G2->setProperty("type",2);ui->B1G2->setProperty("location",5);ui->B1G2->setProperty("state",false);
    ui->B2G2->setProperty("type",2);ui->B2G2->setProperty("location",6);ui->B2G2->setProperty("state",false);
    ui->B3G2->setProperty("type",2);ui->B3G2->setProperty("location",7);ui->B3G2->setProperty("state",false);
    ui->B1S3->setProperty("type",2);ui->B1S3->setProperty("location",3);ui->B1S3->setProperty("state",false);
    ui->B2S3->setProperty("type",2);ui->B2S3->setProperty("location",4);ui->B2S3->setProperty("state",false);
    ui->B1G3->setProperty("type",2);ui->B1G3->setProperty("location",5);ui->B1G3->setProperty("state",false);
    ui->B2G3->setProperty("type",2);ui->B2G3->setProperty("location",6);ui->B2G3->setProperty("state",false);
    ui->B3G3->setProperty("type",2);ui->B3G3->setProperty("location",7);ui->B3G3->setProperty("state",false);

    //ST
    ui->STX1E->setProperty("type",3);ui->STX1E->setProperty("location",1);ui->STX1E->setProperty("state",false);
    ui->STY1E->setProperty("type",3);ui->STY1E->setProperty("location",1);ui->STY1E->setProperty("state",false);
    ui->STX2E->setProperty("type",3);ui->STX2E->setProperty("location",1);ui->STX2E->setProperty("state",false);
    ui->STX3E->setProperty("type",3);ui->STX3E->setProperty("location",1);ui->STX3E->setProperty("state",false);

    ui->STY2E->setProperty("type",3);ui->STY2E->setProperty("location",2);ui->STY2E->setProperty("state",false);

    ui->STY3E->setProperty("type",3);ui->STY3E->setProperty("location",3);ui->STY3E->setProperty("state",false);

    ui->STX1S1->setProperty("type",3);ui->STX1S1->setProperty("location",1);ui->STX1S1->setProperty("state",false);
    ui->STY1S1->setProperty("type",3);ui->STY1S1->setProperty("location",1);ui->STY1S1->setProperty("state",false);
    ui->STX1F1->setProperty("type",3);ui->STX1F1->setProperty("location",1);ui->STX1F1->setProperty("state",false);
    ui->STY1F1->setProperty("type",3);ui->STY1F1->setProperty("location",1);ui->STY1F1->setProperty("state",false);
    ui->STX2F1->setProperty("type",3);ui->STX2F1->setProperty("location",1);ui->STX2F1->setProperty("state",false);

    ui->STX1P2->setProperty("type",3);ui->STX1P2->setProperty("location",3);ui->STX1P2->setProperty("state",false);
    ui->STY1P2->setProperty("type",3);ui->STY1P2->setProperty("location",3);ui->STY1P2->setProperty("state",false);
    ui->STX2P2->setProperty("type",3);ui->STX2P2->setProperty("location",3);ui->STX2P2->setProperty("state",false);
    ui->STY1S2->setProperty("type",3);ui->STY1S2->setProperty("location",3);ui->STY1S2->setProperty("state",false);

    ui->STX1S2->setProperty("type",3);ui->STX1S2->setProperty("location",1);ui->STX1S2->setProperty("state",false);

    ui->STX1G2->setProperty("type",3);ui->STX1G2->setProperty("location",3);ui->STX1G2->setProperty("state",false);
    ui->STY1G2->setProperty("type",3);ui->STY1G2->setProperty("location",3);ui->STY1G2->setProperty("state",false);
    ui->STY2G2->setProperty("type",3);ui->STY2G2->setProperty("location",3);ui->STY2G2->setProperty("state",false);
    ui->STX2G2->setProperty("type",3);ui->STX2G2->setProperty("location",3);ui->STX2G2->setProperty("state",false);

    ui->STY3G2->setProperty("type",3);ui->STY3G2->setProperty("location",1);ui->STY3G2->setProperty("state",false);

    ui->STX1P3->setProperty("type",3);ui->STX1P3->setProperty("location",3);ui->STX1P3->setProperty("state",false);
    ui->STY1P3->setProperty("type",3);ui->STY1P3->setProperty("location",3);ui->STY1P3->setProperty("state",false);
    ui->STX2P3->setProperty("type",3);ui->STX2P3->setProperty("location",3);ui->STX2P3->setProperty("state",false);
    ui->STY1S3->setProperty("type",3);ui->STY1S3->setProperty("location",3);ui->STY1S3->setProperty("state",false);

    ui->STX1S3->setProperty("type",3);ui->STX1S3->setProperty("location",1);ui->STX1S3->setProperty("state",false);

    ui->STX1G3->setProperty("type",3);ui->STX1G3->setProperty("location",3);ui->STX1G3->setProperty("state",false);
    ui->STY1G3->setProperty("type",3);ui->STY1G3->setProperty("location",3);ui->STY1G3->setProperty("state",false);
    ui->STY2G3->setProperty("type",3);ui->STY2G3->setProperty("location",3);ui->STY2G3->setProperty("state",false);
    ui->STX2G3->setProperty("type",3);ui->STX2G3->setProperty("location",3);ui->STX2G3->setProperty("state",false);

    ui->STY3G3->setProperty("type",3);ui->STY3G3->setProperty("location",1);ui->STY3G3->setProperty("state",false);

    //FC
    ui->FC1E->setProperty("type",1);ui->FC1E->setProperty("location",1);ui->FC1E->setProperty("state",false);
    ui->FC1S1->setProperty("type",1);ui->FC1S1->setProperty("location",1);ui->FC1S1->setProperty("state",false);
    ui->FC2S1->setProperty("type",1);ui->FC2S1->setProperty("location",1);ui->FC2S1->setProperty("state",false);
    ui->FC1S2->setProperty("type",1);ui->FC1S2->setProperty("location",1);ui->FC1S2->setProperty("state",false);
    ui->FC2S2->setProperty("type",1);ui->FC2S2->setProperty("location",1);ui->FC2S2->setProperty("state",false);
    ui->FC1S3->setProperty("type",1);ui->FC1S3->setProperty("location",1);ui->FC1S3->setProperty("state",false);
    ui->FC2S3->setProperty("type",1);ui->FC2S3->setProperty("location",1);ui->FC2S3->setProperty("state",false);

    //SC
    ui->SC1E->setProperty("type",2);ui->SC1E->setProperty("location",1);ui->SC1E->setProperty("state",false);
    ui->SC2E->setProperty("type",2);ui->SC2E->setProperty("location",1);ui->SC2E->setProperty("state",false);
    ui->SC3E->setProperty("type",2);ui->SC3E->setProperty("location",2);ui->SC3E->setProperty("state",false);
    ui->SC1S1->setProperty("type",2);ui->SC1S1->setProperty("location",3);ui->SC1S1->setProperty("state",false);
    ui->SC2S1->setProperty("type",2);ui->SC2S1->setProperty("location",4);ui->SC2S1->setProperty("state",false);
    ui->SC3S1->setProperty("type",2);ui->SC3S1->setProperty("location",1);ui->SC3S1->setProperty("state",false);
    ui->SC1F1->setProperty("type",2);ui->SC1F1->setProperty("location",1);ui->SC1F1->setProperty("state",false);
    ui->SC1P2->setProperty("type",2);ui->SC1P2->setProperty("location",3);ui->SC1P2->setProperty("state",false);
    ui->SC2P2->setProperty("type",2);ui->SC2P2->setProperty("location",3);ui->SC2P2->setProperty("state",false);
    ui->SC3P2->setProperty("type",2);ui->SC3P2->setProperty("location",3);ui->SC3P2->setProperty("state",false);
    ui->SC1S2->setProperty("type",2);ui->SC1S2->setProperty("location",3);ui->SC1S2->setProperty("state",false);
    ui->SC2S2->setProperty("type",2);ui->SC2S2->setProperty("location",4);ui->SC2S2->setProperty("state",false);
    ui->SC3S2->setProperty("type",2);ui->SC3S2->setProperty("location",1);ui->SC3S2->setProperty("state",false);
    ui->SC1P3->setProperty("type",2);ui->SC1P3->setProperty("location",3);ui->SC1P3->setProperty("state",false);
    ui->SC2P3->setProperty("type",2);ui->SC2P3->setProperty("location",3);ui->SC2P3->setProperty("state",false);
    ui->SC3P3->setProperty("type",2);ui->SC3P3->setProperty("location",3);ui->SC3P3->setProperty("state",false);
    ui->SC1S3->setProperty("type",2);ui->SC1S3->setProperty("location",3);ui->SC1S3->setProperty("state",false);
    ui->SC2S3->setProperty("type",2);ui->SC2S3->setProperty("location",4);ui->SC2S3->setProperty("state",false);
    ui->SC3S3->setProperty("type",2);ui->SC3S3->setProperty("location",1);ui->SC3S3->setProperty("state",false);

    //IC
    ui->IC1F1->setProperty("type",3);ui->IC1F1->setProperty("location",1);ui->IC1F1->setProperty("state",false);
    ui->IC1G2->setProperty("type",3);ui->IC1G2->setProperty("location",1);ui->IC1G2->setProperty("state",false);
    ui->IC2G2->setProperty("type",3);ui->IC2G2->setProperty("location",1);ui->IC2G2->setProperty("state",false);
    ui->IC3G2->setProperty("type",3);ui->IC3G2->setProperty("location",3);ui->IC3G2->setProperty("state",false);
    ui->IC4G2->setProperty("type",3);ui->IC4G2->setProperty("location",3);ui->IC4G2->setProperty("state",false);
    ui->IC1G3->setProperty("type",3);ui->IC1G3->setProperty("location",1);ui->IC1G3->setProperty("state",false);
    ui->IC2G3->setProperty("type",3);ui->IC2G3->setProperty("location",1);ui->IC2G3->setProperty("state",false);
    ui->IC3G3->setProperty("type",3);ui->IC3G3->setProperty("location",3);ui->IC3G3->setProperty("state",false);
    ui->IC4G3->setProperty("type",3);ui->IC4G3->setProperty("location",3);ui->IC4G3->setProperty("state",false);
}
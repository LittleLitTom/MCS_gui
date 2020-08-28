#include "qpsbutton.h"
#include <QBitmap>

QPSButton::QPSButton(QWidget *parent) : QPushButton(parent)
{
    this->connect(this,&QPushButton::clicked,this,&QPSButton::onclick);
    //将状态指示灯与电源状态联系
    this->connect(this,&QPSButton::stateChanged,this,&QPSButton::changeButtonStyle);

    //初始化父子界面
    PSDialog_ = nullptr;
    //初始化电源灯状态
    m_state = true;
    m_type = 4;
    m_location = 99999;
}

void QPSButton::onclick()
{
    PSDialog_ = new PSDialog(this, objectName());
    PSDialog_->show();
}

//电源的状态指示灯改变，电源状态有on,off,error三种
void QPSButton::changeButtonStyle()
{
    QString image = ":/Resources/";
    QString par1,par2;
    switch (m_type)
    {
        case 0:
            par1 = "Kicker";
            break;
        case 1:
            par1 = "q";
            break;
        case 2:
            par1 = "B";
            break;
        case 3:
            par1 = "ST";
            break;
        case 4:
            return;
    }

    //电源开启
    if(m_state == 1)
        par2 = "on";
    //电源关闭
    else if(m_state == 0)
        par2 = "off";
    //电源故障
    else if(m_state == 2)
        par2 = "err";
    image = image + par1 + par2 + "_" + QString::number(m_location) + ".png";

    //设置Mask会带来锯齿、图片变形的问题,因此视情况而定
    //QPixmap pixmap(image);
    //setMask(pixmap.mask());
    setStyleSheet("QPushButton#"+objectName()+"{background-image: url("+image +");}");
}

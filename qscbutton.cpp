#include "qscbutton.h"
#include <QBitmap>

QSCButton::QSCButton(QWidget *parent) : QPushButton(parent)
{
    this->connect(this,&QPushButton::clicked,this,&QSCButton::onclick);
    //状态指示灯
    this->connect(this,&QSCButton::stateChanged,this,&QSCButton::changeButtonStyle);

    //initialize
    m_state = true;
    m_type = 4;
    m_location = 99999;
}


void QSCButton::onclick()
{
    DBDetails_ = new DBDetails(nullptr,objectName());
    DBDetails_->show();
}

void QSCButton::changeButtonStyle()
{
    QString image = ":/Resources/";
    QString par1,par2;
    switch (m_type)
    {
        case 1:
            par1 = "FC";
            break;
        case 2:
            par1 = "SC";
            break;
        case 3:
            par1 = "IC";
            break;
        case 4:
            return;
    }
    if(m_state == 1)
        par2 = "on";
    else if(m_state == 0)
        par2 = "off";
    else if(m_state == 2)
        par2 = "err";
    image = image + par1 + par2 +"_" + QString::number(m_location) + ".png";
    //设置Mask会带来锯齿、图片变形的问题
    //QPixmap pixmap(image);
    //setMask(pixmap.mask());
    setStyleSheet("QPushButton{background-image: url(" + image + ");}");
}

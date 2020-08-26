#include "powersupply.h"
#include <QThread>

PowerSupply::PowerSupply(QObject *parent) : QObject(parent)
{
    UaPlatformLayer::init();
    SampleClient* myclient = new SampleClient();
    delete myclient;
    myclient = nullptr;
    UaPlatformLayer::cleanup();
}


void PowerSupply::test()
{
    static int nu = 0;

    while(true)
    {
        QThread::msleep(100);
       emit st(nu);
        if(nu == 0)
        {
            nu =1;
        }
        else
        {
            nu = 0;
        }
    }
}

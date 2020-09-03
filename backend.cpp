#include "backend.h"
#include <QThread>


Backend::Backend(QObject *parent) : QObject(parent)
{
    UaPlatformLayer::init();
    myClient = new SampleClient(this);
    myClient->connect();
}

Backend::~Backend()
{
    myClient->unsubscribe();
    myClient->disconnect();
    delete myClient;
    myClient = nullptr;
    UaPlatformLayer::cleanup();
}

//开始数据采集工作
void Backend::runAcquisition()
{
    //采集线程等待5s，目的是让界面线程做好准备
    std::this_thread::sleep_for(std::chrono::seconds(5));
    //开始采集
    myClient->subscribe();
}


void Backend::emitDataChange(uint id, QVariant data)
{
    emit dataChange(id, data);
}

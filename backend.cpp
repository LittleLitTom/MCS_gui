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

//��ʼ���ݲɼ�����
void Backend::runAcquisition()
{
    //�ɼ��̵߳ȴ�5s��Ŀ�����ý����߳�����׼��
    std::this_thread::sleep_for(std::chrono::seconds(5));
    //��ʼ�ɼ�
    myClient->subscribe();
}


void Backend::emitDataChange(uint id, QVariant data)
{
    emit dataChange(id, data);
}

#include "backend.h"
#include <QThread>


Backend::Backend(QObject *parent) : QObject(parent)
{
    UaPlatformLayer::init();
    myClient = new SampleClient(this);
    myClient->connect();
    myClient->subscribe();
}

Backend::~Backend()
{
    myClient->unsubscribe();
    myClient->disconnect();
    delete myClient;
    myClient = nullptr;
    UaPlatformLayer::cleanup();
}


void Backend::emitDataChange(int id, QVariant data)
{
    emit dataChange(id, data);
}

#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include "uaplatformlayer.h"
#include "sampleclient.h"

#include <QVariant>

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);
    virtual ~Backend();

    //开始数据采集
    void runAcquisition();

    void emitDataChange(uint id,QVariant data);

signals:
    void dataChange(uint id,QVariant data);

private:
    //OPC UA客户端
    SampleClient* myClient;
};

#endif // BACKEND_H

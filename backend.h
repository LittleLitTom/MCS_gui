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

    //槽函数：写节点
    void writeNodes(QList<uint>ids, QList<QVariant>datas);
    //槽函数：读节点
    void readNodes(QList<uint> ids);

    void emitDataChange(uint id,QVariant data);

signals:
    //信号：数据变化
    void dataChange(uint id,QVariant data);

    //信号：写节点 results
    void writeNodesResults(QList<uint>ids,QList<int>results);
    //信号：读节点 results
    void readNodesResults(QList<uint>ids,QList<QVariant>datas,QList<int>results);

private:
    //OPC UA客户端
    SampleClient* myClient;
};

#endif // BACKEND_H

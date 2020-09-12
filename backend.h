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

    //��ʼ���ݲɼ�
    void runAcquisition();

    //�ۺ�����д�ڵ�
    void writeNodes(QList<uint>ids, QList<QVariant>datas);
    //�ۺ��������ڵ�
    void readNodes(QList<uint> ids);

    void emitDataChange(uint id,QVariant data);

signals:
    //�źţ����ݱ仯
    void dataChange(uint id,QVariant data);

    //�źţ�д�ڵ� results
    void writeNodesResults(QList<uint>ids,QList<int>results);
    //�źţ����ڵ� results
    void readNodesResults(QList<uint>ids,QList<QVariant>datas,QList<int>results);

private:
    //OPC UA�ͻ���
    SampleClient* myClient;
};

#endif // BACKEND_H

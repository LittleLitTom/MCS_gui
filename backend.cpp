#include "backend.h"
#include "utilities.h"

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
    //�ɼ��̵߳ȴ�5s��Ŀ�����ý����߳�����׼�����ý�����ȫ��ȡ��һ�ε�����
    std::this_thread::sleep_for(std::chrono::seconds(5));
    //��ʼ�ɼ�
    myClient->subscribe();
}

void Backend::writeNodes(QList<uint> ids, QList<QVariant> datas)
{
    //׼������(OPC UA)
    UaStatus result;
    UaWriteValues writeValues;
    UaStatusCodeArray statusArray;
    //׼������(Qt)
    UaVariant Tem;
    QList<int> results;

    //��ֵ����
    writeValues.create(ids.count());
    uint i = 0;
    for (auto data : datas)//���ֱ�����ʽЧ�ʸ���
    {
        writeValues[i].AttributeId = OpcUa_Attributes_Value;
        writeValues[i].NodeId.NamespaceIndex = 2;
        writeValues[i].NodeId.Identifier.Numeric = ids.at(i);
        utilities::QtVarToUaVar(data, Tem);
        OpcUa_Variant_CopyTo(Tem, &writeValues[i].Value.Value);
        i++;
    }

    //ִ��д����
    myClient->write(result, writeValues, statusArray);
    
    //�ش���ֵ�������ź�
    if (result.isGood())
    {
        for (int i =0;i<statusArray.length();i++)
        {
            results.append(statusArray[i]);
        }
        emit writeNodesResults(ids, results);
    }
}


void Backend::readNodes(QList<uint> ids)
{
    //׼������(opc ua)
    UaStatus result;
    UaReadValueIds readValueId;
    UaDataValues dataValue;
    //׼������(Qt)
    QVariant Tem;
    QList<QVariant> datas;
    QList<int> results;

    //��ֵ����
    readValueId.create(ids.count());//ReadId��������
    for (int i = 0; i < ids.count(); i++)
    {
        readValueId[i].AttributeId = OpcUa_Attributes_Value;
        readValueId[i].NodeId.NamespaceIndex = 2;
        readValueId[i].NodeId.Identifier.Numeric = ids[i];
    }

    //ִ�ж�����
    myClient->read(result, readValueId, dataValue);

    //�ش���ֵ�������ź�
    if (result.isGood())
    {
        for (int i = 0; i < ids.count(); i++)
        {
            utilities::UaVarToQtVar(dataValue[i].Value, Tem);
            datas.append(Tem);
            results.append(dataValue[i].StatusCode);
        }
        emit readNodesResults(ids, datas, results);
    }
}

void Backend::emitDataChange(uint id, QVariant data)
{
    emit dataChange(id, data);
}

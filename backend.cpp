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

//开始数据采集工作
void Backend::runAcquisition()
{
    //采集线程等待5s，目的是让界面线程做好准备，让界面完全获取第一次的数据
    std::this_thread::sleep_for(std::chrono::seconds(5));
    //开始采集
    myClient->subscribe();
}

void Backend::writeNodes(QList<uint> ids, QList<QVariant> datas)
{
    //准备参数(OPC UA)
    UaStatus result;
    UaWriteValues writeValues;
    UaStatusCodeArray statusArray;
    //准备参数(Qt)
    UaVariant Tem;
    QList<int> results;

    //赋值参数
    writeValues.create(ids.count());
    uint i = 0;
    for (auto data : datas)//这种遍历方式效率更高
    {
        writeValues[i].AttributeId = OpcUa_Attributes_Value;
        writeValues[i].NodeId.NamespaceIndex = 2;
        writeValues[i].NodeId.Identifier.Numeric = ids.at(i);
        utilities::QtVarToUaVar(data, Tem);
        OpcUa_Variant_CopyTo(Tem, &writeValues[i].Value.Value);
        i++;
    }

    //执行写操作
    myClient->write(result, writeValues, statusArray);
    
    //回传赋值，发射信号
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
    //准备参数(opc ua)
    UaStatus result;
    UaReadValueIds readValueId;
    UaDataValues dataValue;
    //准备参数(Qt)
    QVariant Tem;
    QList<QVariant> datas;
    QList<int> results;

    //赋值参数
    readValueId.create(ids.count());//ReadId数组扩容
    for (int i = 0; i < ids.count(); i++)
    {
        readValueId[i].AttributeId = OpcUa_Attributes_Value;
        readValueId[i].NodeId.NamespaceIndex = 2;
        readValueId[i].NodeId.Identifier.Numeric = ids[i];
    }

    //执行读操作
    myClient->read(result, readValueId, dataValue);

    //回传赋值，发射信号
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

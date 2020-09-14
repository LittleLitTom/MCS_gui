#include "SampleSubscription.h"
#include "uasubscription.h"
#include "uasession.h"

#include "backend.h"
#include "utilities.h"

#include <QtXml>
#include <QtCharts>

#include <iostream>

SampleSubscription::SampleSubscription(Backend* parent_)
	:m_pSession(NULL),
	m_pSubscription(NULL),
    parent(parent_)
{

}

SampleSubscription::~SampleSubscription()
{
    if (m_pSubscription)
    {
        deleteSubscription();
    }
}

void SampleSubscription::subscriptionStatusChanged(OpcUa_UInt32 clientSubscriptionHandle, const UaStatus& status)
{
	OpcUa_ReferenceParameter(clientSubscriptionHandle); // We use the callback only for this subscription
	printf("Subscription not longer valid - failed with status %s\n", status.toString().toUtf8());
}

void SampleSubscription::dataChange(OpcUa_UInt32 clientSubscriptionHandle, const UaDataNotifications& dataNotifications, const UaDiagnosticInfos& diagnosticInfos)
{
    OpcUa_ReferenceParameter(clientSubscriptionHandle); // We use the callback only for this subscription
    OpcUa_ReferenceParameter(diagnosticInfos);
    OpcUa_UInt32 i = 0;
    printf("-- DataChange Notification ---------------------------------\n");
    for (i = 0; i < dataNotifications.length(); i++)
    {
        if (OpcUa_IsGood(dataNotifications[i].Value.StatusCode))
        {
            QVariant tempValue;
            utilities::UaVarToQtVar(UaVariant(dataNotifications[i].Value.Value), tempValue);
            //将OPC UA监视项的变化作为信号发射出去
            parent->emitDataChange(dataNotifications[i].ClientHandle,tempValue);
        }
        else
        {
            UaStatus itemError(dataNotifications[i].Value.StatusCode);
            printf("  Variable %d failed with status %s\n", dataNotifications[i].ClientHandle, itemError.toString().toUtf8());
        }
    }
    printf("------------------------------------------------------------\n");
}

void SampleSubscription::newEvents(OpcUa_UInt32 clientSubscriptionHandle, UaEventFieldLists& eventFieldList)
{
    OpcUa_ReferenceParameter(clientSubscriptionHandle);
    OpcUa_ReferenceParameter(eventFieldList);
}

UaStatus SampleSubscription::createSubscription(UaSession* pSession)
{
    if (m_pSubscription)
    {
        printf("\nError: Subscription already created\n");
        return OpcUa_BadInvalidState;
    }
    m_pSession = pSession;
    UaStatus result;
    ServiceSettings serviceSettings;
    SubscriptionSettings subscriptionSettings;
    subscriptionSettings.publishingInterval = 100;
    printf("\nCreating subscription ...\n");
    result = pSession->createSubscription(
        serviceSettings,
        this,
        1,
        subscriptionSettings,
        OpcUa_True,
        &m_pSubscription);
    if (result.isGood())
    {
        printf("CreateSubscription succeeded\n");
    }
    else
    {
        m_pSubscription = NULL;
        printf("CreateSubscription failed with status %s\n", result.toString().toUtf8());
    }
    return result;
}

UaStatus SampleSubscription::deleteSubscription()
{
    if (m_pSubscription == NULL)
    {
        printf("\nError: No Subscription created\n");
        return OpcUa_BadInvalidState;
    }
    UaStatus result;
    ServiceSettings serviceSettings;
    // let the SDK cleanup the resources for the existing subscription
    printf("\nDeleting subscription ...\n");
    result = m_pSession->deleteSubscription(
        serviceSettings,
        &m_pSubscription);
    if (result.isGood())
    {
        printf("DeleteSubscription succeeded\n");
    }
    else
    {
        printf("DeleteSubscription failed with status %s\n", result.toString().toUtf8());
    }
    m_pSubscription = NULL;
    return result;
}

UaStatus SampleSubscription::createMonitoredIterms()
{
    if (m_pSubscription == NULL)
    {
        printf("\nError: No Subscription created\n");
        return OpcUa_BadInvalidState;
    }

    UaStatus result;
    OpcUa_UInt32 i;
    ServiceSettings serviceSettings;
    UaMonitoredItemCreateRequests itemsToCreate;
    UaMonitoredItemCreateResults createResults;

    //根据xml配置文件构建itemsToCreate
    buildMonitorItems(itemsToCreate);

    //创建监视项
    printf("\nAdding monitored items to subscription ...\n");
    result = m_pSubscription->createMonitoredItems(
        serviceSettings,
        OpcUa_TimestampsToReturn_Both,
        itemsToCreate,
        createResults);

    if (result.isGood())
    {
        // check individual results
        for (i = 0; i < createResults.length(); i++)
        {
            if (OpcUa_IsGood(createResults[i].StatusCode))
            {
                printf("CreateMonitoredItems succeeded for item: %s\n",
                    UaNodeId(itemsToCreate[i].ItemToMonitor.NodeId).toXmlString().toUtf8());
            }
            else
            {
                printf("CreateMonitoredItems failed for item: %s - Status %s\n",
                    UaNodeId(itemsToCreate[i].ItemToMonitor.NodeId).toXmlString().toUtf8(),
                    UaStatus(createResults[i].StatusCode).toString().toUtf8());
            }
        }
    }
    else
    {
        printf("CreateMonitoredItems failed with status %s\n", result.toString().toUtf8());
    }
    return result;
}

void SampleSubscription::buildMonitorItems(UaMonitoredItemCreateRequests& itemsToCreate)
{
    //从xml文本中解析OPC UA节点信息用于监控

    //打开xml文件"mcsGuiConfig.xm"，并将其解析到内存QDomDocument doc中
    QFile xmlFile("mcsGuiConfig.xml");

    if (!xmlFile.open(QFile::ReadOnly))
    {
        std::cout<<"error file"<<std::endl;
        return;
    }
    QDomDocument doc;
    if (!doc.setContent(&xmlFile))
    {
        //std::cout<<"error doc"<<std::endl;
        xmlFile.close();
        return;
    }
    xmlFile.close();

    //命名空间
    int namespaceId = 2;
    //获取根节点和子系统
    QDomElement root = doc.documentElement();
    QDomNodeList subsystems = root.childNodes();
    int subsystemNum = subsystems.count();
    //nu：遍历序号
    int nu = 0;
    //nu_all：叶子节点总数(即OPC UA变量个数)
    int nu_all = 0;

    //计算nu_all，并据此为itemsToCreate申请空间
    for (int i = 0; i < subsystemNum; i++)
    {
        auto controls = subsystems.at(i).childNodes();
        int controlNum = controls.count();
        for (int j = 0; j < controlNum; j++)
        {
            nu_all = nu_all + controls.at(j).childNodes().count();
        }
    }
    itemsToCreate.create(nu_all);

    for (int i = 0; i < subsystemNum; i++)
    {
        auto controls = subsystems.at(i).childNodes();
        int controlNum = controls.count();
        for (int j = 0; j < controlNum; j++)
        {
            auto properties = controls.at(j).childNodes();
            int propertyNum = properties.count();
            for (int k = 0; k < propertyNum; k++)
            {
                auto propertyId = properties.at(k).firstChild().toText().data().toUInt();

                itemsToCreate[nu].ItemToMonitor.AttributeId = OpcUa_Attributes_Value;
                itemsToCreate[nu].ItemToMonitor.NodeId.NamespaceIndex = namespaceId;
                itemsToCreate[nu].ItemToMonitor.NodeId.Identifier.Numeric = propertyId;
                itemsToCreate[nu].RequestedParameters.ClientHandle = propertyId;
                itemsToCreate[nu].RequestedParameters.SamplingInterval = 100;
                itemsToCreate[nu].RequestedParameters.QueueSize = 1;
                itemsToCreate[nu].RequestedParameters.DiscardOldest = OpcUa_True;
                itemsToCreate[nu].MonitoringMode = OpcUa_MonitoringMode_Reporting;
                nu++;
            }
        }
        namespaceId++;
    }
}

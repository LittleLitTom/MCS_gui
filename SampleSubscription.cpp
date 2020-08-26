#include "SampleSubscription.h"
#include "uasubscription.h"
#include "uasession.h"

SampleSubscription::SampleSubscription()
	:m_pSession(NULL),
	m_pSubscription(NULL)
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
            UaVariant tempValue = dataNotifications[i].Value.Value;
            printf("  Variable %d value = %s\n", dataNotifications[i].ClientHandle, tempValue.toString().toUtf8());
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

    //创建监视项
    //...
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


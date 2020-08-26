#pragma once
#include "uabase.h"
#include "uaclientsdk.h"

using namespace UaClientSdk;

class SampleSubscription :
    public UaSubscriptionCallback
{
    UA_DISABLE_COPY(SampleSubscription);
public:
    SampleSubscription();
    virtual~SampleSubscription();

    //�����ӿ�
    virtual void subscriptionStatusChanged(
        OpcUa_UInt32 clientSubscriptionHandle,
        const UaStatus& status) override;
    virtual void dataChange(
        OpcUa_UInt32 clientSubscriptionHandle,
        const UaDataNotifications& dataNotifications,
        const UaDiagnosticInfos& diagnosticInfos) override;
    virtual void newEvents(
        OpcUa_UInt32                clientSubscriptionHandle,
        UaEventFieldLists& eventFieldList) override;

    UaStatus createSubscription(UaSession* pSession);
    UaStatus deleteSubscription();
    UaStatus createMonitoredIterms();
private:
    UaSession* m_pSession;
    UaSubscription* m_pSubscription;
};

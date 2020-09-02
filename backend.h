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

    void emitDataChange(int id,QVariant data);

signals:
    void dataChange(int id,QVariant data);

private:
    //OPC UA¿Í»§¶Ë
    SampleClient* myClient;
};

#endif // BACKEND_H

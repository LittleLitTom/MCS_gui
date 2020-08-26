#ifndef POWERSUPPLY_H
#define POWERSUPPLY_H

#include <QObject>
#include "uaplatformlayer.h"
#include "sampleclient.h"

class PowerSupply : public QObject
{
    Q_OBJECT
public:
    explicit PowerSupply(QObject *parent = nullptr);
    void ReadValues();
    void WriteValues();
    void MonitorValues();

    void test();

signals:
    void st(int);

private:
    QString PSId;

    //float Current;
    //float Voltage;
};

#endif // POWERSUPPLY_H

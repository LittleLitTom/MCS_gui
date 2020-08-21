#ifndef POWERSUPPLY_H
#define POWERSUPPLY_H

#include <QObject>

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
    //ps session
    //float Current;
    //float Voltage;
};

#endif // POWERSUPPLY_H

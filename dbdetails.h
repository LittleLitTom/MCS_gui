#ifndef DBDETAILS_H
#define DBDETAILS_H

#include <QMainWindow>
#include <QButtonGroup>
#include "utilities.h"

//!!!�ر�˵����
//��QtCharts��ʹ��һ��Ҫ��������ͷ�ļ��в���#include<QtCharts>�ķ���������ɱ������
//�ʶ�������ͷ�ļ�������QCharts�࣬��Դ�ļ������ͷ�ļ��ķ����������ͷ�ļ�ʱ������ͳ��#include<QtCharts>�����Ƿ���ģ�����
//������Ч�Ĺ�ܱ������

namespace QtCharts
{
    class QLineSeries;
    class QChart;
    class QDateTimeAxis;
    class QValueAxis;
}
using namespace QtCharts;

namespace Ui {
class DBDetails;
}

class DBDetails : public QMainWindow
{
    Q_OBJECT

public:
    explicit DBDetails(QWidget *parent = nullptr,QString DBname = NULL);
    ~DBDetails();

    //���²ۺ�������(backend)����
    //monitor-��״Ŀ¼
    void display_value(uint dbId, QVariant data);
    //read & write--�Ҷ˽���
    //�����ź�(read���),�����Ҷ˽�����ʾ
    void process_read_results(QList<uint>ids, QList<QVariant>datas, QList<int>results);
    //�����ź�(write���)��������
    void process_write_results(QList<uint>ids, QList<int>results);

    //�����ź��ɽ��淢�͸��ۺ���
signals:
    void writeNodes(QList<uint>ids, QList<QVariant>datas);
    void readNodes(QList<uint> ids);

private:
    Ui::DBDetails *ui;
    QString DBname;
    uint DBId;
    //��checkButton���,Button Group������Check Button���Ϊһ��
    QButtonGroup* daqModeGroup;//���������򵥵㴥��
    QButtonGroup* motionGroup;//�������ƣ�������߰γ�
    //��ͼ��(����)��ʾ���
    //x����ͼ�λ���
    QChart* myChartX;
    QLineSeries* myChartXseries;
    //y����ͼ�λ���
    QChart* myChartY;
    QLineSeries* myChartYseries;
    //ɢ��ͼ
    QChart* myChartDot;
};

#endif // DBDETAILS_H

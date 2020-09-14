#ifndef DBDETAILS_H
#define DBDETAILS_H

#include <QMainWindow>
#include <QButtonGroup>
#include "utilities.h"

//!!!特别说明：
//对QtCharts的使用一定要谨慎，在头文件中采用#include<QtCharts>的方法极易造成编译错误
//故而采用在头文件中声明QCharts类，在源文件中添加头文件的方法，且添加头文件时，不笼统的#include<QtCharts>，而是分子模块添加
//可以有效的规避编译错误

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

    //以下槽函数与后端(backend)交互
    //monitor-树状目录
    void display_value(uint dbId, QVariant data);
    //read & write--右端界面
    //回收信号(read结果),并在右端界面显示
    void process_read_results(QList<uint>ids, QList<QVariant>datas, QList<int>results);
    //回收信号(write结果)，并处理
    void process_write_results(QList<uint>ids, QList<int>results);

    //以下信号由界面发送给槽函数
signals:
    void writeNodes(QList<uint>ids, QList<QVariant>datas);
    void readNodes(QList<uint> ids);

private:
    Ui::DBDetails *ui;
    QString DBname;
    uint DBId;
    //与checkButton相关,Button Group将若干Check Button组合为一组
    QButtonGroup* daqModeGroup;//连续采样或单点触发
    QButtonGroup* motionGroup;//启动控制，插入或者拔出
    //与图形(波形)显示相关
    //x方向图形积分
    QChart* myChartX;
    QLineSeries* myChartXseries;
    //y方向图形积分
    QChart* myChartY;
    QLineSeries* myChartYseries;
    //散点图
    QChart* myChartDot;
};

#endif // DBDETAILS_H

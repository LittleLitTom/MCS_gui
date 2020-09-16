#ifndef ACCELERATER_H
#define ACCELERATER_H

#include <QWidget>
#include <QLabel>
#include "psdialog.h"

namespace Ui {
class accelerater;
}

class accelerater : public QWidget
{
    Q_OBJECT

    //注册加速器的束流状态属性
    Q_PROPERTY(int beamState MEMBER m_beamState NOTIFY beamStateChanged)

public:
    explicit accelerater(QWidget *parent = nullptr);
    ~accelerater();

    void changeWidgetStyle();

signals:
    void beamStateChanged(int);

    //弹出子界面时，该信号发射
    void aNewSubInterface(QString activeBDname);

private slots:

private:
    //initialize函数负责界面的初始化工作
    void acceleratorInitialize();
    Ui::accelerater *ui;
    //代表束线状态
    int m_beamState;
};

#endif // ACCELERATER_H

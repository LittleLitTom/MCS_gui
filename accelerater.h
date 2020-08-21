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

    //加速器的束流属性
    Q_PROPERTY(int beamState MEMBER m_beamState NOTIFY beamStateChanged)

public:
    explicit accelerater(QWidget *parent = nullptr);
    ~accelerater();

    void changeWidgetStyle();

    void changeMe(bool);

signals:
    void beamStateChanged(int);

private slots:

private:
    //initialize函数负责界面的初始化工作
    void acceleratorInitialize();
    Ui::accelerater *ui;
    int m_beamState;

    std::map<uint,QPushButton*> myButtons;
};

#endif // ACCELERATER_H

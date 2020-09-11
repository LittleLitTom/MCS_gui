#ifndef MYCHARTVIEW_H
#define MYCHARTVIEW_H

#include <QWidget>

namespace Ui {
class MyChartView;
}

class MyChartView : public QWidget
{
    Q_OBJECT

public:
    explicit MyChartView(QWidget *parent = nullptr);
    ~MyChartView();

private:
    Ui::MyChartView *ui;
};

#endif // MYCHARTVIEW_H

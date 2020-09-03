#ifndef INTERPS_H
#define INTERPS_H

#include <QMainWindow>

namespace Ui {
class interps;
}

class interps : public QMainWindow
{
    Q_OBJECT

public:
    explicit interps(QWidget *parent = nullptr);
    ~interps();

    void display_value(uint psId,QVariant data);

private slots:
    void on_tabWidget_currentChanged(int index);

private:
    Ui::interps *ui;

    //自定义数据。用以存储电源相关信息
    std::map<uint, QStringList> myPsData;
};

#endif // INTERPS_H

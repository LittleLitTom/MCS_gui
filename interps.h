#ifndef INTERPS_H
#define INTERPS_H

#include <QMainWindow>
#include <QTreeWidgetItem>

namespace Ui {
class interps;
}

class interps : public QMainWindow
{
    Q_OBJECT

public:
    explicit interps(QWidget *parent = nullptr);
    ~interps();

    //以下槽函数与后端交互
    //monitor-树状目录
    void display_value(uint psId,QVariant data);
    //read & write--右端界面
    //回收信号(read结果),并在右端界面显示
    void process_read_results(QList<uint>ids, QList<QVariant>datas, QList<int>results);
    //回收信号(write结果)，并处理
    void process_write_results(QList<uint>ids, QList<int>results);

    //����Ŀ�л���Դ
    void onTreeItemActive(QTreeWidgetItem* item, int column);

private slots:
    //以下槽函数与界面交互相关
    void on_tabWidget_currentChanged(int index);

    void on_CurrentSet_clicked();

    void on_CurrentGet_clicked();

    void on_CurrentMaxSet_clicked();

    void on_CurrentMaxGet_clicked();


//信号
signals:
    void writeNodes(QList<uint>ids, QList<QVariant>datas);
    void readNodes(QList<uint> ids);
private:
    Ui::interps *ui;

    //该信息与树形列表展示相关
    std::map<uint, QStringList> myPsData;

    //储存当前选中的电源信息
    //当前选中的电源名
    QString currentPsName;
    //当前选中的电源号
    uint currentPsId;
};

#endif // INTERPS_H

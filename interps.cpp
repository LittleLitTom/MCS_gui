#include "interps.h"
#include "ui_interps.h"

#include <QtDebug>

interps::interps(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::interps)
{
    ui->setupUi(this);

    //为树型目录的元素加入选择框，并设置为不可选状态
    QTreeWidgetItemIterator it(ui->treeWidget);
    while (*it)
    {
        (*it)->setCheckState(0,Qt::Unchecked);
        (*it)->setFlags(Qt::ItemIsAutoTristate|Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsEnabled);
        it++;
    }
}

interps::~interps()
{
    delete ui;
}

void interps::on_tabWidget_currentChanged(int index)
{
    if(index == 3)//此时位Tab位于批量设置，复选框可选
    {
        QTreeWidgetItemIterator it(ui->treeWidget);
        while (*it)
        {
            (*it)->setFlags(Qt::ItemIsAutoTristate|Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
            it++;
        }
    }
    else//此时Tab不位于批量设置，复选框不可选
    {
        QTreeWidgetItemIterator it(ui->treeWidget);
        while (*it)
        {
            (*it)->setFlags(Qt::ItemIsAutoTristate|Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsEnabled);
            it++;
        }
    }
}

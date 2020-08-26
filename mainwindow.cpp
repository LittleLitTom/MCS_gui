#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>

#include "powersupply.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    ,ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    interBD_ = new interBD(this);
    interPS_ = new interps(this);

    //添加后端线程，负责数据采集
    workThread = new QThread;
    PowerSupply* mypowsupply = new PowerSupply;
    mypowsupply->moveToThread(workThread);
    connect(workThread,&QThread::finished,mypowsupply,&QObject::deleteLater);
    connect(this,&MainWindow::hh,mypowsupply,&PowerSupply::test);
    connect(mypowsupply,&PowerSupply::st,[&](int nu){interBD_->setmagnet(nu);});
    workThread->start();
}

MainWindow::~MainWindow()
{
    //退出工作线程
    workThread->exit();
    delete ui;
}

void MainWindow::on_actionDB_triggered()
{
    interBD_->show();
}

void MainWindow::on_actionPower_Sypply_triggered()
{
    interPS_->show();
}

void MainWindow::on_pushButton_clicked()
{
    emit hh();
}

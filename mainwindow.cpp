#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>

#include "backend.h"
#include "interps.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    ,ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    interBD_ = new interBD(this);
    interPS_ = new interps(this);

    //添加后端线程，负责数据采集
    workThread = new QThread;
    Backend* myBackend = new Backend;
    myBackend->moveToThread(workThread);
    connect(myBackend, &Backend::dataChange,interPS_,&interps::display_value);
    //connect(workThread,&QThread::finished,myBackend,&QObject::deleteLater);
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

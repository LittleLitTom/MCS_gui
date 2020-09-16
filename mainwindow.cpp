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

    //添加后端线程，负责数据采集
    workThread = new QThread;
    Backend* myBackend = new Backend;
    myBackend->moveToThread(workThread);
    connect(workThread, &QThread::finished, myBackend, &QObject::deleteLater);

    //添加子界面
    interBD_ = new interBD(myBackend,this);
    interPS_ = new interps(this);

    //连接电源子界面与后端采集线程
    connect(myBackend, &Backend::dataChange,interPS_,&interps::display_value);
    
    connect(interPS_, &interps::writeNodes, myBackend, &Backend::writeNodes);
    connect(myBackend, &Backend::writeNodesResults, interPS_, &interps::process_write_results);
    connect(interPS_, &interps::readNodes, myBackend, &Backend::readNodes);
    connect(myBackend, &Backend::readNodesResults, interPS_, &interps::process_read_results);

    //开启节点监控(monitor)程序
    connect(this, &MainWindow::startAcquisition, myBackend, &Backend::runAcquisition);;
    emit(startAcquisition());

    //启动工作线程
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

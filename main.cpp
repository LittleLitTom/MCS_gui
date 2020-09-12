#include "mainwindow.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    //注册信号与槽自定义变量
    qRegisterMetaType<QList<uint>>("QList<uint>");
    qRegisterMetaType<QList<int>>("QList<int>");
    qRegisterMetaType<QList<QVariant>>("QList<QVariant>");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
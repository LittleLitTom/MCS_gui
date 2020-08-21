#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <interbd.h>
#include <interps.h>

#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionDB_triggered();

    void on_actionPower_Sypply_triggered();

    void on_pushButton_clicked();

signals:
    void hh();
private:
    Ui::MainWindow *ui;
    interBD* interBD_;
    interps* interPS_;

    //多线程管理类
    QThread workThread;
};
#endif // MAINWINDOW_H

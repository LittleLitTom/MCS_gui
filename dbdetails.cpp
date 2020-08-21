#include "dbdetails.h"
#include "ui_dbdetails.h"

DBDetails::DBDetails(QWidget *parent, QString DBname) :
    QMainWindow(parent),
    ui(new Ui::DBDetails),
    DBname(DBname)
{
    ui->setupUi(this);
    ui->label->setText("荧光屏：    "+DBname);
    setAttribute (Qt::WA_DeleteOnClose);
}

DBDetails::~DBDetails()
{
    delete ui;
}

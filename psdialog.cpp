#include "psdialog.h"
#include "ui_psdialog.h"

PSDialog::PSDialog(QWidget *parent, QString PSname) :
    QDialog(parent),
    ui(new Ui::PSDialog),
    PSname(PSname)
{
    ui->setupUi(this);
    ui->label->setText("PS编号:   "+PSname);
    setAttribute (Qt::WA_DeleteOnClose);
}

PSDialog::~PSDialog()
{
    delete ui;
}

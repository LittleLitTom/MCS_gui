#ifndef PSDIALOG_H
#define PSDIALOG_H

#include <QDialog>

namespace Ui {
class PSDialog;
}

class PSDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PSDialog(QWidget *parent = nullptr,QString PSname = NULL);
    ~PSDialog();

private:
    Ui::PSDialog *ui;
    QString PSname;
};

#endif // PSDIALOG_H

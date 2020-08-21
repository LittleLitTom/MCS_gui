#ifndef DBDETAILS_H
#define DBDETAILS_H

#include <QMainWindow>

namespace Ui {
class DBDetails;
}

class DBDetails : public QMainWindow
{
    Q_OBJECT

public:
    explicit DBDetails(QWidget *parent = nullptr,QString DBname = NULL);
    ~DBDetails();

private:
    Ui::DBDetails *ui;
    QString DBname;
};

#endif // DBDETAILS_H

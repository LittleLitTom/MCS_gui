#ifndef QSCBUTTON_H
#define QSCBUTTON_H

#include <QWidget>
#include <QPushButton>
#include "dbdetails.h"

class QSCButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(int type MEMBER m_type)
    Q_PROPERTY(int location MEMBER m_location)
    Q_PROPERTY(uint state MEMBER m_state NOTIFY stateChanged)

public:
    explicit QSCButton(QWidget *parent = nullptr);
    void onclick();
    void changeButtonStyle();

signals:
    void stateChanged();

private:
    //SC? IC? FC?
    int m_type;
    //1 2 3 4 ...
    int m_location;
    //on? off?
    uint m_state;
    DBDetails* DBDetails_;
};

#endif // QSCBUTTON_H

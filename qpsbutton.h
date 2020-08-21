#ifndef QPSBUTTON_H
#define QPSBUTTON_H

#include <QWidget>
#include <QPushButton>
#include "psdialog.h"

class QPSButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(int type MEMBER m_type)
    Q_PROPERTY(int location MEMBER m_location)
    Q_PROPERTY(uint state MEMBER m_state NOTIFY stateChanged)

public:
    explicit QPSButton(QWidget *parent = nullptr);
    void onclick();
    void changeButtonStyle();

signals:
    void stateChanged();

private:
    //kicker? B? Q? ST?
    int m_type;
    //1 2 3 4 5 ...
    int m_location;
    //on? off?
    uint m_state;

    PSDialog* PSDialog_;
};

#endif // QPSBUTTON_H

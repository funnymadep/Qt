#include "mylabel.h"

MyLabel::MyLabel(const QString text, QWidget *parent)
    :QLabel(text, parent)
{

}

void MyLabel::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton)
        emit left_press();
    else if (ev->button() == Qt::RightButton)
        emit right_press();
}

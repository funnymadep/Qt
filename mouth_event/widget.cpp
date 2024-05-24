#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    startTimer(1000);
}

Widget::~Widget()
{

}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if (Qt::LeftButton == event->button())
        qDebug() << "mouse left button clicked";
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if (Qt::RightButton == event->button())
        qDebug() << "mouse left button release";
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << event->pos() << event->x() << event->y();
}

void Widget::mouseDoubleClickEvent(QMouseEvent *event)
{

}

void Widget::wheelEvent(QWheelEvent *event)
{

}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if ((event->modifiers() == Qt::ControlModifier)
            && (event->key() == Qt::Key_A))
        qDebug() << "ctrl a";
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    qDebug() << "keyrelease";
}

void Widget::resizeEvent(QResizeEvent *event)
{
    qDebug() << event->size();
}

void Widget::closeEvent(QCloseEvent *event)
{
    //event->ignore();
}

void Widget::timerEvent(QTimerEvent *event)
{
    qDebug() << "timeout...";
}


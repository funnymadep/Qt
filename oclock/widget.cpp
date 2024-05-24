#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    startTimer(1000);
    this->setFixedSize(640, 480);
    pixmap = new QPixmap(640, 480);
    pixmap->fill();

    sangle = mangle = hangle = 0;
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent *ev)
{
    QPainter p(pixmap);
    QPen pen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    pen.setWidth(10);
    p.setPen(pen);
    p.translate(this->width()/2, this->height()/2);
    p.drawEllipse(QPoint(0, 0), 200, 200);
    for (int i = 0; i < 60; i++) {

        p.rotate(12);
        p.drawLine(QPoint(0, 190), QPoint(0, 200));
    }

    QPainter pp(this);

    pp.drawPixmap(0, 0, *pixmap);
    pp.translate(this->width()/2, this->height()/2);

    QPen hpen(Qt::green, 7, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    pp.setPen(hpen);
    pp.rotate(hangle);
    pp.drawLine(QPoint(0, 0), QPoint(0, 50));

    QPen mpen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    pp.setPen(mpen);
    pp.rotate(mangle);
    pp.drawLine(QPoint(0, 0), QPoint(100, 0));

    QPen spen(Qt::darkGreen, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    pp.setPen(spen);
    pp.rotate(sangle);
    pp.drawLine(QPoint(0, 0), QPoint(-150, 0));

}

void Widget::timerEvent(QTimerEvent *ev)
{

    sangle += 6;
    if (360 == sangle){
        mangle += 6;
        sangle = 0;
    }
    if(360 == mangle){
        mangle = 0;
        hangle += 30;
    }
    update();
}


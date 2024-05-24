#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    l1 = new QLabel;
    l1->setFixedSize(640, 480);
    l1->setScaledContents(true);
    l1->setPixmap(QPixmap("D:/pictures/1.jpg"));

    l2 = new QLabel;
    l2->setFixedSize(640, 480);
    l2->setScaledContents(true);
    l2->setPixmap(QPixmap("D:/pictures/2.jpg"));

    l3 = new QLabel;
    l3->setFixedSize(640, 480);
    l3->setScaledContents(true);
    l3->setPixmap(QPixmap("D:/pictures/3.jpg"));

    sw = new QStackedWidget(this);
    sw->addWidget(l1);
    sw->addWidget(l2);
    sw->addWidget(l3);
    sw->setFixedSize(640, 480);

    cbb = new QComboBox(this);
    cbb->addItem(QIcon("D:/pictures/1.jpg"), "1.jpg");
    cbb->addItem(QIcon("D:/pictures/2.jpg"), "2.jpg");
    cbb->addItem(QIcon("D:/pictures/1.jpg"), "3.jpg");



}

Widget::~Widget()
{
}


#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    sd = new QSlider;
    sd->setValue(50);
    sd->setRange(0, 100);
    sd->setOrientation(Qt::Horizontal);

    sb = new QScrollBar;
    sb->setValue(50);
    sb->setRange(0, 100);
    sb->setOrientation(Qt::Horizontal);

    pgb = new QProgressBar;
    pgb->setValue(50);
    pgb->setRange(0, 100);
    pgb->setOrientation(Qt::Horizontal);

    le = new QLineEdit;
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(sd);
    vbox->addWidget(sb);
    vbox->addWidget(pgb);
    vbox->addWidget(le);
    setLayout(vbox);

    connect(sd, SIGNAL(valueChanged(int)), sb, SLOT(setValue(int)));
    connect(sb, SIGNAL(valueChanged(int)), sd, SLOT(setValue(int)));
    connect(sd, SIGNAL(valueChanged(int)), pgb, SLOT(setValue(int)));
    connect(sd, SIGNAL(valueChanged(int)), this, SLOT(show_num(int));

}

Widget::~Widget()
{

}


#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    pb1 = new QPushButton("+");
    pb2 = new QPushButton("-");
    le = new QLineEdit("0");

    QFont font("Times", 30, QFont::Black);
    this->setFont(font);

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(pb1);
    hbox->addWidget(pb2);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(le);
    vbox->addLayout(hbox);
    this->setLayout(vbox);

    le->setText(QString::number(100));

    connect(pb1, &QPushButton::clicked, this, &Widget::add);
    connect(pb2, &QPushButton::clicked, this, &Widget::jian);
}

Widget::~Widget()
{
}

void Widget::add()
{
    QString str = le->text();
    if(str.isEmpty())
        return;
   int num = str.toInt();
   num++;
   le->setText(QString::number(num));
}

void Widget::jian()
{
    QString str = le->text();
    if(str.isEmpty())
        return;
   int num = str.toInt();
   num--;
   le->setText(QString::number(num));
}


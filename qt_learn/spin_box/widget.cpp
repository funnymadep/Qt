#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QFont font("Times", 10, QFont::Bold);
    this->setFont(font);
    sb = new QSpinBox;
    le = new QLineEdit;
    sb->setValue(50);
    sb->setRange(-10, 100);
    sb->setPrefix("李汶莲吃稀屎的重量：");
    sb->setSuffix("T");

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(sb);
    vbox->addWidget(le);
    setLayout(vbox);

    connect(sb, SIGNAL(valueChanged(QString)), le, SLOT(setText(QString)));
}

Widget::~Widget()
{
}


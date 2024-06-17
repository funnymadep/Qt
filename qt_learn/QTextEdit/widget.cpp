#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    pb1 = new QPushButton("text->line");
    pb2 = new QPushButton("line->text");
    le = new QLineEdit;
    te = new QTextEdit;

    this->setMinimumSize(500, 500);
    QFont font("Times", 20, QFont::Bold);


    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(pb1);
    hbox->addWidget(pb2);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(te);
    vbox->addWidget(le);
    vbox->addLayout(hbox);
    this->setLayout(vbox);

    connect(pb1, &QPushButton::clicked, [=](){
        QString str = te->toPlainText();
        le->setText(str);
    });
    connect(pb2, &QPushButton::clicked, [=](){
        QString str = le->text();
        te->setText(str);
    });
}

Widget::~Widget()
{
}


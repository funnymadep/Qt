#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QFont font("Times", 20, QFont::Bold);
    this->setFont(font);

    l = new QLabel;
    l->setText("考试须知：\n    1. 总共3题, 每题1分；\n    2. 每题答题时间10s\n    3. 点击开始按钮开始考试");
    pb = new QPushButton("开始");

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(l);
    vbox->addWidget(pb);
    setLayout(vbox);

    connect(pb, &QPushButton::clicked, [=](){
        MyTest *test = new MyTest;
        test->show();
        this->hide();
    });
}

Widget::~Widget()
{
}


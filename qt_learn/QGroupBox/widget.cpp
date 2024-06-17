#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    l1 = new QLabel("孔子姓什么?");
    l2 = new QLabel("老子姓什么？");

    QStringList str = {"A.何", "B.李", "C.子", "D.张", "A.何", "B.李", "C.子", "D.张"};
    for (int i = 0; i < 4; i++)
        rb1[i] = new QRadioButton(str.at(i));
    for (int i = 0; i < 4; i++)
        rb2[i] = new QRadioButton(str.at(i));

    QVBoxLayout *vbox1 = new QVBoxLayout;
    vbox1->addWidget(l1);
    for (int i = 0; i < 4; i++)
        vbox1->addWidget(rb1[i]);

    QVBoxLayout *vbox2 = new QVBoxLayout;
    vbox2->addWidget(l2);
    for (int i = 0; i < 4; i++)
        vbox2->addWidget(rb2[i]);


    gbox1 = new QGroupBox("第一题");
    gbox1->setLayout(vbox1);
    gbox2 = new QGroupBox("第二题");
    gbox2->setLayout(vbox2);

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(gbox1);
    hbox->addWidget(gbox2);
    this->setLayout(hbox);

    for(int i = 0; i < 4; i++)
        connect(rb1[i], &QRadioButton::clicked, [=](){
            QRadioButton *r = static_cast<QRadioButton *>(sender());
            //if (r->isChecked("C"))
                QDebug() << r->text() << endl;
        });
}

Widget::~Widget()
{
}


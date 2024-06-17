#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    l = new QLabel("show_picture", this);
    pb1 = new QPushButton("left");
    pb2 = new QPushButton("right");
    l->setFixedSize(800, 600);
    l->setAlignment(Qt::AlignCenter);
    l->setScaledContents(true);

    this->num = 0;
    QStringList filenames = QFileDialog::getOpenFileNames(this,
        "open image", ":/", "Images(*.jpg *.png *.bmp)");
    l->setPixmap(QPixmap(filenames.at(num)));

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(pb1);
    hbox->addWidget(l);
    hbox->addWidget(pb2);
    this->setLayout(hbox);
    connect(pb1, &QPushButton::clicked, [=](){
        if(num == 0)
            num = filenames.length();
        l->setPixmap(QPixmap(filenames.at(--num)));

    });
    connect(pb2, &QPushButton::clicked, [=](){
        if (num == filenames.length() - 1)
            num = -1;
        l->setPixmap(QPixmap(filenames.at(++num)));
    });
}

Widget::~Widget()
{
}


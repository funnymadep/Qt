#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    l = new MyLabel("showpic", this);
    l->setFixedSize(640, 480);
    l->setAlignment(Qt::AlignCenter);
    l->setScaledContents(true);


    QStringList filenames = QFileDialog::getOpenFileNames(this, "open images",
               ":/", "Images (*.jpg *.png *.bmp)");
    this->num = 0;
    if (filenames.isEmpty())
        this->close();
    l->setPixmap(QPixmap(filenames.at(num)));
    connect(l, &MyLabel::left_press, [=](){
        if(filenames.isEmpty())
            exit(0);
        if (num == 0)
            return;
        l->setPixmap(QPixmap(filenames.at(--num)));
    });

    connect(l, &MyLabel::right_press, [=](){
        if(filenames.isEmpty())
            exit(0);
        if(num == filenames.length() - 1)
            return;
        l->setPixmap(QPixmap(filenames.at(++num)));
    });
}

Widget::~Widget()
{

}



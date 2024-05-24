#include "my_widget.h"

my_widget::my_widget(QWidget *parent) : QWidget(parent)
{
    pb1 = new QPushButton("return");
    pb2 = new QPushButton("close");

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(pb1);
    vbox->addWidget(pb2);
    setLayout(vbox);

    connect(pb1, &QPushButton::clicked, [=](){
        emit return_widget();
        this->close();

    });
    connect(pb2, &QPushButton::clicked, this, &my_widget::close);
}

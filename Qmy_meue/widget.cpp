#include "widget.h"
#include "my_widget.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    l_acc = new QLabel("account：");
    l_pass = new QLabel("password: ");
    pb_login = new QPushButton("login");
    pb_reg = new QPushButton("register");
    le_acc = new QLineEdit;
    le_pass = new QLineEdit;
    cb1 = new QCheckBox("remember password");
    cb2 = new QCheckBox("hide password");

    QGridLayout *gbox = new QGridLayout;
    gbox->addWidget(l_acc, 0, 0, 1, 1);
    gbox->addWidget(l_pass, 1, 0, 1, 1);
    gbox->addWidget(le_acc, 0, 1, 1, 2);
    gbox->addWidget(le_pass, 1, 1, 1, 2);
    gbox->addWidget(cb1, 2, 0, 1, 1);
    gbox->addWidget(cb2, 2, 2, 1, 1);
    gbox->addWidget(pb_login, 3, 0, 1, 1);
    gbox->addWidget(pb_reg, 3, 2, 1, 1);
    setLayout(gbox);

    connect(pb_login, &QPushButton::clicked, [=](){
        my_widget *w = new my_widget;
        w->show();
        this->hide();

        connect(w, &my_widget::return_widget, this, &Widget::show);
    });
}

Widget::~Widget()
{
}


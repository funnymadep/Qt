#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    pb1 = new QPushButton("C");
    pb2 = new QPushButton("X^2");
    pb3 = new QPushButton("+");
    pb4 = new QPushButton("-");
    pb5 = new QPushButton("*");
    pb6 = new QPushButton("/");
    pb7 = new QPushButton("=");
    n0 = new QPushButton("0");
    n1 = new QPushButton("1");
    n2 = new QPushButton("2");
    n3 = new QPushButton("3");
    n4 = new QPushButton("4");
    n5 = new QPushButton("5");
    n6 = new QPushButton("6");
    n7 = new QPushButton("7");
    n8 = new QPushButton("8");
    n9 = new QPushButton("9");
    le = new QLineEdit("0");

    //le->setReadOnly(ture);
    this->setMinimumSize(800,400);

    QFont font("Times", 20, QFont::Bold);
    QFont font1("Times", 40, QFont::Black);
    pb1->setFont(font);
    pb2->setFont(font);
    pb3->setFont(font);
    pb4->setFont(font);
    pb5->setFont(font);
    pb6->setFont(font);
    pb7->setFont(font);
    le->setFont(font1);
    this->setFont(font);

    //le->setAlignment(Qt::);
    QGridLayout *grid = new QGridLayout;
    grid->addWidget(le, 0, 0, 1, 4);
    grid->addWidget(n7, 1, 0, 1, 1);
    grid->addWidget(n8, 1, 1, 1, 1);
    grid->addWidget(n9, 1, 2, 1, 1);
    grid->addWidget(n4, 2, 0, 1, 1);
    grid->addWidget(n5, 2, 1, 1, 1);
    grid->addWidget(n6, 2, 2, 1, 1);
    grid->addWidget(n1, 3, 0, 1, 1);
    grid->addWidget(n2, 3, 1, 1, 1);
    grid->addWidget(n3, 3, 2, 1, 1);
    grid->addWidget(n0, 4, 0, 1, 1);
    grid->addWidget(pb1, 1, 3, 1, 1);
    grid->addWidget(pb2, 2, 3, 1, 1);
    grid->addWidget(pb3, 3, 3, 1, 1);
    grid->addWidget(pb4, 4, 1, 1, 1);
    grid->addWidget(pb5, 4, 2, 1, 1);
    grid->addWidget(pb6, 4, 3, 1, 1);
    grid->addWidget(pb7, 5, 0, 1, 4);
    this->setLayout(grid);

    connect(pb1, &QPushButton::clicked, this, &Widget::clear);
    connect(pb2, &QPushButton::clicked, this, &Widget::square);
    connect(pb3, &QPushButton::clicked, this, &Widget::add);
    connect(pb4, &QPushButton::clicked, this, &Widget::subtract);
    connect(pb5, &QPushButton::clicked, this, &Widget::multi);
    connect(pb6, &QPushButton::clicked, this, &Widget::except);
    connect(pb7, &QPushButton::clicked, this, &Widget::equil);
    connect(n0, &QPushButton::clicked, this, &Widget::e_no);
    connect(n1, &QPushButton::clicked, this, &Widget::e_n1);
    connect(n2, &QPushButton::clicked, this, &Widget::e_n2);
    connect(n3, &QPushButton::clicked, this, &Widget::e_n3);
    connect(n4, &QPushButton::clicked, this, &Widget::e_n4);
    connect(n5, &QPushButton::clicked, this, &Widget::e_n5);
    connect(n6, &QPushButton::clicked, this, &Widget::e_n6);
    connect(n7, &QPushButton::clicked, this, &Widget::e_n7);
    connect(n8, &QPushButton::clicked, this, &Widget::e_n8);
    connect(n9, &QPushButton::clicked, this, &Widget::e_n9);
}

Widget::~Widget()
{
}

void Widget::add()
{
    QString str = le->text();
    if (str.isEmpty())
        return;
    this->numb[0] = str.toInt();
    this->sig[0] = '+';
    int num = 0;
    le->setText(QString::number(num));
}

void Widget::subtract()
{
    QString str = le->text();
    if (str.isEmpty())
        return;
    this->numb[0] = str.toInt();
    this->sig[0] = '-';
    int num = 0;
    le->setText(QString::number(num));
}

void Widget::multi()
{
    QString str = le->text();
    if (str.isEmpty())
        return;
    this->numb[0] = str.toInt();
    this->sig[0] = '*';
    int num = 0;
    le->setText(QString::number(num));
}

void Widget::except()
{
    QString str = le->text();
    if (str.isEmpty())
        return;
    this->numb[0] = str.toInt();
    this->sig[0] = '/';
    int num = 0;
    le->setText(QString::number(num));
}

void Widget::clear()
{
    QString str = le->text();
    if (str.isEmpty())
        return;
    int num = str.toInt();
    num = 0;
    le->setText(QString::number(num));
}

void Widget::square()
{
    QString str = le->text();
    if (str.isEmpty())
        return;
    int num = str.toInt();
    num = num * num;
    le->setText(QString::number(num));
}

void Widget::equil(){
    QString str = le->text();
    if (str.isEmpty())
        return;
    this->numb[1] = str.toInt();
    int num;
    switch (this->sig[0]) {
    case '+':
         num = numb[0] + numb[1];
         le->setText(QString::number(num));
        break;
    case '-':
         num = numb[0] - numb[1];
         le->setText(QString::number(num));
        break;
    case '*':
         num = numb[0] * numb[1];
         le->setText(QString::number(num));
        break;
    case '/':
         num = numb[0] / numb[1];
         le->setText(QString::number(num));
        break;
    default:
        break;
    }
}

void Widget::e_no()
{
    QString str = le->text();
    if (str.isEmpty())
        return;
    str += '0';
    int num = str.toInt();
    le->setText(QString::number(num));
}

void Widget::e_n1()
{
    QString str = le->text();
    if (str.isEmpty())
        return;
    str += '1';
    int num = str.toInt();
    le->setText(QString::number(num));
}

void Widget::e_n2()
{
    QString str = le->text();
    if (str.isEmpty())
        return;
    str += '2';
    int num = str.toInt();
    le->setText(QString::number(num));
}

void Widget::e_n3()
{
    QString str = le->text();
    if (str.isEmpty())
        return;
    str += '3';
    int num = str.toInt();
    le->setText(QString::number(num));
}

void Widget::e_n4()
{
    QString str = le->text();
    if (str.isEmpty())
        return;
    str += '4';
    int num = str.toInt();
    le->setText(QString::number(num));
}

void Widget::e_n5()
{
    QString str = le->text();
    if (str.isEmpty())
        return;
    str += '5';
    int num = str.toInt();
    le->setText(QString::number(num));
}

void Widget::e_n6()
{
    QString str = le->text();
    if (str.isEmpty())
        return;
    str += '6';
    int num = str.toInt();
    le->setText(QString::number(num));
}

void Widget::e_n7()
{
    QString str = le->text();
    if (str.isEmpty())
        return;
    str += '7';
    int num = str.toInt();
    le->setText(QString::number(num));
}

void Widget::e_n8()
{
    QString str = le->text();
    if (str.isEmpty())
        return;
    str += '8';
    int num = str.toInt();
    le->setText(QString::number(num));
}

void Widget::e_n9()
{
    QString str = le->text();
    if (str.isEmpty())
        return;
    str += '9';
    int num = str.toInt();
    le->setText(QString::number(num));
}




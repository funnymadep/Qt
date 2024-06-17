#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{//qt程序启动 自动执行
    qDebug() << "hello qt " << endl;
    cout << "hello qt" << endl;
    //this->setFixedSize(640, 480);
    this->setMaximumSize(1024, 840);
    this->setMinimumSize(200, 200);
    this->setWindowTitle("HELLO QT!");
    this->setWindowIcon(QIcon("./1.jpg"));
    pb1 = new QPushButton("启动", this);
    pb2 = new QPushButton("不启动");//布局可以不要this
    //pb1->setGeometry(0, 0, 100, 100);
    //pb2->setGeometry(0, 150, 100, 100);

    /*QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(pb1);
    hbox->addWidget(pb2);
    this->setLayout(hbox);*/

    QFont font("Times", 20, QFont::Bold);
    pb1->setFont(font);
    pb2->setFont(font);
    this->setFont(font);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(pb1);
    vbox->addWidget(pb2);
    this->setLayout(vbox);
    connect(pb1, SIGNAL(clicked(bool)), this, SLOT(ok_click()));
    //connect(pb2, &QPushButton::clicked, this, &Widget::fail_click);
    connect(pb2, &QPushButton::clicked, [ = ](){
        qDebug() << "爱玩玩不玩滚" << endl;
    });
}

Widget::~Widget()
{

}

void Widget::ok_click()
{
    qDebug() << "启动成功" << endl;
}

void Widget::fail_click()
{
    qDebug() << "启动失败"  << endl;
}


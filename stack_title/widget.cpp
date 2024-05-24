#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QStringList strl = {"第一题:小雷上完厕所为什么不洗手?",
                        "第二题:有两个人掉进了井里，死的人叫死人，活的人叫什么?",
                        "第三题:动物园里谁是百兽之王？"};
    QStringList strr = {"A.手很干净不需要洗", "B.没有规定要洗手", "C.洗手只会影响我的速度 ", "D.水含有核辐射",
                        "A.活人", "B.救命", "C.原神启动 ", "D.死人",
                        "A.老虎", "B.考拉", "C.孔雀 ", "D.猫头鹰"};
    for (int i = 0; i < 3; i++){
        l[i] = new QLabel(strl.at(i));
        gbox[i] = new QGroupBox("智商检测器");
    }

    for (int i = 0; i < 4; i++) {
        rb1[i] = new QRadioButton(strr.at(i));
        rb2[i] = new QRadioButton(strr.at(i+4));
        rb3[i] = new QRadioButton(strr.at(i+8));
    }
    sw = new QStackedWidget(this);

    QVBoxLayout *vbox1 = new QVBoxLayout;
    vbox1->addWidget(l[0]);
    for(int i = 0; i < 4; i++)
        vbox1->addWidget(rb1[i]);
    gbox[0]->setLayout(vbox1);

    QVBoxLayout *vbox2 = new QVBoxLayout;
    vbox2->addWidget(l[1]);
    for(int i = 0; i < 4; i++)
        vbox2->addWidget(rb2[i]);
    setLayout(vbox2);
    gbox[1]->setLayout(vbox2);

    QVBoxLayout *vbox3 = new QVBoxLayout;
    vbox3->addWidget(l[2]);
    for(int i = 0; i < 4; i++)
        vbox3->addWidget(rb3[i]);
    gbox[2]->setLayout(vbox3);

    sw->addWidget(gbox[0]);
    sw->addWidget(gbox[1]);
    sw->addWidget(gbox[2]);
    this->setFixedSize(430, 150);
    score = 0;
    for(int i = 0; i < 4; i++)
    connect(rb1[i], &QRadioButton::clicked, [=](){
        if (rb1[1]->isChecked())
            score++;
        sw->setCurrentIndex(1);
        });

    for(int i = 0; i < 4; i++)
    connect(rb2[i], &QRadioButton::clicked, [=](){
        if (rb2[1]->isChecked())
            score++;
        sw->setCurrentIndex(2);
        });
    for(int i = 0; i < 4; i++)
        connect(rb3[i], &QRadioButton::clicked, [=](){
            if(rb3[0]->isChecked())
                score++;
            switch (score) {
            case 0:
                qDebug() <<"你的分数是：" << score <<
                           ",很抱歉，您的智商系统表示很不幸" ;
                break;
            case 1:
                qDebug() << "你的分数是：" << score <<
                            ",您的智商是正常水平" ;
                break;
            case 2:
                qDebug() << "你的分数是：" << score <<
                            "天才！" ;
                break;
            case 3:
                qDebug() << "你的分数是：" << score <<
                            "根本难不倒他" ;
                break;
            default:
                break;
            }
             this->close();
        });
}

Widget::~Widget()
{
}


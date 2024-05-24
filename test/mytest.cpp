#include "mytest.h"

MyTest::MyTest(QWidget *parent) : QWidget(parent)
{
    QFont font("Helvetica", 15, QFont::Bold);
    this->setFont(font);
    //第一行
    l_score = new QLabel("分数：");
    l_time = new QLabel("倒计时: ");
    le_score = new QLineEdit("0");
    le_score->setReadOnly(true);
    le_time = new QLineEdit("10");
    le_time->setReadOnly(true);

    QHBoxLayout *hbox1 = new QHBoxLayout;
    hbox1->addWidget(l_score);
    hbox1->addWidget(le_score);
    hbox1->addWidget(l_time);
    hbox1->addWidget(le_time);

    //第三行
    pb_next = new QPushButton("下一题");
    pb_submit = new QPushButton("提交");

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(pb_next);
    hbox->addWidget(pb_submit);

    //第二行
    QStringList item = {"第一题", "第二题", "第三题"};
    QStringList question = {"1+1 = ?", "下面不是男明星的是谁？", "三国不包含下面哪国？"};
    QStringList answers = {"A. 0","B. 1", "C. 2", "D. 3", "A. 蔡徐坤",
                           "B. 丁真", "C. 王源", "D. 赵露思", "A. 魏",
                           "B. 晋", "C. 吴", "D. 蜀"};
    sw = new QStackedWidget;
    QVBoxLayout *vbox[3];
    for (int i = 0; i < 3; i++) {
        vbox[i] = new QVBoxLayout;
        gbox[i] = new QGroupBox(item.at(i));
        l_question[i] = new QLabel(question.at(i));
        vbox[i]->addWidget(l_question[i]);
        for (int j = 0; j < 4; j++) {
            rb[i][j] = new QRadioButton(answers.at(i*4+j));
            vbox[i]->addWidget(rb[i][j]);
        }
        gbox[i]->setLayout(vbox[i]);
        sw->addWidget(gbox[i]);
    }

    QVBoxLayout *vbox1 = new QVBoxLayout;
    vbox1->addLayout(hbox1);
    vbox1->addWidget(sw);
    vbox1->addLayout(hbox);
    setLayout(vbox1);

    connect(pb_next, &QPushButton::clicked, this, &MyTest::next_question);
    connect(pb_submit, &QPushButton::clicked, this, &MyTest::submit_test);

    timer = new QTimer;
    timer->start(1000);  //启动定时器
    connect(timer, &QTimer::timeout, this, &MyTest::down_count);

    count = 10;  //倒数计数器的值
    score = 0;
    answer[0] = 2;
    answer[1] = 3;
    answer[2] = 1;
}

void MyTest::down_count()
{
    if (0 == count) {
        next_question();
        return;
    }
    count--;
    le_time->setText(QString::number(count));
}

void MyTest::next_question()
{
    int index = sw->currentIndex(); //获取当前页
    if (sw->count()-1 == index) { //当已经是最后一页，相当于提交
        submit_test();
        return;
    }
    int index_answer = answer[index]; //该页正确答案
    if (rb[index][index_answer]->isChecked()) //判断该页的正确答案是否被选中
        score++;
    le_score->setText(QString::number(score));
    sw->setCurrentIndex(index+1);  //设置当前页面
    count = 10;
    le_time->setText(QString::number(count));
}

void MyTest::submit_test()
{
    int index = sw->currentIndex(); //获取当前页
    int index_answer = answer[index]; //该页正确答案
    if (rb[index][index_answer]->isChecked()) //判断该页的正确答案是否被选中
        score++;
    le_score->setText(QString::number(score));
    timer->stop();  //停止定时器

    Result *r = new Result(score);
    r->show();
    this->hide();
}

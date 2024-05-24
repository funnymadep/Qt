#include "result.h"

Result::Result(int num, QWidget *parent) : QWidget(parent)
{
    score = num;

    l = new QLabel(this);
    l->setFixedSize(400, 300);
    l->setAlignment(Qt::AlignCenter);
    QFont font("Times", 30, QFont::Bold);
    l->setFont(font);
    QString str = "你的分数是: \n   " + QString::number(score);
    l->setText(str);
}

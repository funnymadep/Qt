#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <iostream>
#include <QDebug>
#include <QIcon>
#include <QPushButton>
#include <QHBoxLayout> //水平布局
#include <QVBoxLayout>  //垂直布局
#include <QFont>
using namespace std;

class Widget : public QWidget
{
    Q_OBJECT //类 宏 c++编译前多一个预处理 第一次加入才有用

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    QPushButton *pb1, *pb2;
 private slots: //槽函数一定在slots标签之下
    void ok_click(); //alt + enter
    void fail_click();
};
#endif // WIDGET_H

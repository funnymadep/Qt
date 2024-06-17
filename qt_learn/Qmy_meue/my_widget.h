#ifndef MY_WIDGET_H
#define MY_WIDGET_H

#include <QObject>
#include <QWidget>

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class my_widget : public QWidget
{
    Q_OBJECT
public:
    explicit my_widget(QWidget *parent = nullptr);

signals: //只需要声明在signals标签之下， 不需要定义
    void return_widget();

private:
    QPushButton *pb1, *pb2;
};

#endif // MY_WIDGET_H

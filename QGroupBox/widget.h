#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QRadioButton>
#include <QDebug>
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    QRadioButton *rb1[4], *rb2[4];
    QGroupBox *gbox1, *gbox2;
    QLabel *l1, *l2;
};
#endif // WIDGET_H

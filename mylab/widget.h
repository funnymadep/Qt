#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QEvent>
#include <QKeyEvent>
#include <QFileDialog>
#include "mylabel.h"
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    MyLabel *l;
    int num;

};
#endif // WIDGET_H

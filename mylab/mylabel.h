#ifndef MYLABEL_H
#define MYLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
class MyLabel : public QLabel
{
    Q_OBJECT
public:
    MyLabel(const QString text = "", QWidget *parent=nullptr);
protected:
    void mousePressEvent(QMouseEvent *ev);
signals:
    void left_press();
    void right_press();
};

#endif // MYLABEL_H

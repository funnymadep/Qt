#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPixmap>
#include <QPen>
#include <QDebug>
#include <QTimerEvent>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    void paintEvent(QPaintEvent *ev);
    void timerEvent(QTimerEvent *ev);
private:
    QPixmap *pixmap;
    QPoint *hpoint, *mpoint, *spoint;
    int hangle, mangle, sangle;
};
#endif // WIDGET_H

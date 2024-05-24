#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QComboBox>
#include <QLabel>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    QStackedWidget *sw;
    QLabel *l1, *l2, *l3;
    QComboBox *cbb;
};
#endif // WIDGET_H

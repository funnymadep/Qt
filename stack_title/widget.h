#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QLabel>
#include <QStackedWidget>
#include <QGroupBox>
#include <QDebug>
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    QLabel *l[3];
    QStackedWidget *sw;
    QRadioButton *rb1[4], *rb2[4], *rb3[4];
    QGroupBox *gbox[3];
    int score;
};
#endif // WIDGET_H

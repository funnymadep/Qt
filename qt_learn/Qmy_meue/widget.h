#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QLabel *l_acc, *l_pass;
    QPushButton *pb_login, *pb_reg;
    QLineEdit *le_acc, *le_pass;
    QCheckBox *cb1, *cb2;
};
#endif // WIDGET_H

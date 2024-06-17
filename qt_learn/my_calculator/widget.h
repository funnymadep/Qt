#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QFont>
#include <QLineEdit>
#include <QGridLayout>
#include <iostream>
using namespace std ;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    QPushButton *pb1, *pb2, *pb3, *pb4, *pb5, *pb6, *pb7;
    QPushButton *n0, *n1, *n2, *n3, *n4, *n5, *n6, *n7, *n8, *n9;
    QLineEdit *le;
    double numb[2];
    char sig[2];
private slots:
    void add();
    void subtract();
    void multi();
    void except();
    void clear();
    void square();
    void equil();
    void e_no();
    void e_n1();
    void e_n2();
    void e_n3();
    void e_n4();
    void e_n5();
    void e_n6();
    void e_n7();
    void e_n8();
    void e_n9();
};
#endif // WIDGET_H

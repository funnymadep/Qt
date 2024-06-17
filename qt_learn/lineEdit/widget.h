#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLine>
#include <QFont>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
 private slots:
    void add();
    void jian();
 private:
    QPushButton *pb1, *pb2;
    QLineEdit *le;
};
#endif // WIDGET_H

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFont>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QInputDialog>
#include <QFileDialog>
#include <QColorDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QFile>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    QPushButton *pb1, *pb2, *pb3, *pb4, *pb5;
    QTextEdit *te;
private slots:
    void pb1_clicked();
    void pb2_clicked();
    void pb3_clicked();
    void pb4_clicked();
    void pb5_clicked();
};
#endif // WIDGET_H

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSlider>
#include <QScrollBar>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QLineEdit>
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    QSlider *sd;
    QScrollBar *sb;
    QProgressBar *pgb;
    QLineEdit *le;
private slots:
    void show_num();
};
#endif // WIDGET_H

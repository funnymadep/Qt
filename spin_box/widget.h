#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QFont>
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    QSpinBox *sb;
    QLineEdit *le;
};
#endif // WIDGET_H

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QFile>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    QVBoxLayout *mainLayout;
    QLineEdit *qul;
    QLineEdit *nameEdit;
    QLineEdit *dateEdit;

private slots:
        void   onQulBtnClicked();

};
#endif // WIDGET_H

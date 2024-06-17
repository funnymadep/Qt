#ifndef MYTEST_H
#define MYTEST_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QStackedWidget>
#include <QGroupBox>
#include <QRadioButton>
#include <QPushButton>
#include <QTimer>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include "result.h"

class MyTest : public QWidget
{
    Q_OBJECT
public:
    explicit MyTest(QWidget *parent = nullptr);

signals:

private slots:
    void down_count();
    void next_question();
    void submit_test();

private:
    QLabel *l_score, *l_time;
    QLineEdit *le_score, *le_time;
    QStackedWidget *sw;
    QGroupBox *gbox[3];
    QLabel *l_question[3];
    QRadioButton *rb[3][4];
    QPushButton *pb_next, *pb_submit;
    QTimer *timer;

    int answer[3];
    int score;
    int count;
};

#endif // MYTEST_H

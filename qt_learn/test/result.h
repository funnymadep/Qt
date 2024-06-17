#ifndef RESULT_H
#define RESULT_H

#include <QObject>
#include <QWidget>
#include <QLabel>

class Result : public QWidget
{
    Q_OBJECT
public:
    explicit Result(int num, QWidget *parent = nullptr);

signals:

private:
    QLabel *l;
    int score;

};

#endif // RESULT_H

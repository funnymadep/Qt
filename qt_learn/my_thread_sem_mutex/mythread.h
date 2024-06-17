#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QSemaphore>
#include <iostream>
using namespace  std;

extern int arr[10];
extern QSemaphore sem1, sem2;
extern QMutex mutex1;

class mythread : public QThread
{
    Q_OBJECT
public:
    mythread();
protected:
    void run();
};

#endif // MYTHREAD_H

#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>
class mythread : public QThread
{
    Q_OBJECT
public:
    mythread();
protected:
    void run();
};

#endif // MYTHREAD_H

#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>

class mythread : public QThread
{
    Q_OBJECT
public:
    mythread();
};

#endif // MYTHREAD_H

#include <QCoreApplication>
#include <QThread>
#include <QDebug>
#include "mythread.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    mythread *th = new mythread;
    th->start();

    while(1){
        qDebug() << "hello world";
        QThread::sleep(1);
    }

    return a.exec();
}

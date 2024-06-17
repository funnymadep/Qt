#include <QCoreApplication>
#include <QSemaphore>
#include <QMutex>
#include <iostream>
#include "mythread.h"
#include <QThread>
using namespace std;

int arr[10] = {0,1,2,3,4,5,6,7,8,9};
QSemaphore sem1(1), sem2(0);
QMutex mutex1;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    mythread *th = new mythread;
    th->start();

    while(1){
        sem1.acquire();
        for (int i = 0; i < 10; i++){
            cout << arr[i] << " ";
        }
        cout << endl;
        sem2.release();
        QThread::sleep(1);
    }

    return a.exec();
}

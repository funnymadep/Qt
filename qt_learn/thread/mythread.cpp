#include "mythread.h"

mythread::mythread()
{


}

void mythread::run()
{
    while (1) {
        qDebug() << "nihao";
        sleep(1);
    }
}

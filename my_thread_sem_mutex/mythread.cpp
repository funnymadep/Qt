#include "mythread.h"

mythread::mythread()
{

}

void mythread::run()
{
    while(1){
        sem2.acquire();
        for (int i = 9; i >= 0; i--){
            cout << arr[i] << " ";
        }
        cout << endl;
        sem1.release();
        QThread::sleep(1);
    }
}

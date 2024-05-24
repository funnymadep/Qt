#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); //管理整个应用程序
    Widget w; //界面对象
    w.show(); //显示界面
    return a.exec(); //事件队列
}

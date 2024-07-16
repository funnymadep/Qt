#include "mainWidget.h"
#include "global.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); //管理整个应用程序

    QFile file("../src/style.css");
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        a.setStyleSheet(styleSheet);
    }

    mainWidget w;       //界面对象
    w.show();           //显示界面

    int result = a.exec();
    return result;
}
#include "mainWidget.h"
#include <rclcpp/rclcpp.hpp>
#include <QFile>
#include <QObject>
#include <QWidget>
#include <QProcess>
#include <QApplication>
#include "point_cloud_subscriber.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); //管理整个应用程序
    QFile file("./src/hit_Qt/src/style.css");
    if (file.open(QFile::ReadOnly)) {
        qDebug() << "open css";
        qDebug() << file.fileName();
        QString styleSheet = QLatin1String(file.readAll());
        a.setStyleSheet(styleSheet);
    }
    rclcpp::init(argc, argv);
    mainWidget w;       //界面对象
    w.show();           //显示界面
    int result = a.exec();
    if (10 == result)
    {
        QStringList str;
        QProcess::startDetached(qApp->applicationFilePath(), str);
    }
    rclcpp::shutdown();
    return result;
}
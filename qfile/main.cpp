#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QDateTime>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QFile file("1.txt");
    if (file.exists())
        qDebug() << "open successfully!";
    else
        qDebug() << "open failed!";

    file.copy("2.txt");

    QFileInfo finfo("1.txt");
    qDebug() << finfo.created().toString("yyyy-MM-dd hh:mm:ss A dddd");
    qDebug() << finfo.size();
    qDebug() << finfo.absoluteFilePath();
    qDebug() << finfo.absoluteDir();
    qDebug() << finfo.suffix();


    return a.exec();
}

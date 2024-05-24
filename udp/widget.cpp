#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    socket = new QUdpSocket;
    if (!socket->bind(QHostAddress("192.168.12.182"), 8888)){
        qDebug() << "bind error" << socket->errorString();
        return;
    }
    connect(socket, &QUdpSocket::readyRead, [=](){
        char buf[1024] = {0};
        socket->readDatagram(buf, 1024, &ip, &port);
        ui->textEdit_2->setText(buf);
        ui->pushButton->setEnabled(true);
    });
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    QString str = ui->textEdit->toPlainText();
    if (str.isEmpty()){
        QMessageBox::warning(this, "发送数据", "文本不能为空");
        return;
    }
    socket->writeDatagram(str.toLatin1(), ip, port);
}

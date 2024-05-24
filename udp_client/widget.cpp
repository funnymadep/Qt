#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    socket = new QUdpSocket;

    connect(socket, &QUdpSocket::readyRead, [=](){
        char buf[1024] = {0};
        socket->readDatagram(buf, 1024);
        ui->textEdit_2->setText(buf);
    });
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    QString ip = ui->lineEdit->text();
    QString port = ui->lineEdit_2->text();
    if (ip.isEmpty() || port.isEmpty()){
        QMessageBox::warning(this, "连接", "ip和port不能为空");
        return;
    }
    QString str = ui->textEdit->toPlainText();
    if (str.isEmpty()){
        QMessageBox::warning(this, "发送", "发送框不能为空");
        return;
    }
    socket->writeDatagram(str.toLatin1(), QHostAddress(ip), port.toUShort());
}

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    server = new QTcpServer;
    if(!server->listen(QHostAddress::AnyIPv4, 8888)){
        qDebug() << "listen error:" << server->errorString();
        return;
    }

    connect(server, &QTcpServer::newConnection, this, &Widget::accept_client);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{

}

void Widget::accept_client()
{
    if(server->hasPendingConnections()){
        socket = server->nextPendingConnection();
        ui->pushButton->setEnabled(true);
    }

    connect(socket, &QTcpSocket::readyRead, this, )
}

void Widget::disconnect_client()
{

}

void Widget::recv_data()
{

}

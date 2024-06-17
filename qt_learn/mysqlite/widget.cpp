#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("my.db");
    if (!db.open()){
        qDebug() << "open sql" << db.lastError().text();
        return;
    }

    query = new QSqlQuery(db);

    QString sql = "create table if not exists user(name text, pswd text)";
    if (!query->exec(sql))
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{

}

void Widget::on_pushButton_2_clicked()
{

}

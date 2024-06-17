#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    pb1 = new QPushButton("文本对话框");
    pb2 = new QPushButton("输入对话框");
    pb3 = new QPushButton("消息框");
    pb4 = new QPushButton("字体对话框");
    pb5 = new QPushButton("颜色对话框");

    te = new QTextEdit;

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(pb1);
    vbox->addWidget(pb2);
    vbox->addWidget(pb3);
    vbox->addWidget(pb4);
    vbox->addWidget(pb5);

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addLayout(vbox);
    hbox->addWidget(te);
    setLayout(hbox);

    connect(pb1, &QPushButton::clicked, this, &Widget::pb1_clicked);
    connect(pb2, &QPushButton::clicked, this, &Widget::pb2_clicked);
    connect(pb3, &QPushButton::clicked, this, &Widget::pb3_clicked);
    connect(pb4, &QPushButton::clicked, this, &Widget::pb4_clicked);
    connect(pb5, &QPushButton::clicked, this, &Widget::pb5_clicked);
}

Widget::~Widget()
{
}

void Widget::pb1_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "open file", ".",
            "Tests(*h *cpp *c *txt)");
    if (filename.isEmpty())
        return;
    te->setText(filename);
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
        te->setText("打开文件失败" + file.errorString());
    te->append(file.readAll());
    file.close();
}

void Widget::pb2_clicked()
{
    bool ok;
    QString str = QInputDialog::getText(this, "文本对话框", "请输入你的年龄", QLineEdit
                                        ::Normal, "hql", &ok) ;

}

void Widget::pb3_clicked()
{


}

void Widget::pb4_clicked()
{

}

void Widget::pb5_clicked()
{

}


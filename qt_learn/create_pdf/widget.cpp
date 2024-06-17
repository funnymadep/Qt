#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
        mainLayout = new QVBoxLayout();
        setLayout(mainLayout);
        {
            QHBoxLayout *h = new QHBoxLayout();
            mainLayout->addLayout(h);

            QLabel *l = new QLabel(tr("输入网址"));
            h->addWidget(l);
            qul = new QLineEdit(this);
            h->addWidget(qul);
        }
        {
            QHBoxLayout *h = new QHBoxLayout();
            mainLayout->addLayout(h);

            QLabel *nl = new QLabel(tr("输入名字"));
            h->addWidget(nl);
            nameEdit = new QLineEdit(this);
            h->addWidget(nameEdit);

            QLabel *dl = new QLabel(tr("输入日期"));
            h->addWidget(dl);
            dateEdit = new QLineEdit(this);
            h->addWidget(dateEdit);
        }
        {
            QHBoxLayout *h = new QHBoxLayout();
            mainLayout->addLayout(h);

            QPushButton *btn = new QPushButton(tr("生成pdf"));
            connect(btn, &QPushButton::clicked, this, &Widget::onQulBtnClicked);
            h->addWidget(btn);
            h->addStretch();
        }
}

Widget::~Widget() {}

void Widget::onQulBtnClicked(){
    QString name = nameEdit->text();
    QString date = dateEdit->text();
    QString Qul = qul->text();

    if (name.isEmpty() || date.isEmpty() || Qul.isEmpty()){
        QMessageBox::Warning(this, tr("生成pdf"), tr("错误:必须全部行都输入!"));
        return;
    }

    QString filenameEC = date + ' ' + name + tr("中英.pdf");
    QString filenameE = date + ' ' + name + tr("英文.pdf");
    QString filenameC = date + ' ' + name + tr("中文.pdf");
    QString filenameEE = date + ' ' + name + tr("音标.pdf");

    QString path = "E:\soursedownload";
}

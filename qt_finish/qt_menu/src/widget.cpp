#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //主界面布局 垂直布局
    QVBoxLayout *vlayout = new QVBoxLayout();
    {
        //布局 启动QGroupBox 里嵌套QHBoxLayout
        QGroupBox *gbox = new QGroupBox(tr("启动"));
        vlayout->addWidget(gbox);
        QHBoxLayout *h = new QHBoxLayout();
        gbox->setLayout(h);

        mStartBtn = new QPushButton(tr("启动"));
        mStartBtn->setFixedSize(100, 30);
        h->addStretch(1);
        h->addWidget(mStartBtn);
        connect(mStartBtn, &QPushButton::clicked, this, &Widget::mStartBtnClicked);

        mDataRecordBtn = new QPushButton(tr("数据录制"));
        mDataRecordBtn->setFixedSize(100, 30);
        h->addWidget(mDataRecordBtn);
        h->addStretch(1);
        connect(mDataRecordBtn, &QPushButton::clicked, this, &Widget::mDataRecordBtnClicked);
    }
    //数据保存QGroupBox
    QGroupBox *gbox = new QGroupBox(tr("数据保存"));
    vlayout->addWidget(gbox);
    QVBoxLayout *v = new QVBoxLayout();
    gbox->setLayout(v);
    {
        //数据回放水平布局
        QHBoxLayout *h = new QHBoxLayout();
        v->addLayout(h);
        mDataPlaybackBtn = new QPushButton(tr("数据回放"));
        mDataPlaybackBtn->setFixedSize(100,30);
        h->addStretch(1);
        h->addWidget(mDataPlaybackBtn);
        connect(mDataPlaybackBtn, &QPushButton::clicked, this, &Widget::mDataPlaybackBtnClicked);

        mDataRecodeEdit = new QLineEdit(this);
        mDataRecodeEdit->setReadOnly(true);
        mDataRecodeEdit->setFixedSize(400,30);
        h->addWidget(mDataRecodeEdit);
        h->addStretch(1);
    }
    {
        //数据间隔水平布局
        QHBoxLayout *h = new QHBoxLayout();
        v->addLayout(h);
        QLabel *label = new QLabel(tr("数据间隔:"));
        label->setFixedSize(100, 30);
        h->addStretch(1);
        h->addWidget(label);

        mDataIntervalSpin = new QDoubleSpinBox(this);
        mDataIntervalSpin->setSuffix("s");
        mDataIntervalSpin->setFixedSize(100, 30);
        mDataIntervalSpin->setSingleStep(0.01);
        mDataIntervalSpin->setRange(0.0, 100.0);
        h->addWidget(mDataIntervalSpin);
        h->addStretch(1);

    }
    {
        //数据保存格式水平布局
        QHBoxLayout *h = new QHBoxLayout();
        v->addLayout(h);
        QLabel *label = new QLabel(tr("数据保存格式"));
        label->setFixedSize(100, 30);
        h->addStretch(1);
        h->addWidget(label);

        mDataTypeCombo = new QComboBox(this);
        mDataTypeCombo->setFixedSize(100, 30);
        QStringList typeList;
        typeList << tr("pcd") << tr("ply");
        mDataTypeCombo->addItems(typeList);
        mDataTypeCombo->setCurrentText(tr("pcd"));
        h->addWidget(mDataTypeCombo);
        h->addStretch(1);
    }
    {
        //是否保存地面数据 水平布局
        QHBoxLayout *h = new QHBoxLayout();
        v->addLayout(h);
        QLabel *label = new QLabel(tr("是否保存地面数据："));
        label->setFixedSize(100, 30);
        h->addStretch(1);
        h->addWidget(label);

        mDataSelectCombo = new QComboBox(this);
        QStringList typeList;
        typeList << tr("yes") << tr("no");
        mDataSelectCombo->addItems(typeList);
        mDataSelectCombo->setCurrentText(tr("no"));
        mDataSelectCombo->setFixedSize(100, 30);
        h->addWidget(mDataSelectCombo);
        h->addStretch(1);
    }
    {
        //数据保存水平布局
        QHBoxLayout *h = new QHBoxLayout();
        v->addLayout(h);
        mDataSaveBtn = new QPushButton(tr("数据保存"));
        mDataSaveBtn->setFixedSize(100,30);
        mDataSaveBtn->setEnabled(false);
        h->addStretch(1);
        h->addWidget(mDataSaveBtn);
        connect(mDataSaveBtn, &QPushButton::clicked, this, &Widget::mDataSaveBtnClicked);
        h->addStretch(1);
    }
    setLayout(vlayout);
}

Widget::~Widget()
{

}

//数据回放的槽函数
void Widget::mDataPlaybackBtnClicked(){
    QString filePath = QFileDialog::getOpenFileName(this, tr("数据回放"), "..", tr("Image Files (*.png *.jpg *.bmp *.cpp *.db3)"));
    mDataRecodeEdit->setText(filePath);

    //判断文件后缀
    QFileInfo info(filePath);
    if (info.suffix() != tr("db3"))
    {
        QMessageBox::critical(this, "数据回放", "必须选择.db3文件");
        mDataSaveBtn->setEnabled(false);
        return;
    }

    //获得文件夹路径
    savePath = info.absolutePath();
    // qDebug() << savePath;

    //如果lineedit里面没有.db3 那么就不能保存
    if (mDataRecodeEdit->text().contains(".db3"))
    {
        mDataSaveBtn->setEnabled(true);
        return;
    }
}

//数据保存槽函数
void Widget::mDataSaveBtnClicked(){
    float dataInterval;
    QString saveType;
    bool isSaveGround;

    //判断数据间隔是否为空
    if (mDataIntervalSpin->text().isEmpty())
    {
        QMessageBox::critical(this, "数据保存", "数据间隔内容为空");
        return;
    }
    else{
        dataInterval = mDataIntervalSpin->value();
        // 数据间隔数据大于0
        if (0 == dataInterval)
        {
            QMessageBox::critical(this, tr("数据保存"), tr("数据间隔应为大于0的数字"));
            return;
        }
    }

    saveType = mDataTypeCombo->currentText();

    //判断是否保存地面数据
    if (mDataSelectCombo->currentText() == tr("yes"))
    {
        isSaveGround = true;
    }
    else
    {
        isSaveGround = false;
    }
    
    // QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), savePath, tr("Curve TagName Files (*.%1)").arg(saveType));
    // qDebug() << fileName;
    // if (!fileName.isEmpty())
    // {
    //     fileName = fileName + '.' + saveType;
    //     QFile file(fileName);
    //     if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
    //     {
    //         QMessageBox::critical(this, tr("Error"), tr("Failed to open file \"%1\" for save!").arg(fileName), QMessageBox::Ok);
    //         return;
    //     }
    //     //write file
    //     // QTextStream wr(&file);
    //     QMessageBox::information(this, tr("information"), tr("保存成功"));
    //     file.close();
    // }
    // else
    //     return;       

    //保存文件     
    QString fileName = "filename";
    fileName = savePath + '/' + fileName + '.' + saveType;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QMessageBox::critical(this, tr("Error"), tr("Failed to open file \"%1\" for save!").arg(fileName), QMessageBox::Ok);
        return;
    }

    // QMessageBox::information(this, tr("information"), tr("保存成功"));
    file.close();

    //write file
    // QTextStream wr(&file);

    //如果数据回放不是.db3 那么不能保存
    if (!mDataRecodeEdit->text().contains(tr(".db3")))
    {
        mDataSaveBtn->setEnabled(false);
    }
}

//启动槽函数
void Widget::mStartBtnClicked(){
    QProcess* executeProcess = new QProcess();
    executeProcess->start("/bin/bash", QStringList() << "../hello.sh");
    qDebug() << "启动";
    // mDataSaveBtn->setEnabled(true);
}

//视频录制槽函数
void Widget::mDataRecordBtnClicked(){
    qDebug() << "数据录制";
}
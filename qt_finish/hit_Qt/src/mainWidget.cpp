#include "mainWidget.h"
#include <QTreeWidgetItem>
#include <QHBoxLayout>

mainWidget::mainWidget(QWidget *parent)
    : QWidget(parent)
{
    //主界面布局 垂直布局
    mlayout = new QVBoxLayout();
    init();
    setLayout(mlayout);
    setAutoFillBackground(true);
}

mainWidget::~mainWidget()
{
    
}

void mainWidget::init()
{
    createLogo();

    QHBoxLayout *h = new QHBoxLayout();
    mlayout->addLayout(h);
    createMenu(h);
    createMainPage(h);
    resize(700, 700);
}

void mainWidget::createLogo()
{
    QHBoxLayout *h = new QHBoxLayout();
    mlayout->addLayout(h);
    h->addStretch();
    QLabel *label = new QLabel(tr("hit 项目"),this);
    h->addWidget(label);
    h->addStretch();
}

void mainWidget::createMenu(QHBoxLayout *h)
{
        QTreeWidget *mTreeWidget = new QTreeWidget();
        h->addWidget(mTreeWidget);
        // 隐藏表头
        mTreeWidget->setHeaderHidden(true);
        mTreeWidget->setMinimumWidth(200);  
        mTreeWidget->setMaximumWidth(250);

        // 添加菜单项
        QTreeWidgetItem *laserRoot = new QTreeWidgetItem(mTreeWidget, QStringList() << "3D 激光雷达");
        new QTreeWidgetItem(laserRoot, QStringList() << "电气房左侧激光");
        new QTreeWidgetItem(laserRoot, QStringList() << "电气房右侧激光");
        new QTreeWidgetItem(laserRoot, QStringList() << "动力室左侧激光");
        new QTreeWidgetItem(laserRoot, QStringList() << "动力室右侧激光");

        QTreeWidgetItem *cameraRoot = new QTreeWidgetItem(mTreeWidget, QStringList() << "相机图像");
        new QTreeWidgetItem(cameraRoot, QStringList() << "电气房左侧近景相机");
        new QTreeWidgetItem(cameraRoot, QStringList() << "电气房左侧远景相机");
        new QTreeWidgetItem(cameraRoot, QStringList() << "电气房右侧近景相机");
        new QTreeWidgetItem(cameraRoot, QStringList() << "电气房右侧远景相机");
        new QTreeWidgetItem(cameraRoot, QStringList() << "电气房外侧俯视相机");
        new QTreeWidgetItem(cameraRoot, QStringList() << "电气房内侧俯视相机");
        new QTreeWidgetItem(cameraRoot, QStringList() << "动力室外侧俯视相机");

        // 添加系统日志和系统设置
        new QTreeWidgetItem(mTreeWidget, QStringList() << "系统日志");
        new QTreeWidgetItem(mTreeWidget, QStringList() << "系统设置");

        connect(mTreeWidget, &QTreeWidget::itemClicked, this, &mainWidget::handleItemClicked);
}

void mainWidget::handleItemClicked(QTreeWidgetItem *item) {
    QString itemName = item->text(0);  // 获取被点击的 QTreeWidgetItem 的第一个列的文本

    if (itemName.contains(tr("激光"))) {
            if (!lidar) {
                lidar = new lidarWidget(this);
                mStackedWgt->addWidget(lidar);
            }
            mStackedWgt->setCurrentWidget(lidar);
    }

    if(itemName.contains(tr("相机")))
    {
        if (camera == nullptr)
        {
            camera = new cameraWidget();
            mStackedWgt->addWidget(camera);
        }
        mStackedWgt->setCurrentWidget(camera);
    }
    else
    {
        if (camera)
        {
            mStackedWgt->removeWidget(camera);
            delete camera;  // 删除对象，释放内存
            camera = nullptr;
        }
    }
    
    if(itemName == "系统日志")
    {
        if (syslog == nullptr)
        {
            syslog = new sysLogWidget();
            mStackedWgt->addWidget(syslog);
        }
        mStackedWgt->setCurrentWidget(syslog);
    }
    else
    {
        if (syslog)
        {
            mStackedWgt->removeWidget(syslog);
            delete syslog;  // 删除对象，释放内存
            syslog = nullptr;
        }
    }

    if(itemName == "系统设置")
    {
        if (sysSetting == nullptr)
        {
            sysSetting = new sysSettingWidget();
            mStackedWgt->addWidget(sysSetting);
        }
        mStackedWgt->setCurrentWidget(sysSetting);
    }
    else
    {
        if (sysSetting)
        {
            mStackedWgt->removeWidget(sysSetting);
            delete sysSetting;  // 删除对象，释放内存
            sysSetting = nullptr;
        }
    }
}

void mainWidget::createMainPage(QHBoxLayout *h)
{
    mStackedWgt = new QStackedWidget(this);
    h->addWidget(mStackedWgt);
    
}

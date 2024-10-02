#include "mainWidget.h"
#include <QTreeWidgetItem>
#include <QHBoxLayout>
#include <QProcess>

bool lidarChange = false;

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
    // QProcess *bag_start = new QProcess();
    // bag_start->start("python3", QStringList() << tr("/home/sd-robot/hql_test/bag_test/bag_record.py"));
    QHBoxLayout *h = new QHBoxLayout();
    mlayout->addLayout(h);
    createMenu(h);
    createMainPage(h);
    // resize(700, 700);
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
        new QTreeWidgetItem(cameraRoot, QStringList() << "电气房内侧相机");
        new QTreeWidgetItem(cameraRoot, QStringList() << "电气房外侧相机");
        new QTreeWidgetItem(cameraRoot, QStringList() << "电气房左补盲相机");
        new QTreeWidgetItem(cameraRoot, QStringList() << "电气房右补盲相机");
        new QTreeWidgetItem(cameraRoot, QStringList() << "动力房外侧相机");

        // 添加系统日志和系统设置
        // new QTreeWidgetItem(mTreeWidget, QStringList() << "系统日志");
        new QTreeWidgetItem(mTreeWidget, QStringList() << "系统设置");
        new QTreeWidgetItem(mTreeWidget, QStringList() << "点云回放");
        new QTreeWidgetItem(mTreeWidget, QStringList() << "相机回放");

        connect(mTreeWidget, &QTreeWidget::currentItemChanged, this, &mainWidget::handleItemClicked);
}

void mainWidget::handleItemClicked(QTreeWidgetItem *current, QTreeWidgetItem *previous) {
    QString itemName = current->text(0);  // 获取被点击的 QTreeWidgetItem 的第一个列的文本
    // resize(1080, 1080);
    // setMinimumSize(800,800);
    if (itemName.contains(tr("激光"))) 
    {
        lidarTopic = NO_LIDAR;
        if (itemName == "电气房左侧激光")
        {
            lidarTopic = LIDAR_EL;
            lidarChange = true;
        }
        else if (itemName == "电气房右侧激光")
        {
            lidarTopic = LIDAR_ER;
            lidarChange = true;
        }
        else if (itemName == "动力室左侧激光")
        {
            lidarTopic = LIDAR_PL;  
            lidarChange = true;
        }
        else if (itemName == "动力室右侧激光")
        {
            lidarTopic = LIDAR_PR;
            lidarChange = true;
        }

        if (!lidar) {
            lidar = new lidarWidget(this);
            mStackedWgt->addWidget(lidar);
        }
        mStackedWgt->setCurrentWidget(lidar);
        resize(900, 850);
    }
    else
    {
        if (lidar)
        {
            // qDebug() << "***";
            mStackedWgt->removeWidget(lidar);
            lidar->deleteLater();
            lidar = nullptr;
        }
    }

    if(itemName.contains(tr("相机")))
    {
        cameraTopic = NO_CAMERA;
        if (itemName == "电气房内侧相机")
        {
            cameraTopic = CAMERA_EI;
        }
        else if (itemName == "电气房外侧相机")
        {
            cameraTopic = CAMERA_EO;
        }
        else if (itemName == "电气房左补盲相机")
        {
            cameraTopic = CAMERA_EL;  
        }
        else if (itemName == "电气房右补盲相机")
        {
            cameraTopic = CAMERA_ER;
        }
        else if (itemName == "动力房外侧相机")
        {
            cameraTopic = CAMERA_PO;
        }

        if (camera == nullptr)
        {
            camera = new cameraWidget();
            mStackedWgt->addWidget(camera);
            connect(this, &mainWidget::emitCameraSignal, camera, &cameraWidget::readConfiguration);
        }
        emit emitCameraSignal();
        mStackedWgt->setCurrentWidget(camera);
        resize(1000, 850);
        // qDebug() << "test";

    }
    else
    {
        if (camera)
        {
            disconnect(this, &mainWidget::emitCameraSignal, camera, &cameraWidget::readConfiguration);
            mStackedWgt->removeWidget(camera);
            camera->deleteLater();  // 删除对象，释放内存
            camera = nullptr;
        }
    }
    
    // if(itemName == "系统日志")
    // {
    //     if (syslog == nullptr)
    //     {
    //         syslog = new sysLogWidget();
    //         mStackedWgt->addWidget(syslog);
    //     }
    //     mStackedWgt->setCurrentWidget(syslog);
    // }
    // else
    // {
    //     if (syslog)
    //     {
    //         mStackedWgt->removeWidget(syslog);
    //         syslog->deleteLater();  // 删除对象，释放内存
    //         syslog = nullptr;
    //     }
    // }

    if(itemName == "系统设置")
    {
        if (sysSetting == nullptr)
        {
            sysSetting = new sysSettingWidget();
            mStackedWgt->addWidget(sysSetting);
        }
        mStackedWgt->setCurrentWidget(sysSetting);
        resize(700, 650);
    }
    else
    {
        if (sysSetting)
        {
            mStackedWgt->removeWidget(sysSetting);
            sysSetting->deleteLater();  // 删除对象，释放内存
            sysSetting = nullptr;
        }
    }
    
    if(itemName == "点云回放")
    {
        if (recordCloud == nullptr)
        {
            recordCloud = new recordWidget();
            
            mStackedWgt->addWidget(recordCloud);
        }
        mStackedWgt->setCurrentWidget(recordCloud);
        resize(900, 850);
    }
    else
    {
        if (recordCloud)
        {
            mStackedWgt->removeWidget(recordCloud);
            recordCloud->deleteLater();  // 删除对象，释放内存
            recordCloud = nullptr;
        }
    }

    if(itemName == "相机回放")
    {
        if (recordCamera == nullptr)
        {
            recordCamera = new recordCameraWidget();
            
            mStackedWgt->addWidget(recordCamera);
        }
        mStackedWgt->setCurrentWidget(recordCamera);
        resize(900, 850);
    }
    else
    {
        if (recordCamera)
        {
            mStackedWgt->removeWidget(recordCamera);
            recordCamera->deleteLater();  // 删除对象，释放内存
            recordCamera = nullptr;
        }
    }
}

void mainWidget::createMainPage(QHBoxLayout *h)
{
    mStackedWgt = new QStackedWidget(this);
    h->addWidget(mStackedWgt);
    
}

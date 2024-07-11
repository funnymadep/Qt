#include "mainWidget.h"

mainWidget::mainWidget(QWidget *parent)
    : QWidget(parent)
{
    //主界面布局 垂直布局
    mlayout = new QVBoxLayout();
    init();
    setLayout(mlayout);
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
        // 将 treeWidget 添加到布局中
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

    // 检查是否是“电气房左侧激光”被点击
    if (itemName == "电气房左侧激光")
    {
        QMessageBox::information(this, "Item Clicked", "电气房左侧激光 被点击了");
            // 在这里添加具体的处理逻辑
        if (lidar == nullptr)
        {
            lidar = new lidarWidget();
            mStackedWgt->addWidget(lidar);
        }
        mStackedWgt->setCurrentWidget(lidar);
        
    }
    else if(itemName == "电气房左侧近景相机")
    {
        if (camera == nullptr)
        {
            camera = new cameraWidget();
            mStackedWgt->addWidget(camera);
        }
        mStackedWgt->setCurrentWidget(camera);
    }
}

void mainWidget::createMainPage(QHBoxLayout *h)
{
    mStackedWgt = new QStackedWidget(this);
    h->addWidget(mStackedWgt);
    
}

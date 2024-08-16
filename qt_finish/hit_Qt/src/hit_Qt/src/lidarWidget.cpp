#include "lidarWidget.h"
#include "point_cloud_subscriber.h"
#include <QPushButton>
#include <QLineEdit>
#include <pcl/compression/octree_pointcloud_compression.h>
#include <QThread>
#include <iostream>

lidarWidget::lidarWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *hlayout = new QHBoxLayout();
    setLayout(hlayout);

    QVBoxLayout *vLeft = new QVBoxLayout();
    hlayout->addLayout(vLeft);
    createStatus(vLeft);
    createCloudPoint(vLeft);
    createSetting(hlayout);
}

lidarWidget::~lidarWidget()
{
    
}

void lidarWidget::createStatus(QVBoxLayout *vLeft)
{
    QVBoxLayout *v = new QVBoxLayout();
    vLeft->addLayout(v);
    {
        QHBoxLayout *h = new QHBoxLayout();
        v->addLayout(h);

        mLabelStatus = new QLabel(tr("激光状态: 正常"),this);
        mLabelStatus->setMaximumSize(150, 32);
        h->addWidget(mLabelStatus);
        
        h->addSpacing(50);

        mLabelIsHide = new QLabel(tr("是否遮挡: 是"),this);
        mLabelIsHide->setMaximumSize(150, 32);
        h->addWidget(mLabelIsHide);

        h->addStretch();
    }
    {
        QHBoxLayout *h = new QHBoxLayout();
        v->addLayout(h);

        mLabelIsBlock = new QLabel(tr("是否存在障碍物: 否"),this);
        mLabelIsBlock->setMaximumSize(150, 32);
        h->addWidget(mLabelIsBlock);

        h->addSpacing(30);

        mLabelBlockLen = new QLabel(tr("最近障碍物距离: 100CM"),this);
        mLabelBlockLen->setMaximumSize(150, 32);
        h->addWidget(mLabelBlockLen);

        h->addStretch();
    }
    {
        QHBoxLayout *h = new QHBoxLayout();
        v->addLayout(h);

        mLabelAntiCollisionMode = new QLabel(tr("防撞模式: 自动"),this);
        mLabelAntiCollisionMode->setMaximumSize(150, 32);
        h->addWidget(mLabelAntiCollisionMode);
        h->addStretch();
    }
    // v->addStretch();

}

void lidarWidget::createCloudPoint(QVBoxLayout *vLeft)
{
    vtkWidget = new QVTKOpenGLNativeWidget(this);
    vLeft->addWidget(vtkWidget);

    initializeViewer();

    server = new Server;
    connect(server, &Server::cloudReceived, this, &lidarWidget::handlePointCloudReceived);

    PointThread *thread = new PointThread;
    thread->start(); 
}

void lidarWidget::createSetting(QHBoxLayout *hlayout)
{
    QVBoxLayout *v = new QVBoxLayout();
    hlayout->addLayout(v);

    v->addStretch();
    comb = new QComboBox(this);
    v->addWidget(comb);

    QStringList items;
    items << tr("基于车道线解算") << tr("自定义区域");
    comb->addItems(items);
    comb->setCurrentText(tr("基于车道线解算"));
    connect(comb, &QComboBox::currentTextChanged, this, &lidarWidget::combChange);

    {
        QHBoxLayout *h = new QHBoxLayout();
        v->addLayout(h);
        QLabel *lateralDistanceLabel = new QLabel(tr("防撞横向距离: "));
        h->addWidget(lateralDistanceLabel);

        lateralDistanceEdit = new QLineEdit(this);
        lateralDistanceEdit->setEnabled(false);
        h->addWidget(lateralDistanceEdit);
    }
    {
        QHBoxLayout *h = new QHBoxLayout();
        v->addLayout(h);
        QLabel *longitudinalDistanceLabel = new QLabel(tr("防撞纵向距离: "));
        h->addWidget(longitudinalDistanceLabel);

        longitudinalDistanceEdit = new QLineEdit(this);
        longitudinalDistanceEdit->setEnabled(false);
        h->addWidget(longitudinalDistanceEdit);
    }
    {
        QHBoxLayout *h = new QHBoxLayout();
        v->addLayout(h);
        QPushButton *addCubeBtn = new QPushButton(tr("添加距离"));
        h->addWidget(addCubeBtn);
        connect(addCubeBtn, &QPushButton::clicked, this, &lidarWidget::addCube);

        QPushButton *delCube = new QPushButton(tr("删除距离"));
        h->addWidget(delCube);
        connect(delCube, &QPushButton::clicked, this, &lidarWidget::delCube);
    }
    {
        QHBoxLayout *h = new QHBoxLayout();
        v->addLayout(h);

        colorType = new QComboBox();
        h->addWidget(colorType);
        QStringList items;
        items << tr("x") << tr("y") << tr("z") << tr("i");
        colorType->addItems(items);
        colorType->setCurrentText(tr("x"));
    }
    
    v->addStretch();
}

void lidarWidget::combChange(const QString &context)
{
    if (context == tr(("基于车道线解算")))
    {
        longitudinalDistanceEdit->setEnabled(false);
        lateralDistanceEdit->setEnabled(false);
        longitudinalDistanceEdit->clear();
        lateralDistanceEdit->clear();
    }
    else
    {
        longitudinalDistanceEdit->setEnabled(true);
        lateralDistanceEdit->setEnabled(true);
    }
}

void lidarWidget::addCube()
{
    double max_x = lateralDistanceEdit->text().toDouble();
    double max_y = longitudinalDistanceEdit->text().toDouble(); 

    double max_z = 0.5;
    double min_x = 0.0, min_y = 0.0, min_z = 0.0;
    double r = 1.0, g = 0.0, b = 0.0;
    // 定义立方体的最小点和最大点
    if (!viewer->contains("cube"))
    {
        // 设置颜色为红色
        viewer->addCube(min_x, max_x, min_y, max_y, min_z, max_z, r, g, b, "cube");
        viewer->setShapeRenderingProperties(pcl::visualization::PCL_VISUALIZER_REPRESENTATION, pcl::visualization::PCL_VISUALIZER_REPRESENTATION_WIREFRAME, "cube");
    }
    else
    {
        viewer->removeShape("cube");
        viewer->addCube(min_x, max_x, min_y, max_y, min_z, max_z, r, g, b, "cube");
        viewer->setShapeRenderingProperties(pcl::visualization::PCL_VISUALIZER_REPRESENTATION, pcl::visualization::PCL_VISUALIZER_REPRESENTATION_WIREFRAME, "cube");
    }
}

void lidarWidget::delCube()
{
    if (viewer->contains("cube"))
    {
        viewer->removeShape("cube");
    }
}

void lidarWidget::initializeViewer() {
    renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    vtkWidget->setRenderWindow(renderWindow);

    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderWindow->AddRenderer(renderer);

    viewer.reset(new pcl::visualization::PCLVisualizer(renderer, renderWindow, "viewer", false));
    vtkWidget->setRenderWindow(viewer->getRenderWindow());
    viewer->setupInteractor(vtkWidget->interactor(), vtkWidget->renderWindow());

    viewer->setBackgroundColor(0.1, 0.1, 0.1);
    viewer->addCoordinateSystem(1.0);
    viewer->initCameraParameters();
}

void lidarWidget::handlePointCloudReceived(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud)
{
    // QByteArray data = socket->readAll();
    // std::stringstream compressedData(data.toStdString());
    // pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;
    // pcl::io::OctreePointCloudCompression<pcl::PointXYZ> octreeDecompression;
    // octreeDecompression.decodePointCloud(compressedData, cloud);

    viewer->removeAllPointClouds();
    std::string color = colorType->currentText().toStdString();
    // std::cout << color << endl;
    pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZ> z(cloud, color);
    viewer->addPointCloud(cloud , z, color);
    vtkWidget->update();
    // viewer->resetCamera();  // 重置相机以查看新点云
    renderWindow->Render();
    // update();
}


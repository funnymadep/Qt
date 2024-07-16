#include "pointCloudWidget.h"
#include <boost/asio.hpp>
#include <pcl/io/pcd_io.h>
#include <pcl/compression/octree_pointcloud_compression.h>
#include <QVBoxLayout>
#include <QDebug>

using boost::asio::ip::tcp;

pointCloudWidget::pointCloudWidget(QWidget *parent) :
    QWidget(parent),
    vtkWidget(new QVTKOpenGLNativeWidget(this))
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(vtkWidget);
    setLayout(layout);

    initializeViewer();
    connect(this, &pointCloudWidget::pointCloudReceived, this, &pointCloudWidget::handlePointCloudReceived);
    receivePointCloud();
}

pointCloudWidget::~pointCloudWidget() {}

void pointCloudWidget::initializeViewer() {
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

// 实现文件中的函数定义

void pointCloudWidget::receivePointCloud() {
    boost::asio::io_service io_service;
    tcp::resolver resolver(io_service);
    tcp::resolver::query query("127.0.0.1", "12345");


        try {
            tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

            tcp::socket socket(io_service);
            boost::asio::connect(socket, endpoint_iterator);

            pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
            uint32_t dataSize;

            // 读取数据大小
            boost::asio::read(socket, boost::asio::buffer(&dataSize, sizeof(dataSize)));

            // 读取数据本身
            std::vector<char> data(dataSize);
            boost::asio::read(socket, boost::asio::buffer(data));

            // 解压点云数据
            std::stringstream compressedData(std::string(data.begin(), data.end()));
            pcl::io::OctreePointCloudCompression<pcl::PointXYZ> decompressor;
            decompressor.decodePointCloud(compressedData, cloud);

            // 发射信号，在合适的线程上通知界面更新点云数据
            emit pointCloudReceived(cloud);

            qDebug() << "接收到点云数据并发送信号成功。";

        } catch (std::exception& e) {
            qDebug() << "接收点云数据失败：" << e.what();
        }
    
}

void pointCloudWidget::handlePointCloudReceived(const pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud)
{
    viewer->removeAllPointClouds();
    viewer->addPointCloud(cloud);
    vtkWidget->update();
}


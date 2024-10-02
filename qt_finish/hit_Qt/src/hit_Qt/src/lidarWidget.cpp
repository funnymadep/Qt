#include "lidarWidget.h"
#include "point_cloud_subscriber.h"
#include <QPushButton>
#include <QLineEdit>
#include <pcl/compression/octree_pointcloud_compression.h>
#include <QThread>
#include <iostream>
#include <QGroupBox>

lidarWidget::lidarWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *hlayout = new QHBoxLayout();
    setLayout(hlayout);

    QVBoxLayout *vLeft = new QVBoxLayout();
    hlayout->addLayout(vLeft);
    createStatus(vLeft);
    createCloudPoint(vLeft);
    createSetting(vLeft);
}

lidarWidget::~lidarWidget()
{
    lidarSwitch = false;
    if (lidar_thread_.joinable()) {
        lidar_thread_.join();
    }
    // int run_stop = 0;
    // thread->setRun(run_stop);
    // disconnect(thread, &PointThread::pointCloudReceived, this, &lidarWidget::handlePointCloudReceived);
    // thread->deleteLater();
}

void lidarWidget::createStatus(QVBoxLayout *vLeft)
{
    // QVBoxLayout *v = new QVBoxLayout();

    // QVBoxLayout* gv = new QVBoxLayout();
    // QGroupBox *gBox = new QGroupBox();
    // vLeft->addWidget(gBox);
    // gBox->setLayout(gv);
    // vLeft->addLayout(v);
    {
        QHBoxLayout *h = new QHBoxLayout();
        vLeft->addLayout(h);
  


        mLabelStatus = new QLabel(tr("激光状态: 正常"),this);
        mLabelStatus->setMaximumSize(150, 32);
        h->addWidget(mLabelStatus);
        
        // h->addSpacing(50);

        // mLabelIsHide = new QLabel(tr("是否遮挡: 是"),this);
        // mLabelIsHide->setMaximumSize(150, 32);
        // h->addWidget(mLabelIsHide);

        h->addStretch();
    }
    {
        QHBoxLayout *h = new QHBoxLayout();
        vLeft->addLayout(h);

        mLabelIsBlock = new QLabel(tr("是否存在障碍物: 否"),this);
        mLabelIsBlock->setMaximumSize(150, 32);
        h->addWidget(mLabelIsBlock);

        h->addSpacing(30);

        mLabelBlockLen = new QLabel(tr("最近障碍物距离: 100CM"),this);
        mLabelBlockLen->setMaximumSize(170, 32);
        h->addWidget(mLabelBlockLen);

        h->addStretch();
    }
    {
        QHBoxLayout *h = new QHBoxLayout();
        vLeft->addLayout(h);

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
    // vLeft->addStretch();

    initializeViewer();

    // server = new Server;
    // PointCloudSubscriber *subscriber = new PointCloudSubscriber;
    
    // lidarThread = new lidarRunnable();
    // lidarThread->start();


    // thread = new PointThread;
    // thread->start(); 

    lidar_thread_ = std::thread([this]() {
            auto node = std::make_shared<lidarNode>();
            rclcpp::executors::MultiThreadedExecutor executor;
            executor.add_node(node);
            // cv::namedWindow("显示窗口", cv::WINDOW_AUTOSIZE);
            // connect(this, &cameraWidget::emitCameraMsg, this, &cameraWidget::handleCameraImage);
            lidarSwitch = true;
            while(rclcpp::ok() && lidarSwitch)
            {
                emit emitLidarMsg();
                // qDebug() << "lidar_runnable";
            // rclcpp::spin_some(node);
                executor.spin_once(std::chrono::milliseconds(100));
            
            // std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 避免高CPU占用   
            }
    });
    connect(this, &lidarWidget::emitLidarMsg, this, &lidarWidget::handlePointCloudReceived);

}

// void lidarWidget::createSetting(QHBoxLayout *hlayout)
void lidarWidget::createSetting(QVBoxLayout *vleft)
{
    // QVBoxLayout *v = new QVBoxLayout();
    // hlayout->addLayout(v);

    // v->addStretch();
    // comb = new QComboBox(this);
    // vleft->addWidget(comb);

    // QStringList items;
    // items << tr("基于车道线解算") << tr("自定义区域");
    // comb->addItems(items);
    // comb->setCurrentText(tr("基于车道线解算"));
    // connect(comb, &QComboBox::currentTextChanged, this, &lidarWidget::combChange);

    // {
    //     QHBoxLayout *h = new QHBoxLayout();
    //     v->addLayout(h);
    //     QLabel *lateralDistanceLabel = new QLabel(tr("防撞横向距离: "));
    //     h->addWidget(lateralDistanceLabel);

    //     lateralDistanceEdit = new QLineEdit(this);
    //     lateralDistanceEdit->setEnabled(false);
    //     h->addWidget(lateralDistanceEdit);
    // }
    // {
    //     QHBoxLayout *h = new QHBoxLayout();
    //     v->addLayout(h);
    //     QLabel *longitudinalDistanceLabel = new QLabel(tr("防撞纵向距离: "));
    //     h->addWidget(longitudinalDistanceLabel);

    //     longitudinalDistanceEdit = new QLineEdit(this);
    //     longitudinalDistanceEdit->setEnabled(false);
    //     h->addWidget(longitudinalDistanceEdit);
    // }
    // {
    //     QHBoxLayout *h = new QHBoxLayout();
    //     v->addLayout(h);
    //     QPushButton *addCubeBtn = new QPushButton(tr("添加距离"));
    //     h->addWidget(addCubeBtn);
    //     connect(addCubeBtn, &QPushButton::clicked, this, &lidarWidget::addCube);

    //     QPushButton *delCube = new QPushButton(tr("删除距离"));
    //     h->addWidget(delCube);
    //     connect(delCube, &QPushButton::clicked, this, &lidarWidget::delCube);
    // }
    {
        QHBoxLayout *h = new QHBoxLayout();
        vleft->addLayout(h);

        colorType = new QComboBox();
        h->addWidget(colorType);
        QStringList items;
        items << tr("x") << tr("y") << tr("z") << tr("intensity");
        colorType->addItems(items);
        colorType->setCurrentText(tr("x"));
    }
    
    // v->addStretch();
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
    viewer->setCameraPosition(-15, 0, 5,
        0, 0, 0,
        0, 0, 1);
}

void lidarWidget::handlePointCloudReceived()
{
    if (lidarChange)
    {
        viewer->removeAllPointClouds();
        viewer->removeAllShapes();
        // viewer->removea
        lidarChange = false;
        lidar_marker.markers.clear();
        std::cout << "cubeidsize: " << cubeIds.size() << "textidsize" << textIds.size() << std::endl;
    }
    
    // if (viewer->contains("text_"))
    // {
        // qDebug() << "1";
    // }

    for (const auto& cubeId : cubeIds) {
        if (viewer->contains(cubeId)) {
            std::cout << "Removing text: " << cubeId << std::endl;
            viewer->removeText3D(cubeId);
        }
    }   

        // for (const auto& id : textIds) {
    for (const auto& textId : textIds) {
        if (viewer->contains(textId)) {
            std::cout << "Removing text: " << textId << std::endl;
            viewer->removeText3D(textId);
        }
    }

    // 清空 ID 列表
    cubeIds.clear();
    textIds.clear();

    // short last_topic;
    // short current_topic = lidar_cloud;


    // viewer->removeAllPointClouds();
    std::string color = colorType->currentText().toStdString();
    if (lidar_cloud && !lidar_cloud->empty()) {
        cloudQueue.push_back(lidar_cloud);
        std::string id_string = "cloud" + std::to_string(id++);
        idsQueue.push_back(id_string);
        // pcl::PointCloud<pcl::PointXYZI>::Ptr accumulatedCloud(new pcl::PointCloud<pcl::PointXYZI>);
        pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZI> CloudColorHandler(lidar_cloud, color);
        viewer->addPointCloud(lidar_cloud , CloudColorHandler, id_string);
        if (cloudQueue.size() > maxCloudCount) {
            // std::cout << id << " " << cloudQueue.size()<< std::endl;
            viewer->removePointCloud(idsQueue.front());
            cloudQueue.pop_front();
            idsQueue.pop_front();
            if (id == maxCloudCount+1)
            {
                id = 0;
            }
        }
        // std::cout << id_string << " " << std::endl;
    }

    // QElapsedTimer timer;
    // timer.start();
    // if (cloud_block) {
    for (const auto &marker : lidar_marker.markers) {
        if (marker.action == visualization_msgs::msg::Marker::DELETE) {
            // viewer->removeShape("cube_" + std::to_string(marker.id));
            continue; // 跳过删除操作
        }

        if (marker.type == visualization_msgs::msg::Marker::CUBE) 
        {
            // 添加立方体到PCLVisualizer
            std::string cubeId = "cube_" + std::to_string(marker.id);
            viewer->removeShape("cube_" + std::to_string(marker.id));
            viewer->addCube(marker.pose.position.x - (marker.scale.x / 2.0), marker.pose.position.x + (marker.scale.x / 2.0),
                            marker.pose.position.y - (marker.scale.y / 2.0), marker.pose.position.y + (marker.scale.y / 2.0),
                            marker.pose.position.z - (marker.scale.z / 2.0), marker.pose.position.z + (marker.scale.z / 2.0),
                            marker.color.r, marker.color.g, marker.color.b, 
                            "cube_" + std::to_string(marker.id));
            // std::cout << "cube_" + std::to_string(marker.id) << " " << std::endl;
            cubeIds.push_back(cubeId);
            // std::cout << "x: " << marker.pose.position.x << " y: " << marker.pose.position.y 
            //     << " z: " << marker.pose.position.z ;
            // std::cout << "scale x: " << marker.scale.x << "scale y: " << marker.scale.y 
            //     << "scale z: " << marker.scale.z << std::endl;
            viewer->setShapeRenderingProperties(pcl::visualization::PCL_VISUALIZER_OPACITY, marker.color.a, "cube_" + std::to_string(marker.id));
        } 
        else if (marker.type == visualization_msgs::msg::Marker::TEXT_VIEW_FACING) 
        {
          std::string textId = "text_" + std::to_string(marker.id);
            viewer->removeText3D("text_" + std::to_string(marker.id));
            std::cout << std::endl << "text_" + std::to_string(marker.id) << " " << std::endl;
            // }
            viewer->addText3D(marker.text, pcl::PointXYZ(marker.pose.position.x, marker.pose.position.y, marker.pose.position.z),
                              marker.scale.z, // 文本大小
                              marker.color.r, marker.color.g, marker.color.b, "text_" + std::to_string(marker.id));
            viewer->setShapeRenderingProperties(pcl::visualization::PCL_VISUALIZER_OPACITY, marker.color.a, "text_" + std::to_string(marker.id));
            textIds.push_back(textId);  // 记录 text_ ID
        }
            // }
    }
    // qDebug() << "The slow operation took" << timer.elapsed() << "milliseconds";
    // viewer->addPointCloud(cloud_block , x, color);
    vtkWidget->update();
    // viewer->resetCamera();  // 重置相机以查看新点云
    renderWindow->Render();
    // lidar_marker.markers.clear();
    // update();
}


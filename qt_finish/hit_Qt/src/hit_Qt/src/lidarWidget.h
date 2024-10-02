#ifndef LIDAR_WIDGET_H
#define LIDAR_WIDGET_H 

#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QTcpSocket>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <QVTKOpenGLNativeWidget.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <visualization_msgs/msg/marker.hpp>
#include <pcl/visualization/pcl_visualizer.h>
// #include <pcl/octree/impl/octree_base.hpp>
// #include <pcl/octree/impl/octree_pointcloud.hpp>
#include <pcl/common/io.h>
// #include "point_cloud_subscriber.h"
#include <deque>
#include <vector>
#include "global.h"
#include "rosRunnable.h"
#include "rosNode.h"

using PointCloud = pcl::PointCloud<pcl::PointXYZ>;

class lidarWidget : public QWidget
{
    Q_OBJECT

public:
    lidarWidget(QWidget *parent = nullptr);
    ~lidarWidget();

    void createStatus(QVBoxLayout *vLeft);
    void createCloudPoint(QVBoxLayout *vLeft);
    void createSetting(QVBoxLayout *vleft);
    void initializeViewer();

private slots:
    void handlePointCloudReceived();
    void combChange(const QString &context);
    void addCube();
    void delCube();
    // void connectToServer();

signals:
    void emitLidarMsg();

private:
    QLabel *mLabelStatus = nullptr;
    QLabel *mLabelIsHide = nullptr;
    QLabel *mLabelIsBlock = nullptr;
    QLabel *mLabelBlockLen = nullptr;
    QLabel *mLabelAntiCollisionMode = nullptr;
    QComboBox *comb = nullptr;
    QComboBox *colorType = nullptr;
    QLineEdit *lateralDistanceEdit = nullptr;
    QLineEdit *longitudinalDistanceEdit = nullptr;
    QTimer *timer;
    // Server *server;
    QVTKOpenGLNativeWidget *vtkWidget;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow;
    pcl::visualization::PCLVisualizer::Ptr viewer;

    // PointThread *thread;
    lidarRunnable *lidarThread;
    std::thread lidar_thread_;

    std::deque<pcl::PointCloud<pcl::PointXYZI>::Ptr> cloudQueue; // 用来保存最近的5次点云数据
    std::deque<std::string> idsQueue;
    long id = 0;
    const int maxCloudCount = 10; // 叠加点云的最大数量
    std::vector<std::string> cubeIds;  // 记录所有的 cube_ 标记 ID
    std::vector<std::string> textIds;  // 记录所有的 text_ 标记 ID
};




#endif // CLIENT_H



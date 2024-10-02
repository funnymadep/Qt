#ifndef RECORD_WIDGET_H
#define RECORD_WIDGET_H 

#include <QWidget>
#include <QComboBox>
// #include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
// #include <QTimer>
#include <QDateTimeEdit>
#include <QProcess>
#include <QStackedWidget>
#include <QTableWidget>
// #include <QObject>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <QVTKOpenGLNativeWidget.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/compression/octree_pointcloud_compression.h>
// #include <pcl/octree/impl/octree_base.hpp>
// #include <pcl/octree/impl/octree_pointcloud.hpp>
#include <pcl/common/io.h>
#include "point_cloud_subscriber.h"
#include <deque>
#include "rosRunnable.h"
#include "global.h"
using PointCloud = pcl::PointCloud<pcl::PointXYZ>;

class recordWidget : public QWidget
{
    Q_OBJECT

public:
    recordWidget(QWidget *parent = nullptr);
    ~recordWidget();

    // void createStatus(QVBoxLayout *v);
    void createStackedWidget(QVBoxLayout *v);
    void createSetting(QVBoxLayout *v);
    void createViewer();
    void createSearch();
    void createRecord();
    void initRos();
    void initializeViewer();
    QStringList getDirList();
    QStringList getDirPartList(QString name);
    QStringList getRecordList();
    void writeRecordTxt(QString txt);
    void delRecordTxt(QString txt);
    void playBag(QString name);
    void compressZSTD(QString selectedDirPath);

private slots:
    void handlePointCloudReceived();
    void recordBagClicked();
    void onPlayButtonClicked();
    void pageChanged(QString str);
    void topicCombChange(QString str);
    void recordPlayClicked();
    void delRecordClicked();
    void mvRecordClicked();
    // void connectToServer();
    
private:
    QComboBox *mPageComb = nullptr;
    QComboBox *mTopicComb = nullptr;
    QLineEdit *lateralDistanceEdit = nullptr;
    QLineEdit *longitudinalDistanceEdit = nullptr;
    QStackedWidget *mStackerWgt = nullptr;
    
    QTimer *timer;
    QWidget *mViewerWgt = nullptr;
    QWidget *mSearchWgt = nullptr;
    QWidget *mRecordWgt = nullptr;
    QTableWidget *mTableWgt = nullptr;
    QTableWidget *mRecordTableWgt = nullptr;
    QDateTimeEdit *dateTimeEdit = nullptr;
    QProcess *mBagPlay = nullptr;

    // Server *server;
    QVTKOpenGLNativeWidget *vtkWidget;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow;
    pcl::visualization::PCLVisualizer::Ptr viewer;
    recordRunnable *mRecord = nullptr;
    QStackedWidget *mStackWgt = nullptr;


    std::deque<pcl::PointCloud<pcl::PointXYZI>::Ptr> cloudQueue; // 用来保存最近的5次点云数据
    std::deque<std::string> idsQueue;
    long id = 0;
    const int maxCloudCount = 5; // 叠加点云的最大数量
};




#endif // CLIENT_H



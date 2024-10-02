#ifndef POINT_CLOUD_SUBSCRIBER_H
#define POINT_CLOUD_SUBSCRIBER_H
#include <QDebug>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h> 
#include <pcl_conversions/pcl_conversions.h>
#include <QCoreApplication>
#include <QObject>
#include <QThread>
// #include <ifstream>
// #include <pcl/compression/octree_pointcloud_compression.h>
#include <pcl/common/io.h>
// #include <pcl/octree/impl/octree_base.hpp>
// #include <pcl/octree/impl/octree_pointcloud.hpp>
#include <pcl/io/pcd_io.h>
#include <boost/asio.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
// #include <visualization_msgs/msg/marker.hpp>
#include <visualization_msgs/msg/marker_array.hpp>

// #include <boost/serialization/access.hpp>
#include <mutex>
#include <condition_variable>

using PointCloud = pcl::PointCloud<pcl::PointXYZ>;
using boost::asio::ip::tcp;

extern pcl::PointCloud<pcl::PointXYZI>::Ptr cloud_trans;
extern visualization_msgs::msg::MarkerArray cloud_block;
extern std::mutex mtx;
extern std::mutex bmtx;
// extern std::condition_variable cv;


class PointCloudSubscriber : public QObject , public rclcpp::Node{
    Q_OBJECT
public:
    PointCloudSubscriber();
    ~PointCloudSubscriber();
signals:
    

private:
    void topic_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg);
    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr subscription_oringin;

    void block_callback(const visualization_msgs::msg::MarkerArray::SharedPtr msg);
    rclcpp::Subscription<visualization_msgs::msg::MarkerArray>::SharedPtr subscription_block;

    double lidar_param_el[16] = {0.999743104, 0.0160416272, 0.0160119571, -0.0210943874,
        -0.0165318344, 0.999383688, 0.0309679117, 0.0159573108,
        -0.015505312, -0.031224668, 0.999392092, 0.551909884,
        0, 0, 0, 1}; //Done

    double lidar_param_er[16] = {0.997329533, 0.0728661269, 0.00493951887, -0.0210204162,
        -0.0729164928, 0.997278273, 0.0109249335, 0.0127795637,
        -0.00413001655, -0.0112559311, 0.999928117, 0.5386180567,
        0, 0, 0, 1}; //Done

    double lidar_param_pl[16] ={0.9991225,0.0396473818, 0.0135016516, -0.0796372369,
        -0.0395415, 0.999185801, -0.00802087598, 0.0204944909,
        -0.0138086677, 0.00747996289 ,0.999876618, 0.590474367,
        0, 0, 0 ,1}; //Done

    double lidar_param_pr[16] = {0.999424338, 0.0262180883, 0.021532299, -0.0487143099,
        -0.0265778974, 0.999509, 0.0165977031, -0.0674420297,
        -0.0210865662, -0.0171604324, 0.999630392, 0.5304,
        0, 0, 0, 1}; //Done
};


class PointThread : public QThread 
{
    Q_OBJECT
public:
    PointThread(){ m_run = 1; };
    ~PointThread(){ m_run = 0; }
    void setRun(int run);
signals:
    void pointCloudReceived();
protected:
    void run();
private:
    int m_run;
};

#endif // POINT_CLOUD_SUBSCRIBER_H

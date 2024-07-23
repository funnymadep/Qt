#ifndef POINT_CLOUD_SUBSCRIBER_H
#define POINT_CLOUD_SUBSCRIBER_H
#include <QDebug>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <pcl/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <QCoreApplication>
#include <QObject>
#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include <pcl/compression/octree_pointcloud_compression.h>
#include <pcl/common/io.h>
#include <boost/asio.hpp>

using PointCloud = pcl::PointCloud<pcl::PointXYZ>;
using boost::asio::ip::tcp;

class PointCloudSubscriber : public QObject , public rclcpp::Node{
     Q_OBJECT
public:
    PointCloudSubscriber();

signals:
    void pointCloudReceived(PointCloud::Ptr cloud);

private:
    void topic_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg);
    boost::asio::io_service io_service_;
    tcp::socket socket_;
    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr subscription_;
};


class PointThread : public QThread 
{
    Q_OBJECT
public:
    PointThread(){};
protected:
    void run();
private:

};

#endif // POINT_CLOUD_SUBSCRIBER_H

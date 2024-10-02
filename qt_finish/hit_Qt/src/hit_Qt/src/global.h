#ifndef GLOBAL_H
#define GLOBAL_H

#include <QDebug>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h> 
#include <pcl_conversions/pcl_conversions.h>
#include <QCoreApplication>
#include <QObject>
#include <iostream>
// #include <ifstream>
// #include <pcl/compression/octree_pointcloud_compression.h>
#include <pcl/common/io.h>
// #include <pcl/octree/impl/octree_base.hpp>
// #include <pcl/octree/impl/octree_pointcloud.hpp>
#include <pcl/io/pcd_io.h>
#include <sensor_msgs/msg/point_cloud2.hpp>
// #include <visualization_msgs/msg/marker.hpp>
#include <visualization_msgs/msg/marker_array.hpp>
#include <mutex>
#include <QImage>
#include <deque>

#define NO_RECORD -1
#define RECORD_EL 0
#define RECORD_ER 1
#define RECORD_PL 2
#define RECORD_PR 3

#define NO_LIDAR -1
#define LIDAR_EL 0
#define LIDAR_ER 1
#define LIDAR_PL 2
#define LIDAR_PR 3

#define NO_CAMERA -1
#define CAMERA_EL 0
#define CAMERA_ER 1
#define CAMERA_EI 2
#define CAMERA_EO 3
#define CAMERA_PO 4

extern short recordTopic;
extern short lidarTopic;
extern short cameraTopic;
extern bool lidarChange;
extern pcl::PointCloud<pcl::PointXYZI>::Ptr record_cloud;

extern pcl::PointCloud<pcl::PointXYZI>::Ptr record_cloud_el;
extern pcl::PointCloud<pcl::PointXYZI>::Ptr record_cloud_er;
extern pcl::PointCloud<pcl::PointXYZI>::Ptr record_cloud_pl;
extern pcl::PointCloud<pcl::PointXYZI>::Ptr record_cloud_pr;


extern std::deque<pcl::PointCloud<pcl::PointXYZI>::Ptr> record_vector;
extern pcl::PointCloud<pcl::PointXYZI>::Ptr lidar_cloud;
extern pcl::PointCloud<pcl::PointXYZI>::Ptr camera_cloud;
extern visualization_msgs::msg::MarkerArray lidar_marker;
extern std::mutex recordmtx;
extern std::mutex lidarmtx;
extern std::mutex blockmtx;
extern std::mutex cameramtx;
/* 接收点云回放数据 */
extern QImage camera_image;
extern bool recordSwitch;
extern bool lidarSwitch;
extern bool cameraSwitch;

#endif
#ifndef ROS_NODE_H
#define ROS_NODE_H

#include <QDebug>
#include <opencv2/opencv.hpp>
#include <random>
#include <unordered_map>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/msg/image.hpp>
#include <thread>
#include "yolov8_msgs/msg/detection_array.hpp"
#include "global.h"



class recordNode : public QObject , public rclcpp::Node{
    Q_OBJECT
public:
    recordNode();
    ~recordNode();
signals:
    

private:
    rclcpp::CallbackGroup::SharedPtr callback_group_livox;
    // std::deque<pcl::PointCloud<pcl::PointXYZI>::Ptr> mRecord_vector;

    void eltopic_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg);
    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr subscription_el;

    void ertopic_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg);
    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr subscription_er;

    void pltopic_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg);
    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr subscription_pl;

    void prtopic_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg);
    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr subscription_pr;

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



/* 负责接收雷达数据  */
class lidarNode : public QObject , public rclcpp::Node{
    Q_OBJECT
public:
    lidarNode();
    ~lidarNode();
signals:
    

private:
    rclcpp::CallbackGroup::SharedPtr callback_group_livox;
    rclcpp::CallbackGroup::SharedPtr callback_group_gty;

    // rclcpp::CallbackGroup::SharedPtr callback_group_livox_er;
    // rclcpp::CallbackGroup::SharedPtr callback_group_gty_er;

    // rclcpp::CallbackGroup::SharedPtr callback_group_livox_pl;
    // rclcpp::CallbackGroup::SharedPtr callback_group_gty_pl;

    // rclcpp::CallbackGroup::SharedPtr callback_group_livox_pr;
    // rclcpp::CallbackGroup::SharedPtr callback_group_gty_pr;
    void el_131_topic_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg);
    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr subscription_el_131;

    void er_321_topic_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg);
    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr subscription_er_321;

    void pl_371_topic_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg);
    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr subscription_pl_371;

    void pr_171_topic_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg);
    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr subscription_pr_171;

    void eltopic_callback(const visualization_msgs::msg::MarkerArray::SharedPtr msg);
    rclcpp::Subscription<visualization_msgs::msg::MarkerArray>::SharedPtr subscription_el;

    void ertopic_callback(const visualization_msgs::msg::MarkerArray::SharedPtr msg);
    rclcpp::Subscription<visualization_msgs::msg::MarkerArray>::SharedPtr subscription_er;

    void pltopic_callback(const visualization_msgs::msg::MarkerArray::SharedPtr msg);
    rclcpp::Subscription<visualization_msgs::msg::MarkerArray>::SharedPtr subscription_pl;

    void prtopic_callback(const visualization_msgs::msg::MarkerArray::SharedPtr msg);
    rclcpp::Subscription<visualization_msgs::msg::MarkerArray>::SharedPtr subscription_pr;


    void livox_callback(const sensor_msgs::msg::PointCloud2::ConstSharedPtr &msg);
    void gty_callback(const visualization_msgs::msg::MarkerArray::ConstSharedPtr &msg);

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


/* 负责接收摄像头数据  */
class cameraNode : public QObject , public rclcpp::Node{
    Q_OBJECT
public:
    cameraNode();
    ~cameraNode();
signals:
    
private:
    rclcpp::CallbackGroup::SharedPtr callback_group_livox;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_e_left;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_2;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_3;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_4;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_5;

    typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::msg::Image, yolov8_msgs::msg::DetectionArray> MySyncPolicy;
    std::shared_ptr<message_filters::Synchronizer<MySyncPolicy>> sync_e_left;
    std::shared_ptr<message_filters::Synchronizer<MySyncPolicy>> sync_e_right;
    std::shared_ptr<message_filters::Synchronizer<MySyncPolicy>> sync_eroom_in;
    std::shared_ptr<message_filters::Synchronizer<MySyncPolicy>> sync_eroom_out;
    std::shared_ptr<message_filters::Synchronizer<MySyncPolicy>> sync_proom_out;

    message_filters::Subscriber<sensor_msgs::msg::Image> image_e_left;
    message_filters::Subscriber<yolov8_msgs::msg::DetectionArray> detection_camera_e_left;

    message_filters::Subscriber<sensor_msgs::msg::Image> image_e_right;
    message_filters::Subscriber<yolov8_msgs::msg::DetectionArray> detection_camera_e_right;

    message_filters::Subscriber<sensor_msgs::msg::Image> image_eroom_in;
    message_filters::Subscriber<yolov8_msgs::msg::DetectionArray> detection_camera_eroom_in;

    message_filters::Subscriber<sensor_msgs::msg::Image> image_eroom_out;
    message_filters::Subscriber<yolov8_msgs::msg::DetectionArray> detection_camera_eroom_out;

    message_filters::Subscriber<sensor_msgs::msg::Image> image_proom_out;
    message_filters::Subscriber<yolov8_msgs::msg::DetectionArray> detection_camera_proom_out;

    std::thread thread_e_left;
    std::thread thread_e_right;
    std::thread thread_eroom_in;
    std::thread thread_eroom_out;
    std::thread thread_proom_out;

    // 颜色映射
    std::unordered_map<std::string, cv::Scalar> _class_to_color;
    // 随机生成颜色
    cv::Scalar random_color();
    // 绘制边框
    cv::Mat draw_box(cv::Mat& cv_image, const yolov8_msgs::msg::Detection& detection, const cv::Scalar& color);
    cv::Mat draw_mask(cv::Mat& cv_image, const yolov8_msgs::msg::Detection& detection, const cv::Scalar& color);
    // 回调函数
    void detections_e_left(const sensor_msgs::msg::Image::ConstSharedPtr img_msg, const yolov8_msgs::msg::DetectionArray::ConstSharedPtr detection_msg);
    void detections_e_right(const sensor_msgs::msg::Image::ConstSharedPtr img_msg, const yolov8_msgs::msg::DetectionArray::ConstSharedPtr detection_msg);
    void detections_eroom_in(const sensor_msgs::msg::Image::ConstSharedPtr img_msg, const yolov8_msgs::msg::DetectionArray::ConstSharedPtr detection_msg);
    void detections_eroom_out(const sensor_msgs::msg::Image::ConstSharedPtr img_msg, const yolov8_msgs::msg::DetectionArray::ConstSharedPtr detection_msg);
    void detections_proom_out(const sensor_msgs::msg::Image::ConstSharedPtr img_msg, const yolov8_msgs::msg::DetectionArray::ConstSharedPtr detection_msg);

    void detections1(const sensor_msgs::msg::Image::SharedPtr img_msg);
    void detections2(const sensor_msgs::msg::Image::SharedPtr img_msg);
    void detections3(const sensor_msgs::msg::Image::SharedPtr img_msg);
    void detections4(const sensor_msgs::msg::Image::SharedPtr img_msg);
    void detections5(const sensor_msgs::msg::Image::SharedPtr img_msg);
    // 转图片格式
    QImage cvMatToQImage(const cv::Mat &mat);
};

#endif
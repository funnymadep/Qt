#include "rosRunnable.h"
#include "rosNode.h"
#include "global.h"

bool recordSwitch;
bool lidarSwitch;
bool cameraSwitch;

recordRunnable::recordRunnable() 
{
    recordSwitch = true;
    // setAutoDelete(true);
}

void recordRunnable::stop()
{
    recordSwitch = false;
}

void recordRunnable::run()
{
    auto node = std::make_shared<recordNode>();
    rclcpp::executors::MultiThreadedExecutor executor;
    executor.add_node(node);
    while(rclcpp::ok() && recordSwitch)
    {
        // qDebug() << "1111111";
        emit emitRecordMsg();
        // rclcpp::spin_some(node);
        executor.spin_once();
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // 避免高CPU占用
    }
}

lidarRunnable::lidarRunnable() 
{
    lidarSwitch = true;
    // setAutoDelete(true);  
}

void lidarRunnable::stop()
{
    lidarSwitch = false;
}

void lidarRunnable::run()
{
    auto node = std::make_shared<lidarNode>();
    rclcpp::executors::MultiThreadedExecutor executor;
    // rclcpp::executors::MultiThreadedExecutor executor;
    // executor.set_thread_count(8);
    executor.add_node(node);
    while(rclcpp::ok() && lidarSwitch)
    {
        emit emitLidarMsg();
        // rclcpp::spin_some(node);
        executor.spin_once();
        // std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 避免高CPU占用   
    }
}

cameraRunnable::cameraRunnable()
{
    cameraSwitch = true;
    // setAutoDelete(true);   
}

void cameraRunnable::stop()
{
    cameraSwitch = false;
}

void cameraRunnable::run()
{
    auto node = std::make_shared<cameraNode>();
    rclcpp::executors::MultiThreadedExecutor executor;
    executor.add_node(node);
    // cv::namedWindow("显示窗口", cv::WINDOW_AUTOSIZE);
    while(rclcpp::ok() && cameraSwitch)
    {
        emit emitCameraMsg();
        // qDebug() << "runnable";
        // rclcpp::spin_some(node);
        executor.spin_once();
        
        // std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 避免高CPU占用   
    }
}
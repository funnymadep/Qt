#include "point_cloud_subscriber.h"
#include <thread>
#include <chrono>




PointCloudSubscriber::PointCloudSubscriber()
    : Node("point_cloud_subscriber") , io_service_(), socket_(io_service_) {
    subscription_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
        "/topic", 10,
        std::bind(&PointCloudSubscriber::topic_callback, this, std::placeholders::_1)
    );

    try {
        tcp::resolver resolver(io_service_);
        tcp::resolver::query query("127.0.0.1", "2222");
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

        boost::asio::connect(socket_, endpoint_iterator);
        RCLCPP_INFO(this->get_logger(), "Connected to server.");
    } catch (boost::system::system_error &e) {
        RCLCPP_ERROR(this->get_logger(), "Failed to connect to server: %s", e.what());
    }  

}

PointCloudSubscriber::~PointCloudSubscriber()
{
    
}

void PointCloudSubscriber::topic_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg) {
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::fromROSMsg(*msg, *cloud);
    // server->setCloud(cloud);

    std::stringstream compressedData;
    pcl::io::OctreePointCloudCompression<pcl::PointXYZ> octreeCompression;
    octreeCompression.encodePointCloud(cloud, compressedData);

    std::string data = compressedData.str();
    boost::asio::write(socket_, boost::asio::buffer(data));
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
}

void PointThread::run()
{
    auto node = std::make_shared<PointCloudSubscriber>();
    rclcpp::spin(node);
}

#include "point_cloud_subscriber.h"
#include <pcl/common/transforms.h>
#include <thread>
#include <chrono>
#include <QDebug>
#include <QElapsedTimer>

pcl::PointCloud<pcl::PointXYZI>::Ptr cloud_trans = std::make_shared<pcl::PointCloud<pcl::PointXYZI>>();
visualization_msgs::msg::MarkerArray cloud_block;
// visualization_msgs::msg::MarkerArray::SharedPtr cloud_block = std::make_shared<visualization_msgs::msg::MarkerArray>();
std::mutex mtx;
std::mutex bmtx;
// std::condition_variable cv;

PointCloudSubscriber::PointCloudSubscriber()
    : Node("point_cloud_subscriber")  {
    subscription_oringin = this->create_subscription<sensor_msgs::msg::PointCloud2>(
        "/livox/lidar_3GGDLCR00200371", 10,
        std::bind(&PointCloudSubscriber::topic_callback, this, std::placeholders::_1)
    );
    subscription_block = this->create_subscription<visualization_msgs::msg::MarkerArray>(
        "/gty_obstacle_pl", 10,
        std::bind(&PointCloudSubscriber::block_callback, this, std::placeholders::_1)
    );
    // try {
    //     tcp::resolver resolver(io_service_);
    //     tcp::resolver::query query("127.0.0.1", "2222");
    //     tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

    //     boost::asio::connect(socket_, endpoint_iterator);
    //     RCLCPP_INFO(this->get_logger(), "Connected to server.");
    // } catch (boost::system::system_error &e) {
    //     RCLCPP_ERROR(this->get_logger(), "Failed to connect to server: %s", e.what());
    // }  
}

PointCloudSubscriber::~PointCloudSubscriber()
{
    // rcp::shutdown();
}

void PointCloudSubscriber::topic_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg) {
    pcl::PointCloud<pcl::PointXYZI> cloud;
    pcl::fromROSMsg(*msg, cloud);
    // server->setCloud(cloud);
    // 配置压缩选项
    // pcl::io::compression_Profiles_e compressionProfile = pcl::io::HIGH_RES_ONLINE_COMPRESSION_WITH_COLOR;
    // bool showStatistics = true;
    // std::stringstream compressedData;
    // pcl::io::OctreePointCloudCompression<pcl::PointXYZI> octreeCompression(compressionProfile, showStatistics);
    // octreeCompression.encodePointCloud(cloud, compressedData);
    // std::string data = compressedData.str();

    // boost::asio::write(socket_, boost::asio::buffer(data));
    
    Eigen::Matrix4f LeftToGroundMatrix = Eigen::Matrix4f::Identity(4,4);
	// for(int i=0;i<16;i++)
	// 	LeftToGroundMatrix.<<lidar_param_pl[i];
	LeftToGroundMatrix<<lidar_param_pl[0],lidar_param_pl[1],lidar_param_pl[2],lidar_param_pl[3],
        lidar_param_pl[4],lidar_param_pl[5],lidar_param_pl[6],lidar_param_pl[7],
        lidar_param_pl[8],lidar_param_pl[9],lidar_param_pl[10],lidar_param_pl[11],
        lidar_param_pl[12],lidar_param_pl[13],lidar_param_pl[14],lidar_param_pl[15];
    // 	LeftToGroundMatrix ={0.997528016567, 0.069969959557, 0.006485231686, 0.043471455574,
    // -0.070057712495, 0.997437953949, 0.014469225891, 0.006741475314,
    // -0.005456201732, -0.014887800440, 0.999874174595, 0.510745823383,
    // 0.000000000000, 0.000000000000, 0.000000000000, 1.000000000000};
	// pcl::PointCloud<pcl::PointXYZI>::Ptr pcl_cloud_in(new pcl::PointCloud<pcl::PointXYZI>);
    std::unique_lock<std::mutex> lock(mtx);
	pcl::transformPointCloud(cloud, cloud, LeftToGroundMatrix);

	// out_cloud_data = new_cloud_data;

    *cloud_trans = cloud;
    
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
}

void PointCloudSubscriber::block_callback(const visualization_msgs::msg::MarkerArray::SharedPtr msg)
{
    // 创建一个新的 MarkerArray 用于存储变换后的数据
    visualization_msgs::msg::MarkerArray transformed_msg = *msg;
    // 对每个 marker 应用外参矩阵
    // 将变换后的数据赋值给 cloud_block
    std::unique_lock<std::mutex> lock(bmtx);

    // qDebug() << "1111111111111111111";
    cloud_block = transformed_msg;
    // cloud_block = msg;
    // std::this_thread::sleep_for(std::chrono::milliseconds(300));
}

void PointThread::run()
{
    auto node = std::make_shared<PointCloudSubscriber>();
    // rclcpp::spin(node);
    while (rclcpp::ok() && m_run) {
        // qDebug() << "1111111";
        emit pointCloudReceived();
        rclcpp::spin_some(node);
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 避免高CPU占用
    }

}

void PointThread::setRun(int run)
{
    m_run = run;
}
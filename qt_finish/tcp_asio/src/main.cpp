#include <iostream>
#include <thread>
#include <chrono>
#include <boost/asio.hpp>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/compression/octree_pointcloud_compression.h>

using boost::asio::ip::tcp;

void sendPointCloud(tcp::socket& socket, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud) {


    for (auto& point : cloud->points) {
        point.x = 1024 * rand() / (RAND_MAX + 1.0f);
        point.y = 1024 * rand() / (RAND_MAX + 1.0f);
        point.z = 1024 * rand() / (RAND_MAX + 1.0f);
    }

    // 压缩点云数据
    pcl::io::OctreePointCloudCompression<pcl::PointXYZ> compressor;
    std::stringstream compressedData;
    compressor.encodePointCloud(cloud, compressedData);

    // 发送压缩后的点云数据
    std::string data = compressedData.str();
    uint32_t dataSize = data.size();
    // boost::asio::write(socket, boost::asio::buffer(&dataSize, sizeof(dataSize)));
    // boost::asio::write(socket, boost::asio::buffer(data));
// 将数据大小和数据本身合并为一个发送缓冲区
    std::vector<boost::asio::const_buffer> buffers;
    buffers.push_back(boost::asio::buffer(&dataSize, sizeof(dataSize)));
    buffers.push_back(boost::asio::buffer(data));

    // 通过一个操作将全部数据发送给客户端
    boost::asio::write(socket, buffers);
}

int main() {
    boost::asio::io_service io_service;
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 12345));

    std::cout << "服务端启动，等待连接..." << std::endl;

    tcp::socket socket(io_service);
    acceptor.accept(socket);
    std::cout << "客户端已连接。" << std::endl;

    // 创建点云对象并填充随机数据
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    cloud->width = 10000;  // 设置点云的宽度
    cloud->height = 1;     // 设置点云的高度
    cloud->is_dense = false;
    cloud->points.resize(cloud->width * cloud->height);

    while (true) {
        sendPointCloud(socket, cloud);

        // 模拟点云生成间隔，可以根据需求调整
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
    

    std::cout << "点云数据已发送。" << std::endl;
    return 0;
}

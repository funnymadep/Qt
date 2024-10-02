#include "rosNode.h"
#include <pcl/common/transforms.h>


QImage camera_image;
std::mutex blockmtx;
std::mutex cameramtx;
std::mutex recordmtx;
std::mutex lidarmtx;
short recordTopic = 0;
short lidarTopic = 0;
short cameraTopic = 0;
pcl::PointCloud<pcl::PointXYZI>::Ptr record_cloud = std::make_shared<pcl::PointCloud<pcl::PointXYZI>>();
pcl::PointCloud<pcl::PointXYZI>::Ptr lidar_cloud = std::make_shared<pcl::PointCloud<pcl::PointXYZI>>();
pcl::PointCloud<pcl::PointXYZI>::Ptr camera_cloud = std::make_shared<pcl::PointCloud<pcl::PointXYZI>>();
visualization_msgs::msg::MarkerArray lidar_marker;
std::deque<pcl::PointCloud<pcl::PointXYZI>::Ptr> record_vector;

pcl::PointCloud<pcl::PointXYZI>::Ptr record_cloud_el(new pcl::PointCloud<pcl::PointXYZI>());
pcl::PointCloud<pcl::PointXYZI>::Ptr record_cloud_er(new pcl::PointCloud<pcl::PointXYZI>());
pcl::PointCloud<pcl::PointXYZI>::Ptr record_cloud_pl(new pcl::PointCloud<pcl::PointXYZI>());
pcl::PointCloud<pcl::PointXYZI>::Ptr record_cloud_pr(new pcl::PointCloud<pcl::PointXYZI>());

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++(方便查找) */
recordNode::recordNode()
    : Node("recordNode")  {
    callback_group_livox = this->create_callback_group(rclcpp::CallbackGroupType::Reentrant);
    rclcpp::SubscriptionOptions options_livox;
    options_livox.callback_group = callback_group_livox;   

    subscription_el = this->create_subscription<sensor_msgs::msg::PointCloud2>(
        "/livox/lidar_el", 1,
        std::bind(&recordNode::eltopic_callback, this, std::placeholders::_1),
        options_livox
    );

    subscription_er = this->create_subscription<sensor_msgs::msg::PointCloud2>(
        "/livox/lidar_er", 1,
        std::bind(&recordNode::ertopic_callback, this, std::placeholders::_1),
        options_livox
    );
    subscription_pl = this->create_subscription<sensor_msgs::msg::PointCloud2>(
        "/livox/lidar_pl", 1,
        std::bind(&recordNode::pltopic_callback, this, std::placeholders::_1),
        options_livox
    );    
    subscription_pr = this->create_subscription<sensor_msgs::msg::PointCloud2>(
        "/livox/lidar_pr", 1,
        std::bind(&recordNode::prtopic_callback, this, std::placeholders::_1),
        options_livox
    );
}

recordNode::~recordNode()
{
    recordSwitch = false;
    // rcp::shutdown();
}

void recordNode::eltopic_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
{
    if (recordTopic == RECORD_EL)
    {
        qDebug() << "record_el restopic: " << recordTopic;
        pcl::PointCloud<pcl::PointXYZI> cloud;
        pcl::fromROSMsg(*msg, cloud);
        
        Eigen::Matrix4f LeftToGroundMatrix = Eigen::Matrix4f::Identity(4,4);
        // for(int i=0;i<16;i++)
        // 	LeftToGroundMatrix.<<lidar_param_pl[i];
        LeftToGroundMatrix<<lidar_param_pl[0],lidar_param_pl[1],lidar_param_pl[2],lidar_param_pl[3],
            lidar_param_pl[4],lidar_param_pl[5],lidar_param_pl[6],lidar_param_pl[7],
            lidar_param_pl[8],lidar_param_pl[9],lidar_param_pl[10],lidar_param_pl[11],
            lidar_param_pl[12],lidar_param_pl[13],lidar_param_pl[14],lidar_param_pl[15];
        
        pcl::transformPointCloud(cloud, cloud, LeftToGroundMatrix);

        // if (cloud->empty())
        // {
        //     return;
        // }

        // if (mRecord_vector.size() < 10)
        // {
        //     mRecord_vector.push_back(cloud);
        // }
        // else
        // {
            std::unique_lock<std::mutex> lock(recordmtx);
        //     record_vector = mRecord_vector;
        //     mRecord_vector.clear();
        //     mRecord_vector.push_back(cloud);
        // }
        *record_cloud_el = cloud;
    }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    
}


void recordNode::ertopic_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
{
    if (recordTopic == RECORD_ER)
    {
        qDebug() << "record_er restopic: " << recordTopic;
        pcl::PointCloud<pcl::PointXYZI> cloud;
        pcl::fromROSMsg(*msg, cloud);
        
        Eigen::Matrix4f LeftToGroundMatrix = Eigen::Matrix4f::Identity(4,4);
        // for(int i=0;i<16;i++)
        // 	LeftToGroundMatrix.<<lidar_param_pl[i];
        LeftToGroundMatrix<<lidar_param_pl[0],lidar_param_pl[1],lidar_param_pl[2],lidar_param_pl[3],
            lidar_param_pl[4],lidar_param_pl[5],lidar_param_pl[6],lidar_param_pl[7],
            lidar_param_pl[8],lidar_param_pl[9],lidar_param_pl[10],lidar_param_pl[11],
            lidar_param_pl[12],lidar_param_pl[13],lidar_param_pl[14],lidar_param_pl[15];
        
        std::unique_lock<std::mutex> lock(recordmtx);
        pcl::transformPointCloud(cloud, cloud, LeftToGroundMatrix);
        *record_cloud_er = cloud;
    }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    
}


void recordNode::pltopic_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
{
    if (recordTopic == RECORD_PL)
    {
        qDebug() << "record_pl restopic: " << recordTopic;
        pcl::PointCloud<pcl::PointXYZI> cloud;
        pcl::fromROSMsg(*msg, cloud);
        
        Eigen::Matrix4f LeftToGroundMatrix = Eigen::Matrix4f::Identity(4,4);
        // for(int i=0;i<16;i++)
        // 	LeftToGroundMatrix.<<lidar_param_pl[i];
        LeftToGroundMatrix<<lidar_param_pl[0],lidar_param_pl[1],lidar_param_pl[2],lidar_param_pl[3],
            lidar_param_pl[4],lidar_param_pl[5],lidar_param_pl[6],lidar_param_pl[7],
            lidar_param_pl[8],lidar_param_pl[9],lidar_param_pl[10],lidar_param_pl[11],
            lidar_param_pl[12],lidar_param_pl[13],lidar_param_pl[14],lidar_param_pl[15];
        
        std::unique_lock<std::mutex> lock(recordmtx);
        pcl::transformPointCloud(cloud, cloud, LeftToGroundMatrix);
        *record_cloud_pl = cloud;
    }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    
}


void recordNode::prtopic_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
{
    if (recordTopic == RECORD_PR)
    {
        qDebug() << "pr restopic: " << recordTopic;
        pcl::PointCloud<pcl::PointXYZI> cloud;
        pcl::fromROSMsg(*msg, cloud);
        
        Eigen::Matrix4f LeftToGroundMatrix = Eigen::Matrix4f::Identity(4,4);
        // for(int i=0;i<16;i++)
        // 	LeftToGroundMatrix.<<lidar_param_pl[i];
        LeftToGroundMatrix<<lidar_param_pl[0],lidar_param_pl[1],lidar_param_pl[2],lidar_param_pl[3],
            lidar_param_pl[4],lidar_param_pl[5],lidar_param_pl[6],lidar_param_pl[7],
            lidar_param_pl[8],lidar_param_pl[9],lidar_param_pl[10],lidar_param_pl[11],
            lidar_param_pl[12],lidar_param_pl[13],lidar_param_pl[14],lidar_param_pl[15];
        
        // std::unique_lock<std::mutex> lock(recordmtx);
        pcl::transformPointCloud(cloud, cloud, LeftToGroundMatrix);
        *record_cloud_pr = cloud;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    
}


/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++(方便查找) */
lidarNode::lidarNode()
    : Node("lidarNode")  {
    
    callback_group_livox = this->create_callback_group(rclcpp::CallbackGroupType::Reentrant);
    callback_group_gty = this->create_callback_group(rclcpp::CallbackGroupType::Reentrant);

    // callback_group_livox_er = this->create_callback_group(rclcpp::CallbackGroupType::Reentrant);
    // callback_group_gty_er = this->create_callback_group(rclcpp::CallbackGroupType::Reentrant);

    // callback_group_livox_pl = this->create_callback_group(rclcpp::CallbackGroupType::Reentrant);
    // callback_group_gty_pl = this->create_callback_group(rclcpp::CallbackGroupType::Reentrant);

    // callback_group_livox_pr = this->create_callback_group(rclcpp::CallbackGroupType::Reentrant);
    // callback_group_gty_pr = this->create_callback_group(rclcpp::CallbackGroupType::Reentrant);

    rclcpp::SubscriptionOptions options_livox;
    options_livox.callback_group = callback_group_livox;

    rclcpp::SubscriptionOptions options_livox_gty;
    options_livox_gty.callback_group = callback_group_gty;
    // rclcpp::SubscriptionOptions options_livox_er;
    // options_livox_er.callback_group = callback_group_livox_er;

    // rclcpp::SubscriptionOptions options_livox_pl;
    // options_livox_pl.callback_group = callback_group_livox_pl;

    // rclcpp::SubscriptionOptions options_livox_pr;
    // options_livox_pr.callback_group = callback_group_livox_pr;

    // rclcpp::SubscriptionOptions options_gty_el;
    // options_gty_el.callback_group = callback_group_gty_el;

    // rclcpp::SubscriptionOptions options_gty_er;
    // options_gty_er.callback_group = callback_group_gty_er;

    // rclcpp::SubscriptionOptions options_gty_pl;
    // options_gty_pl.callback_group = callback_group_gty_pl;

    // rclcpp::SubscriptionOptions options_gty_pr;
    // options_gty_pr.callback_group = callback_group_gty_pr;

    subscription_el_131 = this->create_subscription<sensor_msgs::msg::PointCloud2>(
        "/livox/lidar_3GGDLCR00200131", 1,
        std::bind(&lidarNode::el_131_topic_callback, this, std::placeholders::_1),
        options_livox
    );
    subscription_el = this->create_subscription<visualization_msgs::msg::MarkerArray>(
        "/gty_obstacle_el", 1,
        std::bind(&lidarNode::eltopic_callback, this, std::placeholders::_1),
        options_livox
    ); 

    subscription_er_321 = this->create_subscription<sensor_msgs::msg::PointCloud2>(
        "/livox/lidar_3GGDLCR00200321", 1,
        std::bind(&lidarNode::er_321_topic_callback, this, std::placeholders::_1),
        options_livox
    );
    subscription_er = this->create_subscription<visualization_msgs::msg::MarkerArray>(
        "/gty_obstacle_er", 1,
        std::bind(&lidarNode::ertopic_callback, this, std::placeholders::_1),
        options_livox
    ); 

    subscription_pl_371 = this->create_subscription<sensor_msgs::msg::PointCloud2>(
        "/livox/lidar_3GGDLCR00200371", 1,
        std::bind(&lidarNode::pl_371_topic_callback, this, std::placeholders::_1),
        options_livox
    );
    subscription_pl = this->create_subscription<visualization_msgs::msg::MarkerArray>(
        "/gty_obstacle_pl", 1,
        std::bind(&lidarNode::pltopic_callback, this, std::placeholders::_1),
        options_livox
    ); 
    
    subscription_pr_171 = this->create_subscription<sensor_msgs::msg::PointCloud2>(
        "/livox/lidar_3GGDLCR00200171", 1,
        std::bind(&lidarNode::pr_171_topic_callback, this, std::placeholders::_1),
        options_livox
    );
    subscription_pr = this->create_subscription<visualization_msgs::msg::MarkerArray>(
        "/gty_obstacle_pr", 1,
        std::bind(&lidarNode::prtopic_callback, this, std::placeholders::_1),
        options_livox
    ); 
}

lidarNode::~lidarNode()
{
    // rcp::shutdown();
}

void lidarNode::livox_callback(const sensor_msgs::msg::PointCloud2::ConstSharedPtr &msg)
{
    // if (topic_name == "/livox/lidar_el")
    // {
        if (lidarTopic == LIDAR_EL)
        {
            pcl::PointCloud<pcl::PointXYZI> cloud;
            pcl::fromROSMsg(*msg, cloud);
            
            Eigen::Matrix4f LeftToGroundMatrix = Eigen::Matrix4f::Identity(4,4);
            // for(int i=0;i<16;i++)
            // 	LeftToGroundMatrix.<<lidar_param_pl[i];
            LeftToGroundMatrix<<lidar_param_pl[0],lidar_param_pl[1],lidar_param_pl[2],lidar_param_pl[3],
                lidar_param_pl[4],lidar_param_pl[5],lidar_param_pl[6],lidar_param_pl[7],
                lidar_param_pl[8],lidar_param_pl[9],lidar_param_pl[10],lidar_param_pl[11],
                lidar_param_pl[12],lidar_param_pl[13],lidar_param_pl[14],lidar_param_pl[15];
            std::unique_lock<std::mutex> lock(lidarmtx);
            pcl::transformPointCloud(cloud, cloud, LeftToGroundMatrix);
            *lidar_cloud = cloud;
        }    
    //     std::this_thread::sleep_for(std::chrono::milliseconds(300));
    // }
    // else if (topic_name == "/livox/lidar_er")
    // {
        if (lidarTopic == LIDAR_ER)
        {
            pcl::PointCloud<pcl::PointXYZI> cloud;
            pcl::fromROSMsg(*msg, cloud);
            
            Eigen::Matrix4f LeftToGroundMatrix = Eigen::Matrix4f::Identity(4,4);
            // for(int i=0;i<16;i++)
            // 	LeftToGroundMatrix.<<lidar_param_pl[i];
            LeftToGroundMatrix<<lidar_param_pl[0],lidar_param_pl[1],lidar_param_pl[2],lidar_param_pl[3],
                lidar_param_pl[4],lidar_param_pl[5],lidar_param_pl[6],lidar_param_pl[7],
                lidar_param_pl[8],lidar_param_pl[9],lidar_param_pl[10],lidar_param_pl[11],
                lidar_param_pl[12],lidar_param_pl[13],lidar_param_pl[14],lidar_param_pl[15];
            std::unique_lock<std::mutex> lock(lidarmtx);
            pcl::transformPointCloud(cloud, cloud, LeftToGroundMatrix);
            *lidar_cloud = cloud;
        }    
    //     std::this_thread::sleep_for(std::chrono::milliseconds(300));
    // }
    // else if (topic_name == "/livox/lidar_pl")
    // {
        if (lidarTopic == LIDAR_PL)
        {
            pcl::PointCloud<pcl::PointXYZI> cloud;
            pcl::fromROSMsg(*msg, cloud);
            
            Eigen::Matrix4f LeftToGroundMatrix = Eigen::Matrix4f::Identity(4,4);
            // for(int i=0;i<16;i++)
            // 	LeftToGroundMatrix.<<lidar_param_pl[i];
            LeftToGroundMatrix<<lidar_param_pl[0],lidar_param_pl[1],lidar_param_pl[2],lidar_param_pl[3],
                lidar_param_pl[4],lidar_param_pl[5],lidar_param_pl[6],lidar_param_pl[7],
                lidar_param_pl[8],lidar_param_pl[9],lidar_param_pl[10],lidar_param_pl[11],
                lidar_param_pl[12],lidar_param_pl[13],lidar_param_pl[14],lidar_param_pl[15];
            std::unique_lock<std::mutex> lock(lidarmtx);
            pcl::transformPointCloud(cloud, cloud, LeftToGroundMatrix);
            *lidar_cloud = cloud;
        }    
    //     std::this_thread::sleep_for(std::chrono::milliseconds(300));
    // }
    // else if (topic_name == "/livox/lidar_pr")
    // {
        if (lidarTopic == LIDAR_PR)
        {
            pcl::PointCloud<pcl::PointXYZI> cloud;
            pcl::fromROSMsg(*msg, cloud);
            
            Eigen::Matrix4f LeftToGroundMatrix = Eigen::Matrix4f::Identity(4,4);
            // for(int i=0;i<16;i++)
            // 	LeftToGroundMatrix.<<lidar_param_pl[i];
            LeftToGroundMatrix<<lidar_param_pl[0],lidar_param_pl[1],lidar_param_pl[2],lidar_param_pl[3],
                lidar_param_pl[4],lidar_param_pl[5],lidar_param_pl[6],lidar_param_pl[7],
                lidar_param_pl[8],lidar_param_pl[9],lidar_param_pl[10],lidar_param_pl[11],
                lidar_param_pl[12],lidar_param_pl[13],lidar_param_pl[14],lidar_param_pl[15];
            std::unique_lock<std::mutex> lock(lidarmtx);
            pcl::transformPointCloud(cloud, cloud, LeftToGroundMatrix);
            *lidar_cloud = cloud;
        }    
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
}

void lidarNode::gty_callback(const visualization_msgs::msg::MarkerArray::ConstSharedPtr &msg)
{
    // if (topic_name == "/gty_obstacle_el")
    // {
        if (lidarTopic == LIDAR_EL)
        {
                // 创建一个新的 MarkerArray 用于存储变换后的数据
                visualization_msgs::msg::MarkerArray transformed_msg = *msg;
                // 将变换后的数据赋值给 cloud_block
                std::unique_lock<std::mutex> lock(blockmtx);

                // qDebug() << "1111111111111111111";
                lidar_marker = transformed_msg;
                // cloud_block = msg;
        }
        // std::this_thread::sleep_for(std::chrono::milliseconds(300));
    // }
    // else if (topic_name == "/gty_obstacle_er")
    // {
        if (lidarTopic == LIDAR_ER)
        {
            // 创建一个新的 MarkerArray 用于存储变换后的数据
            visualization_msgs::msg::MarkerArray transformed_msg = *msg;
            // 将变换后的数据赋值给 cloud_block
            std::unique_lock<std::mutex> lock(blockmtx);

            // qDebug() << "1111111111111111111";
            lidar_marker = transformed_msg;
            // cloud_block = msg;
    }
    // std::this_thread::sleep_for(std::chrono::milliseconds(300));
    // }
    // else if (topic_name == "/gty_obstacle_pl")
    // {
        if (lidarTopic == LIDAR_PL)
        {
            // 创建一个新的 MarkerArray 用于存储变换后的数据
            visualization_msgs::msg::MarkerArray transformed_msg = *msg;
            // 将变换后的数据赋值给 cloud_block
            std::unique_lock<std::mutex> lock(blockmtx);

            lidar_marker = transformed_msg;
            // cloud_block = msg;
        }
        // std::this_thread::sleep_for(std::chrono::milliseconds(300));
    // }
    // else if (topic_name == "/gty_obstacle_pr")
    // {
        if (lidarTopic == LIDAR_PR)
        {
            // 创建一个新的 MarkerArray 用于存储变换后的数据
            visualization_msgs::msg::MarkerArray transformed_msg = *msg;
            // 对每个 marker 应用外参矩阵
            // 将变换后的数据赋值给 cloud_block
            std::unique_lock<std::mutex> lock(blockmtx);

            // qDebug() << "1111111111111111111";
            lidar_marker = transformed_msg;
            // cloud_block = msg;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    // }
}

void lidarNode::el_131_topic_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg) {
    if (lidarTopic == LIDAR_EL)
    {
        // RCLCPP_INFO(this->get_logger(), "My log message");
        pcl::PointCloud<pcl::PointXYZI> cloud;
        pcl::fromROSMsg(*msg, cloud);
        
        Eigen::Matrix4f LeftToGroundMatrix = Eigen::Matrix4f::Identity(4,4);
        // for(int i=0;i<16;i++)
        // 	LeftToGroundMatrix.<<lidar_param_pl[i];
        LeftToGroundMatrix<<lidar_param_pl[0],lidar_param_pl[1],lidar_param_pl[2],lidar_param_pl[3],
            lidar_param_pl[4],lidar_param_pl[5],lidar_param_pl[6],lidar_param_pl[7],
            lidar_param_pl[8],lidar_param_pl[9],lidar_param_pl[10],lidar_param_pl[11],
            lidar_param_pl[12],lidar_param_pl[13],lidar_param_pl[14],lidar_param_pl[15];
        std::unique_lock<std::mutex> lock(lidarmtx);
        pcl::transformPointCloud(cloud, cloud, LeftToGroundMatrix);
        *lidar_cloud = cloud;
    }    
    // std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

void lidarNode::er_321_topic_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg) {
    if (lidarTopic == LIDAR_ER)
    {
        pcl::PointCloud<pcl::PointXYZI> cloud;
        pcl::fromROSMsg(*msg, cloud);
        
        Eigen::Matrix4f LeftToGroundMatrix = Eigen::Matrix4f::Identity(4,4);
        // for(int i=0;i<16;i++)
        // 	LeftToGroundMatrix.<<lidar_param_pl[i];
        LeftToGroundMatrix<<lidar_param_pl[0],lidar_param_pl[1],lidar_param_pl[2],lidar_param_pl[3],
            lidar_param_pl[4],lidar_param_pl[5],lidar_param_pl[6],lidar_param_pl[7],
            lidar_param_pl[8],lidar_param_pl[9],lidar_param_pl[10],lidar_param_pl[11],
            lidar_param_pl[12],lidar_param_pl[13],lidar_param_pl[14],lidar_param_pl[15];
        std::unique_lock<std::mutex> lock(lidarmtx);
        pcl::transformPointCloud(cloud, cloud, LeftToGroundMatrix);
        *lidar_cloud = cloud;
    }    
    // std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

void lidarNode::pl_371_topic_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg) {
    if (lidarTopic == LIDAR_PL)
    {
        // qDebug() << "111";
        pcl::PointCloud<pcl::PointXYZI> cloud;
        pcl::fromROSMsg(*msg, cloud);
        
        Eigen::Matrix4f LeftToGroundMatrix = Eigen::Matrix4f::Identity(4,4);
        // for(int i=0;i<16;i++)
        // 	LeftToGroundMatrix.<<lidar_param_pl[i];
        LeftToGroundMatrix<<lidar_param_pl[0],lidar_param_pl[1],lidar_param_pl[2],lidar_param_pl[3],
            lidar_param_pl[4],lidar_param_pl[5],lidar_param_pl[6],lidar_param_pl[7],
            lidar_param_pl[8],lidar_param_pl[9],lidar_param_pl[10],lidar_param_pl[11],
            lidar_param_pl[12],lidar_param_pl[13],lidar_param_pl[14],lidar_param_pl[15];
        std::unique_lock<std::mutex> lock(lidarmtx);
        pcl::transformPointCloud(cloud, cloud, LeftToGroundMatrix);
        *lidar_cloud = cloud;
    }    
    // std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

void lidarNode::pr_171_topic_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg) {
    if (lidarTopic == LIDAR_PR)
    {
        pcl::PointCloud<pcl::PointXYZI> cloud;
        pcl::fromROSMsg(*msg, cloud);
        
        Eigen::Matrix4f LeftToGroundMatrix = Eigen::Matrix4f::Identity(4,4);
        // for(int i=0;i<16;i++)
        // 	LeftToGroundMatrix.<<lidar_param_pl[i];
        LeftToGroundMatrix<<lidar_param_pl[0],lidar_param_pl[1],lidar_param_pl[2],lidar_param_pl[3],
            lidar_param_pl[4],lidar_param_pl[5],lidar_param_pl[6],lidar_param_pl[7],
            lidar_param_pl[8],lidar_param_pl[9],lidar_param_pl[10],lidar_param_pl[11],
            lidar_param_pl[12],lidar_param_pl[13],lidar_param_pl[14],lidar_param_pl[15];
        std::unique_lock<std::mutex> lock(lidarmtx);
        pcl::transformPointCloud(cloud, cloud, LeftToGroundMatrix);
        *lidar_cloud = cloud;
    }    
    // std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

void lidarNode::eltopic_callback(const visualization_msgs::msg::MarkerArray::SharedPtr msg)
{
    if (lidarTopic == LIDAR_EL)
    {
        // 创建一个新的 MarkerArray 用于存储变换后的数据
        visualization_msgs::msg::MarkerArray transformed_msg = *msg;
        // 对每个 marker 应用外参矩阵
        // 将变换后的数据赋值给 cloud_block
        std::unique_lock<std::mutex> lock(blockmtx);

        // qDebug() << "1111111111111111111";
        lidar_marker = transformed_msg;
        // cloud_block = msg;
    }
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void lidarNode::ertopic_callback(const visualization_msgs::msg::MarkerArray::SharedPtr msg)
{
    if (lidarTopic == LIDAR_ER)
    {
        // 创建一个新的 MarkerArray 用于存储变换后的数据
        visualization_msgs::msg::MarkerArray transformed_msg = *msg;
        // 对每个 marker 应用外参矩阵
        // 将变换后的数据赋值给 cloud_block
        std::unique_lock<std::mutex> lock(blockmtx);

        // qDebug() << "1111111111111111111";
        lidar_marker = transformed_msg;
        // cloud_block = msg;
    }
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void lidarNode::pltopic_callback(const visualization_msgs::msg::MarkerArray::SharedPtr msg)
{
    if (lidarTopic == LIDAR_PL)
    {
        // 创建一个新的 MarkerArray 用于存储变换后的数据
        visualization_msgs::msg::MarkerArray transformed_msg = *msg;
        // 对每个 marker 应用外参矩阵
        // 将变换后的数据赋值给 cloud_block
        std::unique_lock<std::mutex> lock(blockmtx);

        // qDebug() << "1111111111111111111";
        lidar_marker = transformed_msg;
        // cloud_block = msg;
    }
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void lidarNode::prtopic_callback(const visualization_msgs::msg::MarkerArray::SharedPtr msg)
{
    if (lidarTopic == LIDAR_PR)
    {
        // 创建一个新的 MarkerArray 用于存储变换后的数据
        visualization_msgs::msg::MarkerArray transformed_msg = *msg;
        // 对每个 marker 应用外参矩阵
        // 将变换后的数据赋值给 cloud_block
        std::unique_lock<std::mutex> lock(blockmtx);

        // qDebug() << "1111111111111111111";
        lidar_marker = transformed_msg;
        // cloud_block = msg;
    }
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++(方便查找) */
cameraNode::cameraNode()
    : Node("CameraNode")  {
    callback_group_livox = this->create_callback_group(rclcpp::CallbackGroupType::Reentrant);
    rclcpp::SubscriptionOptions options_livox;
    options_livox.callback_group = callback_group_livox;
    // subscription_e_left = this->create_subscription<sensor_msgs::msg::Image>(
    //     "/camera_e_left/image_raw", 1,
    //     std::bind(&cameraNode::detections1, this, std::placeholders::_1),
    //     options_livox
    // ); 
    // subscription_2 = this->create_subscription<sensor_msgs::msg::Image>(
    //     "/camera_e_right/image_raw", 1,
    //     std::bind(&cameraNode::detections2, this, std::placeholders::_1),
    //     options_livox
    // ); 
    // subscription_3 = this->create_subscription<sensor_msgs::msg::Image>(
    //     "/camera_eroom_in/image_raw", 1,
    //     std::bind(&cameraNode::detections3, this, std::placeholders::_1),
    //     options_livox
    // ); 
    //     subscription_4 = this->create_subscription<sensor_msgs::msg::Image>(
    //     "/camera_eroom_out/image_raw", 1,
    //     std::bind(&cameraNode::detections4, this, std::placeholders::_1),
    //     options_livox
    // ); 
    //     subscription_5 = this->create_subscription<sensor_msgs::msg::Image>(
    //     "/camera_proom_out/image_raw", 1,
    //     std::bind(&cameraNode::detections5, this, std::placeholders::_1),
    //     options_livox
    // ); 

    image_e_left.subscribe(this, "/camera_e_left/image_raw", rclcpp::QoS(10).get_rmw_qos_profile(), options_livox);
    detection_camera_e_left.subscribe(this, "/yolo/detection_camera_e_left/image_raw", rclcpp::QoS(10).get_rmw_qos_profile(), options_livox);

    image_e_right.subscribe(this, "/camera_e_right/image_raw", rclcpp::QoS(10).get_rmw_qos_profile(), options_livox);
    detection_camera_e_right.subscribe(this, "/yolo/detection_camera_e_right/image_raw", rclcpp::QoS(10).get_rmw_qos_profile(), options_livox);

    image_eroom_in.subscribe(this, "/camera_eroom_in/image_raw", rclcpp::QoS(10).get_rmw_qos_profile(), options_livox);
    detection_camera_eroom_in.subscribe(this, "/yolo/detection_camera_eroom_in/image_raw", rclcpp::QoS(10).get_rmw_qos_profile(), options_livox);

    image_eroom_out.subscribe(this, "/camera_eroom_out/image_raw", rclcpp::QoS(10).get_rmw_qos_profile(), options_livox);
    detection_camera_eroom_out.subscribe(this, "/yolo/detection_camera_eroom_out/image_raw", rclcpp::QoS(10).get_rmw_qos_profile(), options_livox);

    image_proom_out.subscribe(this, "/camera_proom_out/image_raw", rclcpp::QoS(10).get_rmw_qos_profile(), options_livox);
    detection_camera_proom_out.subscribe(this, "/yolo/detection_camera_proom_out/image_raw", rclcpp::QoS(10).get_rmw_qos_profile(), options_livox);
    // 同步回调
    sync_e_left.reset(new message_filters::Synchronizer<MySyncPolicy>(MySyncPolicy(10), image_e_left, detection_camera_e_left));
    sync_e_left->registerCallback(std::bind(&cameraNode::detections_e_left, this, std::placeholders::_1, std::placeholders::_2));

    sync_e_right.reset(new message_filters::Synchronizer<MySyncPolicy>(MySyncPolicy(10), image_e_right, detection_camera_e_right));
    sync_e_right->registerCallback(std::bind(&cameraNode::detections_e_right, this, std::placeholders::_1, std::placeholders::_2));

    sync_eroom_in.reset(new message_filters::Synchronizer<MySyncPolicy>(MySyncPolicy(10), image_eroom_in, detection_camera_eroom_in));
    sync_eroom_in->registerCallback(std::bind(&cameraNode::detections_eroom_in, this, std::placeholders::_1, std::placeholders::_2));

    sync_eroom_out.reset(new message_filters::Synchronizer<MySyncPolicy>(MySyncPolicy(10), image_eroom_out, detection_camera_eroom_out));
    sync_eroom_out->registerCallback(std::bind(&cameraNode::detections_eroom_out, this, std::placeholders::_1, std::placeholders::_2));

    sync_proom_out.reset(new message_filters::Synchronizer<MySyncPolicy>(MySyncPolicy(10), image_proom_out, detection_camera_proom_out));
    sync_proom_out->registerCallback(std::bind(&cameraNode::detections_proom_out, this, std::placeholders::_1, std::placeholders::_2));

    // 启动回调线程
    // thread_e_left = std::thread(&cameraNode::spinThread, this, sync_e_left);
    // thread_e_right = std::thread(&cameraNode::spinThread, this, sync_e_right);
    // thread_eroom_in = std::thread(&cameraNode::spinThread, this, sync_eroom_in);
    // thread_eroom_out = std::thread(&cameraNode::spinThread, this, sync_eroom_out);
    // thread_proom_out = std::thread(&cameraNode::spinThread, this, sync_proom_out);
}

cameraNode::~cameraNode()
{
    // 确保在析构时停止线程
    // if (thread_e_left.joinable()) {
    //     thread_e_left.join();
    // }
    // if (thread_e_right.joinable()) {
    //     thread_e_right.join();
    // }    // rcp::shutdown();
    // // 确保在析构时停止线程
    // if (thread_eroom_in.joinable()) {
    //     thread_eroom_in.join();
    // }
    // if (thread_eroom_out.joinable()) {
    //     thread_eroom_out.join();
    // }
    // // 确保在析构时停止线程
    // if (thread_proom_out.joinable()) {
    //     thread_proom_out.join();
    // }
}

cv::Scalar cameraNode::random_color()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);
    return cv::Scalar(dis(gen), dis(gen), dis(gen));
}

// 绘制边框
cv::Mat cameraNode::draw_box(cv::Mat& cv_image, const yolov8_msgs::msg::Detection& detection, const cv::Scalar& color)
{
    // test
    // std::string filename = "output_image.jpg";
    // bool isSuccess = cv::imwrite(filename, cv_image);
    // return cv_image;

    std::string label = detection.class_name;
    float score = detection.score;
    auto box_msg = detection.bbox;
    auto track_id = detection.id;


    //过滤识别低的
    if (score <= 0.75)
        return cv_image;

    // 计算矩形顶点
    cv::Point min_pt(cvRound(box_msg.center.position.x - box_msg.size.x / 2.0),
                    cvRound(box_msg.center.position.y - box_msg.size.y / 2.0));
    cv::Point max_pt(cvRound(box_msg.center.position.x + box_msg.size.x / 2.0),
                    cvRound(box_msg.center.position.y + box_msg.size.y / 2.0));

    // 四个顶点
    std::vector<cv::Point> rect_pts = {
        min_pt,
        cv::Point(max_pt.x, min_pt.y),
        max_pt,
        cv::Point(min_pt.x, max_pt.y)
    };

    std::cout << "before" << rect_pts << std::endl;
    // 旋转矩阵
    cv::Mat rotation_matrix = cv::getRotationMatrix2D(cv::Point2f(box_msg.center.position.x, box_msg.center.position.y),
                                                        -cv::fastAtan2(sin(box_msg.center.theta), cos(box_msg.center.theta)),
                                                        1.0);

    // 旋转矩形顶点
    cv::transform(rect_pts, rect_pts, rotation_matrix);

    // 绘制旋转后的矩形
    for (size_t i = 0; i < 4; ++i)
    {
        cv::line(cv_image, rect_pts[i], rect_pts[(i + 1) % 4], color, 2);
    }
    std::cout << "after" << rect_pts << std::endl;
    // 绘制标签
    label = label + " (" + track_id + ") (" + std::to_string(score) + ")";
    cv::putText(cv_image, label, min_pt + cv::Point(5, 25), cv::FONT_HERSHEY_SIMPLEX, 1.0, color, 1, cv::LINE_AA);

    return cv_image;
}

cv::Mat cameraNode::draw_mask(cv::Mat& cv_image, const yolov8_msgs::msg::Detection& detection, const cv::Scalar& color)
{
    auto mask_msg = detection.mask;

    // 如果mask中有数据
    if (!mask_msg.data.empty()) {
        // 将mask数据转换为cv::Point类型
        std::vector<cv::Point> mask_array;
        for (const auto& ele : mask_msg.data) {
            mask_array.emplace_back(cv::Point(cvRound(ele.x), cvRound(ele.y)));
        }

        // 创建图层副本
        cv::Mat layer = cv_image.clone();

        // 填充多边形
        cv::fillPoly(layer, std::vector<std::vector<cv::Point>>{mask_array}, color);

        // 将图层与原图像加权合成
        cv::addWeighted(cv_image, 0.4, layer, 0.6, 0, cv_image);

        // 绘制多边形边界
        cv::polylines(cv_image, mask_array, true, color, 2, cv::LINE_AA);
    }

    return cv_image;
}

// 回调函数
void cameraNode::detections_e_left(const sensor_msgs::msg::Image::ConstSharedPtr img_msg, const yolov8_msgs::msg::DetectionArray::ConstSharedPtr detection_msg)
{
    if (cameraTopic == CAMERA_EL)
    // qDebug() << "detection cb";
    {
        cv::Mat cv_image = cv_bridge::toCvShare(img_msg, "bgr8")->image;

        for (const auto& detection : detection_msg->detections)
        {
            std::string label = detection.class_name;

            if (_class_to_color.find(label) == _class_to_color.end())
            {
                _class_to_color[label] = random_color();
            }

            cv_image = draw_box(cv_image, detection, _class_to_color[label]);
            cv_image = draw_mask(cv_image, detection, _class_to_color[label]);
                        // 显示图像
        }

        std::unique_lock<std::mutex> lock(cameramtx);
        // qDebug() << "1";


        QImage img;
        img = cvMatToQImage(cv_image);
        camera_image = img.copy();
    }
    // else
    // {
    //     std::this_thread::sleep_for(std::chrono::milliseconds(300));
    // }
}

void cameraNode::detections1(const sensor_msgs::msg::Image::SharedPtr img_msg)
{
    if (cameraTopic == CAMERA_EL)
    {
        cv::Mat cv_image = cv_bridge::toCvShare(img_msg, "bgr8")->image;
        std::unique_lock<std::mutex> lock(cameramtx);
        QImage img;
        img = cvMatToQImage(cv_image);
        camera_image = img.copy();
    } 
}
void cameraNode::detections2(const sensor_msgs::msg::Image::SharedPtr img_msg)
{
    if (cameraTopic == CAMERA_ER)
    {
        cv::Mat cv_image = cv_bridge::toCvShare(img_msg, "bgr8")->image;
        std::unique_lock<std::mutex> lock(cameramtx);
        QImage img;
        img = cvMatToQImage(cv_image);
        camera_image = img.copy();
    }
}
void cameraNode::detections3(const sensor_msgs::msg::Image::SharedPtr img_msg)
{
    if (cameraTopic == CAMERA_EI)
    {
        cv::Mat cv_image = cv_bridge::toCvShare(img_msg, "bgr8")->image;
        std::unique_lock<std::mutex> lock(cameramtx);
        QImage img;
        img = cvMatToQImage(cv_image);
        camera_image = img.copy();
    }
    else
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }    
}
void cameraNode::detections4(const sensor_msgs::msg::Image::SharedPtr img_msg)
{
    if (cameraTopic == CAMERA_EO)
    {
        cv::Mat cv_image = cv_bridge::toCvShare(img_msg, "bgr8")->image;
        std::unique_lock<std::mutex> lock(cameramtx);
        QImage img;
        img = cvMatToQImage(cv_image);
        camera_image = img.copy();
    }
}
void cameraNode::detections5(const sensor_msgs::msg::Image::SharedPtr img_msg)
{
    if (cameraTopic == CAMERA_PO)
    {
        cv::Mat cv_image = cv_bridge::toCvShare(img_msg, "bgr8")->image;
        std::unique_lock<std::mutex> lock(cameramtx);
        QImage img;
        img = cvMatToQImage(cv_image);
        camera_image = img.copy();
    }  
}

void cameraNode::detections_e_right(const sensor_msgs::msg::Image::ConstSharedPtr img_msg, const yolov8_msgs::msg::DetectionArray::ConstSharedPtr detection_msg)
{
    // qDebug() << "detection cb";
    if (cameraTopic == CAMERA_ER)
    {
        cv::Mat cv_image = cv_bridge::toCvShare(img_msg, "bgr8")->image;

        for (const auto& detection : detection_msg->detections)
        {
            std::string label = detection.class_name;

            if (_class_to_color.find(label) == _class_to_color.end())
            {
                _class_to_color[label] = random_color();
            }

            cv_image = draw_box(cv_image, detection, _class_to_color[label]);
            cv_image = draw_mask(cv_image, detection, _class_to_color[label]);
        }

        std::unique_lock<std::mutex> lock(cameramtx);
        // qDebug() << "1";


        QImage img;
        img = cvMatToQImage(cv_image);
        camera_image = img.copy();
    }
    // else
    // {
    //     std::this_thread::sleep_for(std::chrono::milliseconds(300));
    // }
}

void cameraNode::detections_eroom_in(const sensor_msgs::msg::Image::ConstSharedPtr img_msg, const yolov8_msgs::msg::DetectionArray::ConstSharedPtr detection_msg)
{
    if (cameraTopic == CAMERA_EI)
    {
    // qDebug() << "callback ein";
        cv::Mat cv_image = cv_bridge::toCvShare(img_msg, "bgr8")->image;

        for (const auto& detection : detection_msg->detections)
        {
            std::string label = detection.class_name;

            if (_class_to_color.find(label) == _class_to_color.end())
            {
                _class_to_color[label] = random_color();
            }

            cv_image = draw_box(cv_image, detection, _class_to_color[label]);
            cv_image = draw_mask(cv_image, detection, _class_to_color[label]);
        }

        std::unique_lock<std::mutex> lock(cameramtx);
        // qDebug() << "1";


        QImage img;
        img = cvMatToQImage(cv_image);
        camera_image = img.copy();
    }
    // else
    // {
    //     std::this_thread::sleep_for(std::chrono::milliseconds(300));
    // }
}

void cameraNode::detections_eroom_out(const sensor_msgs::msg::Image::ConstSharedPtr img_msg, const yolov8_msgs::msg::DetectionArray::ConstSharedPtr detection_msg)
{
    // qDebug() << "detection cb";
    if (cameraTopic == CAMERA_EO)
    {
        cv::Mat cv_image = cv_bridge::toCvShare(img_msg, "bgr8")->image;

        for (const auto& detection : detection_msg->detections)
        {
            std::string label = detection.class_name;

            if (_class_to_color.find(label) == _class_to_color.end())
            {
                _class_to_color[label] = random_color();
            }

            cv_image = draw_box(cv_image, detection, _class_to_color[label]);
            cv_image = draw_mask(cv_image, detection, _class_to_color[label]);
        }

        std::unique_lock<std::mutex> lock(cameramtx);
        // qDebug() << "1";


        QImage img;
        img = cvMatToQImage(cv_image);
        camera_image = img.copy();
    }
    // else
    // {
    //     std::this_thread::sleep_for(std::chrono::milliseconds(300));
    // }
}

void cameraNode::detections_proom_out(const sensor_msgs::msg::Image::ConstSharedPtr img_msg, const yolov8_msgs::msg::DetectionArray::ConstSharedPtr detection_msg)
{   

    // qDebug() << "detection cb";
    if (cameraTopic == CAMERA_PO)
    {
        cv::Mat cv_image = cv_bridge::toCvShare(img_msg, "bgr8")->image;

        for (const auto& detection : detection_msg->detections)
        {
            std::string label = detection.class_name;

            if (_class_to_color.find(label) == _class_to_color.end())
            {
                _class_to_color[label] = random_color();
            }

            cv_image = draw_box(cv_image, detection, _class_to_color[label]);
            cv_image = draw_mask(cv_image, detection, _class_to_color[label]);
        }

        std::unique_lock<std::mutex> lock(cameramtx);
        // qDebug() << "1";


        QImage img;
        img = cvMatToQImage(cv_image);
        camera_image = img.copy();
    }
    // else
    // {
    //     std::this_thread::sleep_for(std::chrono::milliseconds(300));
    // }
}

QImage cameraNode::cvMatToQImage(const cv::Mat &mat)
{
    QImage image;
    switch(mat.type())
    {
        // std::cout << "图片大小: " << mat.cols << " x " << mat.rows << std::endl;
        case CV_8UC1:
            // QImage构造：数据，宽度，高度，每行多少字节，存储结构
            image = QImage((const unsigned char*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
            break;
        case CV_8UC3:
            image = QImage((const unsigned char*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
            image = image.rgbSwapped(); // BRG转为RGB
            // Qt5.14增加了Format_BGR888
            // image = QImage((const unsigned char*)mat.data, mat.cols, mat.rows, mat.cols * 3, QImage::Format_BGR888);
            break;
        case CV_8UC4:
            image = QImage((const unsigned char*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
            break;
        case CV_16UC4:
            image = QImage((const unsigned char*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGBA64);
            image = image.rgbSwapped(); // BRG转为RGB
            break;
    }
    // qDebug() << "图片大小:" << image.width() << "x" << image.height();
    return image;
}

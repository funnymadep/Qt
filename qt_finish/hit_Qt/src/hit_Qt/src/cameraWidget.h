#ifndef CAMERA_WIDGET_H
#define CAMERA_WIDGET_H

#include "resizableitem.h"


#include <QLabel>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsVideoItem>
#include <QMediaPlayer>
#include <QLineEdit>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <iostream>
#include <thread>

class cameraWidget : public QWidget
{
      Q_OBJECT

public:
    cameraWidget(QWidget *parent = nullptr);
    void initRosPublish();
    ~cameraWidget();

private slots:
   void saveConfiguration();
   void addRedRect();
   void deleteSelectedRect();
   void videoPlay();
   void videoStop();

private:
    QLabel *cameraSignalLabel;
    QLabel *obstacleLabel;
    QGraphicsView *mView;
    QGraphicsScene *mScene;
    QGraphicsPixmapItem *pixmapItem;
    ResizableRectItem *selectedRect;
    QGraphicsVideoItem *mVideoItem;
    QMediaPlayer *mMediaPlayer;
    QLineEdit *mRtspLineEdit;

    std::shared_ptr<rclcpp::Node> ros_node_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr json_publisher_;
    std::thread ros_spin_thread_;
    std::atomic<bool> stop_spin_;
private:
};


#endif
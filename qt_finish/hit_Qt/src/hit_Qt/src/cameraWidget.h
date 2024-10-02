#ifndef CAMERA_WIDGET_H
#define CAMERA_WIDGET_H

// #include "resizableitem.h"
#include "PolygonItem.h"
#include "rosRunnable.h"
#include "rosNode.h"
#include "global.h"

#include <QLabel>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsVideoItem>
#include <QMediaPlayer>
#include <QLineEdit>
// #include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <iostream>
#include <thread>
#include <QVector>
#include <QGraphicsPixmapItem>

class cameraWidget : public QWidget
{
      Q_OBJECT

public:
    cameraWidget(QWidget *parent = nullptr);
    void initRosPublish();
    ~cameraWidget();

signals:
   void emitCameraMsg();

public slots:
   void readConfiguration();

private slots:
   void saveConfiguration();
   void addRedRect();
   void deleteSelectedRect();
   void videoPlay();
   void videoStop();
   void handleCameraImage();

private:
    QLabel *cameraSignalLabel;
    QLabel *obstacleLabel;
    QGraphicsView *mView;
    QGraphicsScene *mScene;
    // QGraphicsPixmapItem *pixmapItem;
    // ResizableRectItem *selectedRect;
    QGraphicsVideoItem *mVideoItem;
    QMediaPlayer *mMediaPlayer;
    // QLineEdit *mRtspLineEdit;

    std::shared_ptr<rclcpp::Node> ros_node_;
    cameraRunnable *mCameraThread = nullptr;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr json_publisher_;
    std::thread ros_spin_thread_;
    std::thread camera_thread_;
    std::atomic<bool> stop_spin_;
    QVector<PolygonItem*> polygons;
    PolygonItem* lastClickedPolygon;
    QGraphicsPixmapItem *pixmapItem;

private:
};


#endif
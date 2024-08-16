#ifndef LIDAR_WIDGET_H
#define LIDAR_WIDGET_H 

#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QTcpSocket>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <QVTKOpenGLNativeWidget.h>
#include <vtkGenericOpenGLRenderWindow.h>

#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/visualization/pcl_visualizer.h>

#include "point_cloud_subscriber.h"

using PointCloud = pcl::PointCloud<pcl::PointXYZ>;




class Server : public QTcpServer {
    Q_OBJECT

public:
    Server() {
        if (!this->listen(QHostAddress::Any, 2222)) {
            qCritical() << "Unable to start the server: " << this->errorString();
        } else {
            qDebug() << "Server started...";
        }
    }

signals:
    void cloudReceived(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);

protected:
    void incomingConnection(qintptr socketDescriptor) override {
        QTcpSocket* socket = new QTcpSocket(this);
        socket->setSocketDescriptor(socketDescriptor);
        connect(socket, &QTcpSocket::readyRead, this, [this, socket]() {
            QByteArray data = socket->readAll();
            std::stringstream compressedData(data.toStdString());
            pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
            pcl::io::OctreePointCloudCompression<pcl::PointXYZ> octreeDecompression;
            octreeDecompression.decodePointCloud(compressedData, cloud);
            emit cloudReceived(cloud);
        });
        connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    }
};



class lidarWidget : public QWidget
{
    Q_OBJECT

public:
    lidarWidget(QWidget *parent = nullptr);
    ~lidarWidget();

    void createStatus(QVBoxLayout *vLeft);
    void createCloudPoint(QVBoxLayout *vLeft);
    void createSetting(QHBoxLayout *hlayout);
    void initializeViewer();

private slots:
    void handlePointCloudReceived(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);
    void combChange(const QString &context);
    void addCube();
    void delCube();
    // void connectToServer();
    
private:
    QLabel *mLabelStatus = nullptr;
    QLabel *mLabelIsHide = nullptr;
    QLabel *mLabelIsBlock = nullptr;
    QLabel *mLabelBlockLen = nullptr;
    QLabel *mLabelAntiCollisionMode = nullptr;
    QComboBox *comb = nullptr;
    QComboBox *colorType = nullptr;
    QLineEdit *lateralDistanceEdit = nullptr;
    QLineEdit *longitudinalDistanceEdit = nullptr;
    QTimer *timer;
    Server *server;
    QVTKOpenGLNativeWidget *vtkWidget;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow;
    pcl::visualization::PCLVisualizer::Ptr viewer;
};




#endif // CLIENT_H



#ifndef POINTCLOUDWIDGET_H
#define POINTCLOUDWIDGET_H

#include <QWidget>
#include <QVTKOpenGLNativeWidget.h>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/visualization/pcl_visualizer.h>

class pointCloudWidget : public QWidget
{
    Q_OBJECT

public:
    explicit pointCloudWidget(QWidget *parent = nullptr);
    ~pointCloudWidget();

private slots:
    void handlePointCloudReceived(const pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud);

signals:
    void pointCloudReceived(const pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud);

private:
    void initializeViewer();
    void receivePointCloud();

    QVTKOpenGLNativeWidget *vtkWidget;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow;
    pcl::visualization::PCLVisualizer::Ptr viewer;
};

#endif // POINTCLOUDWIDGET_H

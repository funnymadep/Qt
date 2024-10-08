#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "cameraWidget.h"
#include "lidarWidget.h"
#include "sysLogWidegt.h"
#include "sysSettingWidget.h"
#include "recordWidget.h"
#include "recordCamera.h"

#include <QVBoxLayout>
#include <QTreeWidget>
#include <QStackedWidget>
#include <QWidget>
#include <iostream>
#include <memory>

class mainWidget : public QWidget
{
    Q_OBJECT

public:
    mainWidget(QWidget *parent = nullptr);
    ~mainWidget();

    void init();
    void createLogo();
    void createMenu(QHBoxLayout *h);
    void createMainPage(QHBoxLayout *h);

private slots:
    void handleItemClicked(QTreeWidgetItem *current, QTreeWidgetItem *previous);
signals:
    void emitCameraSignal();

private:
    QVBoxLayout *mlayout = nullptr;
    QTreeWidget *mTreeWidget = nullptr;
    QStackedWidget *mStackedWgt = nullptr;

    lidarWidget *lidar = nullptr;
    cameraWidget *camera = nullptr;
    sysLogWidget *syslog = nullptr;
    sysSettingWidget *sysSetting = nullptr;
    recordWidget *recordCloud = nullptr;
    recordCameraWidget *recordCamera = nullptr;
    
};
#endif // WIDGET_H

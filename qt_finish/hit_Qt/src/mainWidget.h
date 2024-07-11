#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "cameraWidget.h"
#include "lidarWidget.h"
#include "sysLogWidegt.h"
#include "sysSettingWidget.h"
#include "global.h"


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
    void handleItemClicked(QTreeWidgetItem *item);

private:
    QVBoxLayout *mlayout = nullptr;
    QTreeWidget *mTreeWidget = nullptr;
    QStackedWidget *mStackedWgt = nullptr;

    lidarWidget *lidar = nullptr;
    cameraWidget *camera = nullptr;
};
#endif // WIDGET_H

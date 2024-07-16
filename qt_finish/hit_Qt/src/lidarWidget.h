#ifndef LIDAR_WIDGET_H
#define LIDAR_WIDGET_H 

#include "global.h"
#include "pointCloudWidget.h"

class lidarWidget : public QWidget
{
    Q_OBJECT

public:
    lidarWidget(QWidget *parent = nullptr);
    ~lidarWidget();

    void createStatus(QVBoxLayout *vLeft);
    void createCloudPoint(QVBoxLayout *vLeft);
    void createSetting(QHBoxLayout *hlayout);
private slots:
   

private:
    QLabel *mLabelStatus = nullptr;
    QLabel *mLabelIsHide = nullptr;
    QLabel *mLabelIsBlock = nullptr;
    QLabel *mLabelBlockLen = nullptr;
    QLabel *mLabelAntiCollisionMode = nullptr;
    QComboBox *comb = nullptr;
    QLineEdit *lateralDistanceEdit = nullptr;
    QLineEdit *LongitudinalDistanceEdit = nullptr;
};

#endif
#ifndef CAMERA_WIDGET_H
#define CAMERA_WIDGET_H

#include "global.h"
#include "resizableitem.h"

class cameraWidget : public QWidget
{
      Q_OBJECT

public:
    cameraWidget(QWidget *parent = nullptr);
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
};


#endif
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
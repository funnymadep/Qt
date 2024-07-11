#ifndef CAMERA_WIDGET_H
#define CAMERA_WIDGET_H

#include "global.h"

class DraggableRectItem : public QGraphicsRectItem
{
public:
    DraggableRectItem(QGraphicsItem *parent = nullptr) : QGraphicsRectItem(parent) {
        setFlag(QGraphicsItem::ItemIsMovable);
        setFlag(QGraphicsItem::ItemIsSelectable);
        setFlag(QGraphicsItem::ItemSendsGeometryChanges);
        setFlag(QGraphicsItem::ItemIsFocusable);
    }
};

class cameraWidget : public QWidget
{
      Q_OBJECT

public:
    cameraWidget(QWidget *parent = nullptr);
    ~cameraWidget();

private slots:
   void saveConfiguration();

private:
    QLabel *cameraSignalLabel;
    QLabel *obstacleLabel;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *pixmapItem;
    DraggableRectItem *draggableRect;

};


#endif
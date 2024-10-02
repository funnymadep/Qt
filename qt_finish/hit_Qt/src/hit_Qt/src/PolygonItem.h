#ifndef POLYGONITEM_H
#define POLYGONITEM_H

#include <QGraphicsPolygonItem>
#include <QGraphicsSceneMouseEvent>

class PolygonItem : public QGraphicsPolygonItem {
public:
    PolygonItem(QPolygonF polygon);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    int movingIndex;
    bool isMovingPolygon;
};

#endif // POLYGONITEM_H

#include "PolygonItem.h"
#include <QPen>

PolygonItem::PolygonItem(QPolygonF polygon) 
    : QGraphicsPolygonItem(polygon), movingIndex(-1), isMovingPolygon(false) {
    // 设置线条的颜色为红色，宽度为2
    QPen pen(Qt::red);
    pen.setWidth(2);
    setPen(pen);
    // setFlag(QGraphicsItem::ItemIsMovable); // 允许整个多边形移动
    // setFlag(QGraphicsItem::ItemSendsGeometryChanges); // 让几何变化触发事件
}

void PolygonItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QPointF pos = event->pos();
    movingIndex = -1;
    for (int i = 0; i < polygon().size(); ++i) {
        if (QLineF(pos, polygon().at(i)).length() < 10) {
            movingIndex = i;
            break;
        }
    }

    if (movingIndex == -1) {
        isMovingPolygon = true;
    } else {
        isMovingPolygon = false;
    }

    QGraphicsPolygonItem::mousePressEvent(event);
}

void PolygonItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (movingIndex >= 0) {
        QPolygonF poly = polygon();
        poly[movingIndex] = event->pos();
        setPolygon(poly);
    } else if (isMovingPolygon) {
        QGraphicsPolygonItem::mouseMoveEvent(event);
    }
}

void PolygonItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    movingIndex = -1;
    isMovingPolygon = false;
    QGraphicsPolygonItem::mouseReleaseEvent(event);
}
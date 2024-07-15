#ifndef RESIZABLEITEM_H
#define RESIZABLEITEM_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class ResizableRectItem : public QGraphicsRectItem {
public:
    ResizableRectItem(const QRectF &rect);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    enum ResizeHandle { NoHandle, LeftHandle, RightHandle, TopHandle, BottomHandle, TopLeftHandle, TopRightHandle, BottomLeftHandle, BottomRightHandle };
    ResizeHandle currentHandle;
    QRectF initialRect;
    QPointF initialMousePos;
    void updateCursorShape(const QPointF &pos);
    ResizeHandle getResizeHandle(const QPointF &pos);
};

#endif // RESIZABLEITEM_H

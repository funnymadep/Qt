#include "resizableitem.h"
#include <QCursor>
#include <QGraphicsScene>
#include <QGraphicsView>

ResizableRectItem::ResizableRectItem(const QRectF &rect) : QGraphicsRectItem(rect), currentHandle(NoHandle) {}

void ResizableRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    currentHandle = getResizeHandle(event->pos());
    initialRect = rect();
    initialMousePos = event->pos();
    QGraphicsRectItem::mousePressEvent(event);
}

void ResizableRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (currentHandle != NoHandle) {
        QPointF delta = event->pos() - initialMousePos;
        QRectF newRect = initialRect;

        switch (currentHandle) {
            case LeftHandle:
                newRect.setLeft(newRect.left() + delta.x());
                break;
            case RightHandle:
                newRect.setRight(newRect.right() + delta.x());
                break;
            case TopHandle:
                newRect.setTop(newRect.top() + delta.y());
                break;
            case BottomHandle:
                newRect.setBottom(newRect.bottom() + delta.y());
                break;
            case TopLeftHandle:
                newRect.setTopLeft(newRect.topLeft() + delta);
                break;
            case TopRightHandle:
                newRect.setTopRight(newRect.topRight() + delta);
                break;
            case BottomLeftHandle:
                newRect.setBottomLeft(newRect.bottomLeft() + delta);
                break;
            case BottomRightHandle:
                newRect.setBottomRight(newRect.bottomRight() + delta);
                break;
            default:
                break;
        }
        setRect(newRect);
    } else {
        QGraphicsRectItem::mouseMoveEvent(event);
    }
}

void ResizableRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    currentHandle = NoHandle;
    QGraphicsRectItem::mouseReleaseEvent(event);
}

void ResizableRectItem::updateCursorShape(const QPointF &pos) {
    switch (getResizeHandle(pos)) {
        case LeftHandle:
        case RightHandle:
            setCursor(Qt::SizeHorCursor);
            break;
        case TopHandle:
        case BottomHandle:
            setCursor(Qt::SizeVerCursor);
            break;
        case TopLeftHandle:
        case BottomRightHandle:
            setCursor(Qt::SizeFDiagCursor);
            break;
        case TopRightHandle:
        case BottomLeftHandle:
            setCursor(Qt::SizeBDiagCursor);
            break;
        default:
            setCursor(Qt::ArrowCursor);
            break;
    }
}

ResizableRectItem::ResizeHandle ResizableRectItem::getResizeHandle(const QPointF &pos) {
    const qreal handleSize = 10.0;
    QRectF leftHandle(rect().left() - handleSize, rect().top() + handleSize, handleSize, rect().height() - 2 * handleSize);
    QRectF rightHandle(rect().right(), rect().top() + handleSize, handleSize, rect().height() - 2 * handleSize);
    QRectF topHandle(rect().left() + handleSize, rect().top() - handleSize, rect().width() - 2 * handleSize, handleSize);
    QRectF bottomHandle(rect().left() + handleSize, rect().bottom(), rect().width() - 2 * handleSize, handleSize);

    QRectF topLeftHandle(rect().topLeft() - QPointF(handleSize, handleSize), QSizeF(handleSize, handleSize));
    QRectF topRightHandle(rect().topRight() - QPointF(0, handleSize), QSizeF(handleSize, handleSize));
    QRectF bottomLeftHandle(rect().bottomLeft() - QPointF(handleSize, 0), QSizeF(handleSize, handleSize));
    QRectF bottomRightHandle(rect().bottomRight(), QSizeF(handleSize, handleSize));

    if (leftHandle.contains(pos)) return LeftHandle;
    if (rightHandle.contains(pos)) return RightHandle;
    if (topHandle.contains(pos)) return TopHandle;
    if (bottomHandle.contains(pos)) return BottomHandle;
    if (topLeftHandle.contains(pos)) return TopLeftHandle;
    if (topRightHandle.contains(pos)) return TopRightHandle;
    if (bottomLeftHandle.contains(pos)) return BottomLeftHandle;
    if (bottomRightHandle.contains(pos)) return BottomRightHandle;

    return NoHandle;
}

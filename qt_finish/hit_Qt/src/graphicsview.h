#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include "global.h"

class GraphicsView : public QGraphicsView {
    Q_OBJECT

public:
    GraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr) : QGraphicsView(scene, parent), addMode(false) {}

    void setAddMode(bool mode) {
        addMode = mode;
    }

signals:
    void imageClicked(const QPointF &point);

protected:
    void mousePressEvent(QMouseEvent *event) override {
        if (addMode) {
            QPointF scenePos = mapToScene(event->pos());
            emit imageClicked(scenePos);
        } else {
            QGraphicsView::mousePressEvent(event);
        }
    }

private:
    bool addMode;
};

#endif
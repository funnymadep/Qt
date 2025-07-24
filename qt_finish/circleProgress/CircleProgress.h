#ifndef CIRCLEPROGRESSBAR_H
#define CIRCLEPROGRESSBAR_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <cmath>

class CircleProgressBar : public QWidget
{
    Q_OBJECT
public:
    explicit CircleProgressBar(QWidget *parent = nullptr);

    // 设置和获取进度值
    void setProgress(int value);
    void setColor(QColor color);
    int getProgress() const { return progress; }

signals:
    // 进度改变信号
    void progressChanged(int value);

protected:
    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *) override;

private:
    // 计算鼠标位置对应的进度值
    int calculateProgressFromMousePos(const QPointF &pos);

    // 绘制圆环
    void drawRing(QPainter &painter, const QRectF &rect, qreal ringWidth,
                  const QColor &bgColor, const QColor &progressColor);

    // 绘制指针
    void drawPointer(QPainter &painter, const QPointF &center, qreal radius, qreal ringWidth);

    // 绘制中心文本
    void drawCenterText(QPainter &painter, const QRectF &rect);

    int progress;            // 当前进度 (0-100)
    bool dragging;           // 是否正在拖动
    QSizeF lastSize;         // 上次窗口大小
    qreal ringWidth;         // 圆环宽度
    qreal outerRadius;       // 外半径
    QPointF centerPoint;     // 中心点
    QRectF ringRect;         // 圆环区域
    QColor m_color;
};

#endif // CIRCLEPROGRESSBAR_H

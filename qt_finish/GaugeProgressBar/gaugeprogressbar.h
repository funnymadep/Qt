#ifndef GAUGEPROGRESSBAR_H
#define GAUGEPROGRESSBAR_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <cmath>

class GaugeProgressBar : public QWidget
{
    Q_OBJECT
public:
    explicit GaugeProgressBar(QWidget *parent = nullptr);

    // 设置和获取进度值
    void setProgress(int value);
    int getProgress() const { return progress; };
    void setColor(QColor newColor);

signals:
    // 进度改变信号
    void progressChanged(int value);

protected:
    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void leaveEvent(QEvent *event) override;

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

    void drawPointer(QPainter &painter);

    void updateCurrentDimensions();

    int progress;            // 当前进度 (0-100)
    bool dragging;           // 是否正在拖动
    QSizeF lastSize;         // 上次窗口大小
    qreal ringWidth;         // 圆环宽度
    qreal outerRadius;       // 外半径
    QPointF centerPoint;     // 中心点
    QRectF ringRect;         // 圆环区域
    qreal pointerRadius;
    qreal innerRadius;
    QColor color;
    bool mouseOver;     // 标记鼠标是否在控件上
    double scaleFactor; // 当前缩放因子
    double baseOuterRadius; // 原始外半径（未缩放）
    double baseRingWidth;   // 原始圆环宽度（未缩放）
    double basePointerRadius; // 原始指针半径（未缩放）
};



#endif // GAUGEPROGRESSBAR_H

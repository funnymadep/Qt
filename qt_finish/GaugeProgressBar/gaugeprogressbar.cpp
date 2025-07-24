// gaugeprogressbar.cpp
#include "gaugeprogressbar.h"
#include <QDebug>
#include <cmath>

GaugeProgressBar::GaugeProgressBar(QWidget *parent)
    : QWidget(parent), progress(0), dragging(false), ringWidth(0),
    color(QColor(255, 105, 225)), scaleFactor(0.5)
{
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
}

void GaugeProgressBar::setProgress(int value)
{
    // 确保进度在0-100范围内
    int newProgress = qBound(0, value, 100);

    if (newProgress != progress) {
        progress = newProgress;
        update(); // 触发重绘
    }
}

void GaugeProgressBar::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    // 计算圆环参数
    qreal side = qMin(width(), height()) * 0.8; // 留出20%边距
    outerRadius = side / 2.0;
    baseRingWidth = outerRadius * 0.3; // 原始圆环宽度为半径的30%
    basePointerRadius = baseRingWidth * 0.4; // 原始指针小圆的半径
    innerRadius = outerRadius - baseRingWidth;

    // 计算当前尺寸
    updateCurrentDimensions();

    // 计算中心点和圆环区域
    centerPoint = QPointF(width() / 2.0, height() / 2.0);
    ringRect = QRectF(centerPoint.x() - outerRadius, centerPoint.y() - outerRadius,
                      outerRadius * 2, outerRadius * 2);
}

void GaugeProgressBar::updateCurrentDimensions()
{
    // 只缩放圆环宽度和小球大小
    ringWidth = baseRingWidth * scaleFactor;
    pointerRadius = basePointerRadius * scaleFactor;
}

void GaugeProgressBar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制背景
    painter.fillRect(rect(), palette().window());

    QColor innerColor(QColor(220, 220, 220));
    painter.setBrush(innerColor);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(centerPoint, innerRadius, innerRadius);

    // 绘制圆环
    drawRing(painter, ringRect, ringWidth,
             QColor(105, 105, 105), // 背景色
             color); // 进度色

    // 绘制指针小圆
    drawPointer(painter);
}

void GaugeProgressBar::drawRing(QPainter &painter, const QRectF &rect, qreal ringWidth,
                                const QColor &bgColor, const QColor &progressColor)
{
    // 绘制背景圆环
    QPen pen(bgColor);
    pen.setWidthF(ringWidth);
    pen.setCapStyle(Qt::FlatCap);
    painter.setPen(pen);
    painter.drawEllipse(rect);

    // 绘制进度圆弧
    if (progress > 0) {
        // 计算进度角度（从270度底部开始顺时针）
        int angle = progress * 360 / 100;

        // 设置进度颜色
        pen.setColor(progressColor);
        painter.setPen(pen);

        // 绘制圆弧（270度开始，顺时针绘制）
        painter.drawArc(rect, 270 * 16, -angle * 16);
    }
}

void GaugeProgressBar::drawPointer(QPainter &painter)
{
    // 计算指针小圆的位置（在圆环宽度的中间）
    qreal trackRadius = outerRadius - ringWidth;

    // 计算角度：0%在底部（270度），顺时针增加
    qreal angleDeg = 270 - progress * 3.6;
    qreal angleRad = -angleDeg * M_PI / 180.0;

    // 计算小圆中心坐标
    QPointF pointerCenter(
        centerPoint.x() + trackRadius * cos(angleRad),
        centerPoint.y() + trackRadius * sin(angleRad)
        );

    // 绘制小圆
    painter.setPen(Qt::NoPen);
    painter.setBrush(color);
    painter.drawEllipse(pointerCenter, pointerRadius, pointerRadius);
}

int GaugeProgressBar::calculateProgressFromMousePos(const QPointF &pos)
{
    // 计算鼠标相对于圆心的角度
    qreal dx = pos.x() - centerPoint.x();
    qreal dy = pos.y() - centerPoint.y();

    // 计算角度（弧度）
    qreal angle = atan2(dy, dx);

    // 转换为角度值（0-360度），0度在右侧（3点钟方向）
    qreal degrees = angle * 180.0 / M_PI;

    // 转换为从270度底部开始的进度（0-100）
    degrees = fmod(degrees + 90, 360); // 旋转90度使0点在顶部
    degrees = fmod(degrees + 180, 360); // 旋转180度使0点在底部

    // 计算进度（0-100）
    int newProgress = qRound(degrees / 3.6);

    // 确保在0-100范围内
    return qBound(0, newProgress, 100);
}

void GaugeProgressBar::mouseMoveEvent(QMouseEvent *event)
{
    // 计算鼠标到圆心的距离
    QPointF mousePos = event->pos();
    qreal distance = QLineF(centerPoint, mousePos).length();

    // 定义缩放过渡区域
    const qreal minDistance = outerRadius * 1.2;  // 开始放大的距离
    const qreal maxDistance = outerRadius * 1.4;  // 完全放大的距离

    // 计算动态缩放因子
    if (distance < minDistance) {
        // 在圆环内部或接近圆环，完全放大
        scaleFactor = 1.0;
    } else if (distance <= maxDistance) {
        // 在过渡区域，线性插值
        scaleFactor = 1.0 - (distance - minDistance) / (maxDistance - minDistance) * 0.5;
    } else {
        // 在外部区域，缩小一半
        scaleFactor = 0.5;
    }

    // 更新当前尺寸
    updateCurrentDimensions();
    update(); // 重绘

    // 处理拖动逻辑
    if (dragging) {
        setProgress(calculateProgressFromMousePos(mousePos));
    }

    QWidget::mouseMoveEvent(event);
}

void GaugeProgressBar::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QPointF mousePos = event->pos();
        qreal distance = QLineF(centerPoint, mousePos).length();

        // 计算圆环的内外边界（使用当前尺寸）
        qreal innerRadius = outerRadius - ringWidth * 2;

        // 简化逻辑：只要点击在圆环轨道范围内（内径到外径之间），就启动拖动
        if (distance >= innerRadius && distance <= outerRadius + ringWidth / 2) {
            dragging = true;
            setProgress(calculateProgressFromMousePos(mousePos));
        }
    }

    QWidget::mousePressEvent(event);
}

void GaugeProgressBar::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragging = false;
    }

    QWidget::mouseReleaseEvent(event);
}

void GaugeProgressBar::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    // 鼠标离开时缩小一半
    scaleFactor = 0.5;
    updateCurrentDimensions();
    update();
}

void GaugeProgressBar::setColor(QColor newColor)
{
    color = newColor;
}

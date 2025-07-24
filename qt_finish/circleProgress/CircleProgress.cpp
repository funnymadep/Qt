#include "circleprogress.h"
#include <QDebug>

CircleProgressBar::CircleProgressBar(QWidget *parent)
    : QWidget(parent), progress(0), dragging(false), ringWidth(0)
{
    m_color = QColor(65,65,65);
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
}

void CircleProgressBar::setProgress(int value)
{
    // 确保进度在0-100范围内
    int newProgress = qBound(0, value, 100);

    if (newProgress != progress) {
        progress = newProgress;
        update(); // 触发重绘
        emit progressChanged(progress); // 发送进度改变信号
    }
}

void CircleProgressBar::setColor(QColor color)
{
    m_color = color;
}

void CircleProgressBar::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    // 计算圆环参数
    qreal side = qMin(width(), height()) * 0.8; // 留出20%边距
    outerRadius = side / 2.0;
    ringWidth = outerRadius * 0.3; // 圆环宽度为半径的30%

    // 计算中心点和圆环区域
    centerPoint = QPointF(width() / 2.0, height() / 2.0);
    ringRect = QRectF(centerPoint.x() - outerRadius, centerPoint.y() - outerRadius,
                      outerRadius * 2, outerRadius * 2);

    lastSize = QSizeF(width(), height());
}

void CircleProgressBar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制背景
    painter.fillRect(rect(), palette().window());

    // 绘制圆环

    drawRing(painter, ringRect, ringWidth,
             QColor(220, 220, 220), // 背景色
             m_color); // 进度色

    // 绘制指针
    // drawPointer(painter, centerPoint, outerRadius, ringWidth);

    // 绘制中心文本
    drawCenterText(painter, ringRect);
}

void CircleProgressBar::drawRing(QPainter &painter, const QRectF &rect, qreal ringWidth,
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

void CircleProgressBar::drawPointer(QPainter &painter, const QPointF &center, qreal radius, qreal ringWidth)
{
    // 计算指针角度（从270度底部开始，顺时针）
    qreal angle = -(270 - progress * 3.6) * M_PI / 180.0;

    // 指针长度（从圆心到圆环中间位置）
    qreal pointerLength = radius - ringWidth;

    // 计算指针末端坐标
    qreal endX = center.x() + pointerLength * cos(angle);
    qreal endY = center.y() + pointerLength * sin(angle);

    // 绘制指针
    QPen pointerPen(Qt::red, 3);
    pointerPen.setCapStyle(Qt::RoundCap);
    painter.setPen(pointerPen);
    painter.drawLine(center, QPointF(endX, endY));

    // 绘制指针末端圆点
    painter.setBrush(Qt::red);
    painter.drawEllipse(QPointF(endX, endY), 5, 5);

    // 绘制中心圆点
    painter.drawEllipse(center, 6, 6);
}

void CircleProgressBar::drawCenterText(QPainter &painter, const QRectF &rect)
{
    painter.setPen(Qt::black);
    QFont font = painter.font();
    font.setPointSizeF(rect.width() * 0.1); // 根据圆环大小设置字体
    painter.setFont(font);
    painter.drawText(rect, Qt::AlignCenter, QString("%1%").arg(progress));
}

int CircleProgressBar::calculateProgressFromMousePos(const QPointF &pos)
{
    // 计算鼠标相对于圆心的角度
    qreal dx = pos.x() - centerPoint.x();
    qreal dy = pos.y() - centerPoint.y();

    // 计算角度（弧度）
    qreal angle = atan2(dy, dx);

    // 转换为角度值（0-360度），0度在右侧（3点钟方向）
    qreal degrees = angle * 180.0 / M_PI;

    // 转换为从270度底部开始的进度（0-100）
    // 270度对应0%，270+360=630度对应100%
    degrees = fmod(degrees + 90, 360); // 旋转90度使0点在顶部

    // 现在：0度=顶部，90度=右侧，180度=底部，270度=左侧
    // 我们希望0%在底部（180度），顺时针增加
    degrees = fmod(degrees + 180, 360); // 旋转180度使0点在底部

    // 计算进度（0-100）
    int newProgress = qRound(degrees / 3.6);

    // 确保在0-100范围内
    return qBound(0, newProgress, 100);
}

void CircleProgressBar::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // 检查是否在圆环区域内
        QPointF mousePos = event->pos();
        qreal distance = QLineF(centerPoint, mousePos).length();

        // 判断是否在圆环范围内（内径到外径之间）
        qreal innerRadius = outerRadius - ringWidth;
        if (distance >= innerRadius && distance <= outerRadius + ringWidth) {
            dragging = true;
            setProgress(calculateProgressFromMousePos(mousePos));
        }
    }

    QWidget::mousePressEvent(event);
}

void CircleProgressBar::mouseMoveEvent(QMouseEvent *event)
{
    if (dragging) {
        setProgress(calculateProgressFromMousePos(event->pos()));
    }

    QWidget::mouseMoveEvent(event);
}

void CircleProgressBar::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragging = false;
    }

    QWidget::mouseReleaseEvent(event);
}

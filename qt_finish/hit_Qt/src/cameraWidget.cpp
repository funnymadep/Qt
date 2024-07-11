#include "cameraWidget.h"

cameraWidget::cameraWidget(QWidget *parent)
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // 状态显示部分
    QWidget *statusWidget = new QWidget(centralWidget);
    QHBoxLayout *statusLayout = new QHBoxLayout(statusWidget);

    cameraSignalLabel = new QLabel("相机信号状态: 正常", statusWidget);
    obstacleLabel = new QLabel("是否存在障碍物: 否", statusWidget);

    statusLayout->addWidget(cameraSignalLabel);
    statusLayout->addWidget(obstacleLabel);

    mainLayout->addWidget(statusWidget);

    // 图像及防撞区域部分
    QGraphicsView *graphicsView = new QGraphicsView(centralWidget);
    scene = new QGraphicsScene(this);
    graphicsView->setScene(scene);
    graphicsView->setFixedHeight(400);

    // 加载图像
    QImageReader reader("./image/3.jpg");  // 示例图片路径
    QImage image = reader.read();
    if (image.isNull()) {
        QMessageBox::critical(this, "错误", "无法加载图像");
    } else {
        pixmapItem = new QGraphicsPixmapItem(QPixmap::fromImage(image));
        scene->addItem(pixmapItem);
    }

    // 添加可拖拽的矩形框
    draggableRect = new DraggableRectItem();
    draggableRect->setRect(100, 100, 200, 200);
    draggableRect->setPen(QPen(Qt::red));
    scene->addItem(draggableRect);

    mainLayout->addWidget(graphicsView);

    // 保存按钮
    QPushButton *saveButton = new QPushButton("保存", centralWidget);
    connect(saveButton, &QPushButton::clicked, this, &cameraWidget::saveConfiguration);

    mainLayout->addWidget(saveButton);

    setWindowTitle("状态显示和防撞区域配置");
    resize(600, 500);
}
cameraWidget::~cameraWidget()
{

}

void cameraWidget::saveConfiguration() {
    QRectF rect = draggableRect->rect();
    QPointF position = draggableRect->pos();

    QString config = QString("防撞区域配置:\n位置: (%1, %2)\n大小: (%3 x %4)")
        .arg(position.x()).arg(position.y()).arg(rect.width()).arg(rect.height());

    QMessageBox::information(this, "配置已保存", config);
}
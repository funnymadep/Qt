#include "cameraWidget.h"

cameraWidget::cameraWidget(QWidget *parent) : QWidget(parent), selectedRect(nullptr)
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

    mView = new QGraphicsView(centralWidget);
    mScene = new QGraphicsScene(this);
    mView->setScene(mScene);
    mView->setMinimumSize(500, 500);


    mVideoItem = new QGraphicsVideoItem();
    mScene->addItem(mVideoItem);
    mView->show();

    mMediaPlayer = new QMediaPlayer(this);
    mMediaPlayer->setVideoOutput(mVideoItem);
    

    mainLayout->addWidget(mView);

    {
        QHBoxLayout *h = new QHBoxLayout();
        mainLayout->addLayout(h);

        QPushButton *addRect = new QPushButton(tr("添加红框"));
        h->addWidget(addRect);
        connect(addRect, &QPushButton::clicked, this, &cameraWidget::addRedRect);

        QPushButton *delRect = new QPushButton(tr("删除红框"));
        h->addWidget(delRect);
        connect(delRect, &QPushButton::clicked, this, &cameraWidget::deleteSelectedRect);
    }
    {
        QHBoxLayout *h = new QHBoxLayout();
        mainLayout->addLayout(h);

        QLabel *label = new QLabel(tr("rtsp地址"));
        h->addWidget(label);

        mRtspLineEdit = new QLineEdit(this);
        h->addWidget(mRtspLineEdit);
        h->addStretch();
    }
    {
        QHBoxLayout *h = new QHBoxLayout();
        mainLayout->addLayout(h);

        QPushButton *videoPlay = new QPushButton(tr("播放"));
        h->addWidget(videoPlay);
        connect(videoPlay, &QPushButton::clicked, this, &cameraWidget::videoPlay);

        QPushButton *videoStop = new QPushButton(tr("停止"));
        h->addWidget(videoStop);
        connect(videoStop, &QPushButton::clicked, this, &cameraWidget::videoStop);
    }


    // 保存按钮
    QPushButton *saveButton = new QPushButton("保存", centralWidget);
    connect(saveButton, &QPushButton::clicked, this, &cameraWidget::saveConfiguration);

    mainLayout->addWidget(saveButton);

    // test camera
    // QString rtspUrl = "rtsp://admin:sd123456@192.168.1.89:554/h264/ch1/main/av_stream";
    // mMediaPlayer->setMedia(QUrl(rtspUrl));
    // mMediaPlayer->play();


    mView->setRenderHint(QPainter::Antialiasing);

    setWindowTitle("状态显示和防撞区域配置");
}

void cameraWidget::addRedRect()
{
    QRectF rect(0, 0, 100, 100);
    ResizableRectItem *rectItem = new ResizableRectItem(rect);
    QPen pen;
    pen.setWidth(5);
    pen.setColor(QColor("red"));
    rectItem->setPen(pen);

    rectItem->setFlag(QGraphicsItem::ItemIsMovable);
    rectItem->setFlag(QGraphicsItem::ItemIsSelectable);
    rectItem->setFlag(QGraphicsItem::ItemIsFocusable);
    mScene->addItem(rectItem);
}

void cameraWidget::deleteSelectedRect()
{
    QList<QGraphicsItem *> selectedItems = mScene->selectedItems();
        if (selectedItems.size() == 1) {
            selectedRect = dynamic_cast<ResizableRectItem *>(selectedItems.first());
        } else {
            selectedRect = nullptr;
        }
        mScene->removeItem(selectedRect);
        delete selectedRect;
        selectedRect = nullptr;
}


void cameraWidget::saveConfiguration() {
    QString filePath = QFileDialog::getSaveFileName(this, "保存图片", "", "Images (*.png *.xpm *.jpg)");
    if (!filePath.isEmpty()) {
        QImage image(mView->viewport()->size(), QImage::Format_ARGB32);
        QPainter painter(&image);
        mView->render(&painter);
        image.save(filePath);
    }
}

void cameraWidget::videoPlay()
{
    QString rtspUrl = mRtspLineEdit->text();
    if (rtspUrl.isEmpty())
    {
        QMessageBox::warning(this, tr("rtsp源"), tr("rtsp源为空"));
        return;
    }
    mMediaPlayer->setMedia(QUrl(rtspUrl));
    mMediaPlayer->play();
}

void cameraWidget::videoStop()
{
    mMediaPlayer->stop();
}

cameraWidget::~cameraWidget()
{

}
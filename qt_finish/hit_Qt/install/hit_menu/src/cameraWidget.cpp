#include "cameraWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QUuid>
#include <QPushButton>
#include <QPen>


cameraWidget::cameraWidget(QWidget *parent) : QWidget(parent), selectedRect(nullptr), stop_spin_(false)
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
    mView->setMinimumSize(500, 450);


    mVideoItem = new QGraphicsVideoItem();
    mVideoItem->setSize(QSizeF(500, 450));
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
    initRosPublish();
}

void cameraWidget::initRosPublish()
{
    stop_spin_ = true;

    // 初始化发布者
    ros_node_ = rclcpp::Node::make_shared("json_publisher_node");
    json_publisher_ = ros_node_->create_publisher<std_msgs::msg::String>("json_topic", 10);
    // 启动ROS 2 spin线程
    ros_spin_thread_ = std::thread([this]() {
        while (rclcpp::ok() && !stop_spin_) {
            rclcpp::spin_some(ros_node_);
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 避免高CPU占用
        }
    });
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
    // QString filePath = QFileDialog::getSaveFileName(this, "选择保存文件", "", "YAML Files (*.yaml)");
    // if (filePath.isEmpty()) {
    //     return;
    // }
    QString filePath = QString(tr("/home/sd-robot/hql_test/hit_Qt/src/hit_Qt/camera.yaml"));
    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "无法打开文件";
        return;
    }

    // 读取当前文件内容
    QString yamlContent = file.readAll();
    QTextStream stream(&file);
    // file.resize(0); // 清空文件内容

    // 开始构建 JSON 对象
    QJsonArray areasArray;
    for (QGraphicsItem* item : mScene->items()) {
        ResizableRectItem* rectItem = dynamic_cast<ResizableRectItem*>(item);
        if (rectItem) {
            QRectF rect = rectItem->boundingRect();
            QPointF topLeft = rectItem->mapToScene(rect.topLeft());
            QPointF topRight = rectItem->mapToScene(rect.topRight());
            QPointF bottomLeft = rectItem->mapToScene(rect.bottomLeft());
            QPointF bottomRight = rectItem->mapToScene(rect.bottomRight());

            QJsonObject jsonObject;
            jsonObject["id"] = QUuid::createUuid().toString(QUuid::WithoutBraces);
            jsonObject["x1"] = topLeft.x();
            jsonObject["y1"] = topLeft.y();
            jsonObject["x2"] = topRight.x();
            jsonObject["y2"] = topRight.y();
            jsonObject["x3"] = bottomRight.x();
            jsonObject["y3"] = bottomRight.y();
            jsonObject["x4"] = bottomLeft.x();
            jsonObject["y4"] = bottomLeft.y();

            areasArray.append(jsonObject);
        }
    }

    // 将 JSON 数据转换为字符串
    QJsonDocument jsonDoc(areasArray);
    QString jsonString = jsonDoc.toJson(QJsonDocument::Indented);

    // 将 JSON 数据追加到 YAML 文件中
    if (!yamlContent.contains("areas:")) {
        stream << "areas:\n";
    }
    QJsonArray newAreasArray = QJsonDocument::fromJson(jsonString.toUtf8()).array();
    for (const QJsonValue& value : newAreasArray) {
        QJsonObject jsonObj = value.toObject();
        stream << "  - id: \"" << jsonObj["id"].toString() << "\"\n";
        stream << "    x1: " << jsonObj["x1"].toDouble() << "\n";
        stream << "    y1: " << jsonObj["y1"].toDouble() << "\n";
        stream << "    x2: " << jsonObj["x2"].toDouble() << "\n";
        stream << "    y2: " << jsonObj["y2"].toDouble() << "\n";
        stream << "    x3: " << jsonObj["x3"].toDouble() << "\n";
        stream << "    y3: " << jsonObj["y3"].toDouble() << "\n";
        stream << "    x4: " << jsonObj["x4"].toDouble() << "\n";
        stream << "    y4: " << jsonObj["y4"].toDouble() << "\n";
    }

    //发布ros
    auto message = std_msgs::msg::String();
    message.data = jsonString.toStdString();
    json_publisher_->publish(message);
    
    file.close();
}

void cameraWidget::videoPlay()
{
    // QString rtspUrl = mRtspLineEdit->text();
    QString rtspUrl = "rtsp://admin:sd123456@192.168.1.108:554/cam/realmonitor?channel=1&subtype=0";
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
    stop_spin_ = true;
    if (ros_spin_thread_.joinable()) {
        ros_spin_thread_.join();
    }
}
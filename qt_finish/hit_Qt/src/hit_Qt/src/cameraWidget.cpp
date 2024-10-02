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
#include <QImage>
#include <QVector>
#include <QPixmap>

cameraWidget::cameraWidget(QWidget *parent) : QWidget(parent),  stop_spin_(false)
{
    QWidget *centralWidget = new QWidget(this);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    {
        QHBoxLayout *h = new QHBoxLayout();
        mainLayout->addLayout(h);
        cameraSignalLabel = new QLabel("相机信号状态: 正常", this);
        h->addWidget(cameraSignalLabel);
        obstacleLabel = new QLabel("是否存在障碍物: 否", this);
        h->addWidget(obstacleLabel);
    }

    {
        QHBoxLayout *h = new QHBoxLayout();
        mainLayout->addLayout(h);

        QPushButton *addRect = new QPushButton(tr("添加区域"));
        h->addWidget(addRect);
        connect(addRect, &QPushButton::clicked, this, &cameraWidget::addRedRect);

        QPushButton *delRect = new QPushButton(tr("删除区域"));
        h->addWidget(delRect);
        connect(delRect, &QPushButton::clicked, this, &cameraWidget::deleteSelectedRect);

        QPushButton *saveButton = new QPushButton("保存区域", centralWidget);
        h->addWidget(saveButton);
        connect(saveButton, &QPushButton::clicked, this, &cameraWidget::saveConfiguration);
    }

    mView = new QGraphicsView(centralWidget);
    mScene = new QGraphicsScene(this);
    mView->setScene(mScene);

    mScene->setSceneRect(0, 0, 640, 480);
    
    mView->setFixedSize(640, 480);
    mView->setFrameShape(QFrame::NoFrame);  // 移除 QGraphicsView 的边框
    mView->setAlignment(Qt::AlignLeft | Qt::AlignTop); // 将对齐方式设为左上角
    // resize(900, 900);


    // mVideoItem = new QGraphicsVideoItem();
    // mVideoItem->setSize(QSizeF(500, 450));
    // mScene->addItem(mVideoItem);

    pixmapItem = new QGraphicsPixmapItem();
    mScene->addItem(pixmapItem);
    mView->show();

    // mMediaPlayer = new QMediaPlayer(this);
    // mMediaPlayer->setVideoOutput(mVideoItem);
    
    mainLayout->addWidget(mView);

    // {
    //     QHBoxLayout *h = new QHBoxLayout();
    //     mainLayout->addLayout(h);

    //     QLabel *label = new QLabel(tr("rtsp地址"));
    //     h->addWidget(label);

    //     mRtspLineEdit = new QLineEdit(this);
    //     h->addWidget(mRtspLineEdit);
    //     h->addStretch();
    // }
    {
        // QHBoxLayout *h = new QHBoxLayout();
        // v_lay->addLayout(h);

        // QPushButton *videoPlay = new QPushButton(tr("开始播放"));
        // h->addWidget(videoPlay);
        // connect(videoPlay, &QPushButton::clicked, this, &cameraWidget::videoPlay);
        // videoPlay->hide();

        cameraSwitch = true;
        camera_thread_ = std::thread([this]() {
            auto node = std::make_shared<cameraNode>();
            rclcpp::executors::MultiThreadedExecutor executor;
            executor.add_node(node);
            // cv::namedWindow("显示窗口", cv::WINDOW_AUTOSIZE);
            while(rclcpp::ok() && cameraSwitch)
            {
                // qDebug() << "1";
                emit emitCameraMsg();
                // qDebug() << "2";
                // qDebug() << "camera_runnable";
                // rclcpp::spin_some(node);
                // executor.spin_once();
                executor.spin_once(std::chrono::milliseconds(100));
                // qDebug() << "3";
            
            // std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 避免高CPU占用   
            }
        });

        connect(this, &cameraWidget::emitCameraMsg, this, &cameraWidget::handleCameraImage);
        

        // mCameraThread = new cameraRunnable();
        // mCameraThread->start();

        // QPushButton *videoStop = new QPushButton(tr("停止播放"));
        // h->addWidget(videoStop);
        // connect(videoStop, &QPushButton::clicked, this, &cameraWidget::videoStop);
    }


    {
        // QHBoxLayout *h = new QHBoxLayout();
        // v_lay->addLayout(h);
        // // 保存按钮
        // QPushButton *saveButton = new QPushButton("保存区域", centralWidget);
        // connect(saveButton, &QPushButton::clicked, this, &cameraWidget::saveConfiguration);
        // h->addWidget(saveButton);

        // QPushButton *readButton = new QPushButton("加载区域", centralWidget);
        // connect(readButton, &QPushButton::clicked, this, &cameraWidget::readConfiguration);
        // h->addWidget(readButton);
    }

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
    // stop_spin_ = true;

    // 初始化发布者
    ros_node_ = rclcpp::Node::make_shared("json_publisher_node");
    // connect();
    json_publisher_ = ros_node_->create_publisher<std_msgs::msg::String>("json_topic", 10);
    // 启动ROS 2 spin线程
    ros_spin_thread_ = std::thread([this]() {
        while (rclcpp::ok() && !stop_spin_) {
            rclcpp::spin_some(ros_node_);
            std::this_thread::sleep_for(std::chrono::milliseconds(300)); // 避免高CPU占用
        }
    });
}

void cameraWidget::addRedRect()
{
    QList<QGraphicsItem *> selectedItems = mScene->selectedItems();
    if (selectedItems.size() == 1) {
        QMessageBox::warning(this, tr("添加区域"), tr("最多只能有一个!"));
        return;
    }
    // QRectF rect(0, 0, 100, 100);
    // ResizableRectItem *rectItem = new ResizableRectItem(rect);
    // QPen pen;
    // pen.setWidth(5);
    // pen.setColor(QColor("red"));
    // rectItem->setPen(pen);

    // rectItem->setFlag(QGraphicsItem::ItemIsMovable);
    // rectItem->setFlag(QGraphicsItem::ItemIsSelectable);
    // rectItem->setFlag(QGraphicsItem::ItemIsFocusable);
    // mScene->addItem(rectItem);

    QPolygonF polygon;
    polygon << QPointF(0, 0) << QPointF(100, 0) << QPointF(100, 100) << QPointF(0, 100);
    PolygonItem *item = new PolygonItem(polygon);
    item->setFlag(QGraphicsItem::ItemIsMovable);
    item->setFlag(QGraphicsItem::ItemIsSelectable);
    item->setFlag(QGraphicsItem::ItemIsFocusable);
    mScene->addItem(item);
    polygons.append(item);

}

void cameraWidget::deleteSelectedRect()
{
    QList<QGraphicsItem *> selectedItems = mScene->selectedItems();
    if (selectedItems.size() == 1) {
        PolygonItem *selectedPolygon = dynamic_cast<PolygonItem *>(selectedItems.first());
        if (selectedPolygon) {
            mScene->removeItem(selectedPolygon);
            polygons.removeOne(selectedPolygon);
            delete selectedPolygon;
        }
    }
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
    file.resize(0); // 清空文件内容

    QStringList lines = yamlContent.split("\n");
    // 开始构建 JSON 对象
    QJsonArray areasArray;
    double scale = 1.0;
            
    for (QGraphicsItem* item : mScene->items()) {
         PolygonItem* polygonItem = dynamic_cast<PolygonItem*>(item);
        if (polygonItem) {
            // QRectF rect = rectItem->boundingRect();
            // QPointF topLeft = rectItem->mapToScene(rect.topLeft());
            // QPointF topRight = rectItem->mapToScene(rect.topRight());
            // QPointF bottomLeft = rectItem->mapToScene(rect.bottomLeft());
            // QPointF bottomRight = rectItem->mapToScene(rect.bottomRight());
            QPolygonF polygon = polygonItem->polygon();
            QJsonObject jsonObject;

            QString Jsonid;
            switch (cameraTopic)
            {
                case CAMERA_EL:
                    Jsonid = "img_el";
                    scale = 1.0;
                    break;
                case CAMERA_ER:
                    Jsonid = "img_er";
                    scale = 1.0;
                    break;
                case CAMERA_EI:
                    Jsonid = "img_e_in";
                    scale = 0.5;
                    break;
                case CAMERA_EO:
                    Jsonid = "img_e_out";
                    scale = 0.5;
                    break;
                case CAMERA_PO:
                    Jsonid = "img_p_out";
                    scale = 0.5;
                    break;          
                default:
                    break;
            }
            jsonObject["id"] = Jsonid;
            // jsonObject["x1"] = topLeft.x();
            // jsonObject["y1"] = topLeft.y();
            // jsonObject["x2"] = topRight.x();
            // jsonObject["y2"] = topRight.y();
            // jsonObject["x3"] = bottomRight.x();
            // jsonObject["y3"] = bottomRight.y();
            // jsonObject["x4"] = bottomLeft.x();
            // jsonObject["y4"] = bottomLeft.y();

            // QPointF scene_pos = polygonItem->scenePos();
            
            // QPolygonF polygon = polygonItem->polygon();
            // QPointF scene_point;
            // for (int i = 0; i < polygon.count(); ++i) {
            // }
            // scene_point = polygonItem->scenePos();
            QPointF scenePoint1;
            QPointF scenePoint2;
            QPointF scenePoint3;
            QPointF scenePoint4;

            if (polygon.size() == 4) 
            {


                scenePoint1 = polygonItem->mapToScene(polygon[0]);
                scenePoint2 = polygonItem->mapToScene(polygon[1]);
                scenePoint3 = polygonItem->mapToScene(polygon[2]);
                scenePoint4 = polygonItem->mapToScene(polygon[3]);
                
                scenePoint1 /= scale;
                scenePoint2 /= scale;
                scenePoint3 /= scale;
                scenePoint4 /= scale;

                jsonObject["x1"] = scenePoint1.x();
                jsonObject["y1"] = scenePoint1.y();
                jsonObject["x2"] = scenePoint2.x();
                jsonObject["y2"] = scenePoint2.y();
                jsonObject["x3"] = scenePoint3.x();
                jsonObject["y3"] = scenePoint3.y();
                jsonObject["x4"] = scenePoint4.x();
                jsonObject["y4"] = scenePoint4.y();              
            }
            areasArray.append(jsonObject);

            // 如果文件中已存在相同的 id，则更新相关内容
            bool foundId = false;
            for (int i = 0; i < lines.size(); ++i) {
                if (lines[i].contains("id: \"" + Jsonid + "\"")) {
                    foundId = true;
                    // 覆盖其下的坐标
                    lines[i + 1] = QString("    x1: %1").arg(scenePoint1.x());
                    lines[i + 2] = QString("    y1: %1").arg(scenePoint1.y());
                    lines[i + 3] = QString("    x2: %1").arg(scenePoint2.x());
                    lines[i + 4] = QString("    y2: %1").arg(scenePoint2.y());
                    lines[i + 5] = QString("    x3: %1").arg(scenePoint3.x());
                    lines[i + 6] = QString("    y3: %1").arg(scenePoint3.y());
                    lines[i + 7] = QString("    x4: %1").arg(scenePoint4.x());
                    lines[i + 8] = QString("    y4: %1").arg(scenePoint4.y());
                    break;
                }
            }

            // 如果没有找到相同的 id，则追加新数据
            if (!foundId) {
                lines.append(QString("  - id: \"%1\"").arg(Jsonid));
                lines.append(QString("    x1: %1").arg(scenePoint1.x()));
                lines.append(QString("    y1: %1").arg(scenePoint1.y()));
                lines.append(QString("    x2: %1").arg(scenePoint2.x()));
                lines.append(QString("    y2: %1").arg(scenePoint2.y()));
                lines.append(QString("    x3: %1").arg(scenePoint3.x()));
                lines.append(QString("    y3: %1").arg(scenePoint3.y()));
                lines.append(QString("    x4: %1").arg(scenePoint4.x()));
                lines.append(QString("    y4: %1").arg(scenePoint4.y()));
            }            
        }
    }

    // 将 JSON 数据转换为字符串
    QJsonDocument jsonDoc(areasArray);
    QString jsonString = jsonDoc.toJson(QJsonDocument::Indented);

    // 将 JSON 数据追加到 YAML 文件中
    if (!yamlContent.contains("areas:")) {
        stream << "areas:\n" << lines.join('\n');
    }
    else
    {
        stream << lines.join('\n');
    }
    // QJsonArray newAreasArray = QJsonDocument::fromJson(jsonString.toUtf8()).array();
    // for (const QJsonValue& value : newAreasArray) {
    //     QJsonObject jsonObj = value.toObject();
    //     stream << "  - id: \"" << jsonObj["id"].toString() << "\"\n";
    //     stream << "    x1: " << jsonObj["x1"].toDouble() << "\n";
    //     stream << "    y1: " << jsonObj["y1"].toDouble() << "\n";
    //     stream << "    x2: " << jsonObj["x2"].toDouble() << "\n";
    //     stream << "    y2: " << jsonObj["y2"].toDouble() << "\n";
    //     stream << "    x3: " << jsonObj["x3"].toDouble() << "\n";
    //     stream << "    y3: " << jsonObj["y3"].toDouble() << "\n";
    //     stream << "    x4: " << jsonObj["x4"].toDouble() << "\n";
    //     stream << "    y4: " << jsonObj["y4"].toDouble() << "\n";
    // }

    // // 将 JSON 数组转换为字符串并写入文件
    // QJsonDocument jsonDoc(areasArray);
    // QString jsonString = jsonDoc.toJson(QJsonDocument::Indented);
    // qDebug() << jsonString;
    // QTextStream out(&file);
    // out << jsonString << "\n";
    // file.write(jsonString.toLatin1());

    //发布ros
    auto message = std_msgs::msg::String();
    message.data = jsonString.toStdString();
    json_publisher_->publish(message);
    
    file.close();
}

void cameraWidget::readConfiguration() {
    // 定义 YAML 文件路径
    // qDebug() << "1";
    QString filePath = QString(tr("/home/sd-robot/hql_test/hit_Qt/src/hit_Qt/camera.yaml"));
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开文件";
        return;
    }

    // 读取文件内容
    QTextStream stream(&file);
    QString yamlContent = stream.readAll();
    file.close();

    // 清空当前的 QGraphicsPolygonItem（移除所有的多边形）
    QList<QGraphicsItem*> items = mScene->items();
    for (QGraphicsItem* item : items) {
        if (QGraphicsPolygonItem* polygonItem = dynamic_cast<QGraphicsPolygonItem*>(item)) {
            mScene->removeItem(polygonItem);
            delete polygonItem;
        }
    }

    double scale = 1.0;
    // 定义正则表达式用于匹配 id 和坐标 (x1, y1, x2, y2, x3, y3, x4, y4)
    QRegularExpression idRegex(R"id(\s*id:\s*"(.+?)")id");
    QRegularExpression coordRegex(R"coord(\s*x(\d):\s*(-?\d+(\.\d+)?)\s*y(\d):\s*(-?\d+(\.\d+)?))coord");

    QRegularExpressionMatchIterator idIter = idRegex.globalMatch(yamlContent);
    while (idIter.hasNext()) {
        QRegularExpressionMatch idMatch = idIter.next();
        QString jsonId = idMatch.captured(1); // 获取 id 值

        // 根据 id 判断当前的 cameraTopic
        bool isMatchingCamera = false;
        switch (cameraTopic) {
            case CAMERA_EL:
                isMatchingCamera = (jsonId == "img_el");
                scale = 1.0;
                break;
            case CAMERA_ER:
                isMatchingCamera = (jsonId == "img_er");
                scale = 1.0;
                break;
            case CAMERA_EI:
                isMatchingCamera = (jsonId == "img_e_in");
                scale = 0.5;
                break;
            case CAMERA_EO:
                isMatchingCamera = (jsonId == "img_e_out");
                scale = 0.5;
                break;
            case CAMERA_PO:
                isMatchingCamera = (jsonId == "img_p_out");
                scale = 0.5;
                break;
            default:
                break;
        }

        if (isMatchingCamera) {
            // 初始化一个空的 QPolygonF
            QPolygonF polygon;

            // 在当前位置后匹配 4 个坐标 (x1, y1, x2, y2, x3, y3, x4, y4)
            int currentPosition = idMatch.capturedStart(0);
            QRegularExpressionMatchIterator coordIter = coordRegex.globalMatch(yamlContent, currentPosition);

            while (coordIter.hasNext()) {
                QRegularExpressionMatch coordMatch = coordIter.next();
                // 提取坐标并添加到 QPolygonF
                double x = coordMatch.captured(2).toDouble() * scale;
                double y = coordMatch.captured(5).toDouble() * scale;
                polygon << QPointF(x, y);

                // 如果已经添加了4个点，退出循环
                if (polygon.size() == 4) {
                    break;
                }
            }

            // 创建 PolygonItem 用于显示红框
            PolygonItem* polygonItem = new PolygonItem(polygon);
            polygonItem->setPen(QPen(Qt::red, 1)); // 设置红色边框
            polygonItem->setFlag(QGraphicsItem::ItemIsMovable);
            polygonItem->setFlag(QGraphicsItem::ItemIsSelectable);
            polygonItem->setFlag(QGraphicsItem::ItemIsFocusable);
            // 将多边形添加到 mScene 中
            mScene->addItem(polygonItem);
        }
    }
}

void cameraWidget::videoPlay()
{
    // QString rtspUrl = mRtspLineEdit->text();
    // QString rtspUrl = "/home/sd-robot/Downloads/output.mp4";
    // if (rtspUrl.isEmpty())
    // {
    //     QMessageBox::warning(this, tr("rtsp源"), tr("rtsp源为空"));
    //     return;
    // }
    // mMediaPlayer->setMedia(QUrl::fromLocalFile(rtspUrl));
    // mMediaPlayer->play();
    // mCameraThread = new cameraRunnable();

    mCameraThread = new cameraRunnable;
    mCameraThread->start();
    connect(mCameraThread, &cameraRunnable::emitCameraMsg, this, &cameraWidget::handleCameraImage);
    
}

void cameraWidget::handleCameraImage()
{
    // qDebug() << "11";
    if (camera_image.isNull())
    {
        // qDebug() << "null";
        
        return;
    }
    // QPixmap pixmap = QPixmap::fromImage(camera_image);
    // qDebug() << "3";
    // 创建一个 QGraphicsPixmapItem 对象并将其添加到场景中
    QSize size = mView->size();
    // mScene->setSceneRect(0, 0, camera_image.width(), camera_image.height());
    // mView->setFixedSize(camera_image.width(), camera_image.height());
    // // 按照 QGraphicsPixmapItem 的大小缩放 QImage
    QImage scaledImage = camera_image.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // // 将缩放后的 QImage 设置为 QGraphicsPixmapItem 的图像
    pixmapItem->setPixmap(QPixmap::fromImage(scaledImage)); 
    // pixmapItem->setPixmap(QPixmap::fromImage(scaledImage));    
    // pixmapItem->setPixmap(pixmap);

}

void cameraWidget::videoStop()
{
    // mMediaPlayer->stop();
    mCameraThread->stop();
    disconnect(mCameraThread, &cameraRunnable::emitCameraMsg, this, &cameraWidget::handleCameraImage);
}

cameraWidget::~cameraWidget()
{
    cameraSwitch = false;
    stop_spin_ = true;
    if (ros_spin_thread_.joinable()) {
        ros_spin_thread_.join();
    }
    if (camera_thread_.joinable()) {
        camera_thread_.join();
    }
}
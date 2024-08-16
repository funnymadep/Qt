#include "mainwindow.h"
#include <QApplication>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      mediaPlayer(new QMediaPlayer(this)),
      videoWidget(new QVideoWidget(this)),
      startButton(new QPushButton("Start Stream", this))
{
    // 设置媒体播放器的输出为视频窗口
    mediaPlayer->setVideoOutput(videoWidget);

    // 创建布局
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(videoWidget);
    layout->addWidget(startButton);

    // 创建一个中心小部件
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    resize(640, 480);
    // 连接按钮点击信号到槽函数
    connect(startButton, &QPushButton::clicked, this, &MainWindow::startStream);
}

MainWindow::~MainWindow() {
    // 确保在销毁窗口时释放资源
    mediaPlayer->stop();
}

void MainWindow::startStream() {
    // 设置RTSP流的URL
    QString rtspUrl = "rtsp://admin:sd123456@192.168.1.108:554/cam/realmonitor?channel=1&subtype=0";
    mediaPlayer->setMedia(QUrl(rtspUrl));

    // 开始播放
    mediaPlayer->play();
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv); //管理整个应用程序
    MainWindow m;       //界面对象
    m.show();           //显示界面

    int result = a.exec();
   return result;
}

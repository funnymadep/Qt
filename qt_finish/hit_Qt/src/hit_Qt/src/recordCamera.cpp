#include "recordCamera.h"
#include <QMessageBox>
#include <QDateTimeEdit>
#include <QDateTime>
#include <QMessageBox>


recordCameraWidget::recordCameraWidget(QWidget *parent)
{
    QVBoxLayout *vlayout = new QVBoxLayout();
    createSetting(vlayout);
    this->setLayout(vlayout);
}

recordCameraWidget::~recordCameraWidget()
{
    
}

void recordCameraWidget::createSetting(QVBoxLayout *vlayout)
{
    mView = new QGraphicsView(this);
    vlayout->addWidget(mView);
    mScene = new QGraphicsScene(this);
    mView->setScene(mScene);
    mView->setMinimumSize(500, 450);

    mVideoItem = new QGraphicsVideoItem();
    mVideoItem->setSize(QSizeF(500, 450));
    mScene->addItem(mVideoItem);

    mView->show();

    mMediaPlayer = new QMediaPlayer(this);
    mMediaPlayer->setVideoOutput(mVideoItem);   

    {
        QHBoxLayout *h = new QHBoxLayout();
        vlayout->addLayout(h);   

        QPushButton *rtspPlay = new QPushButton(tr("播放"));
        h->addWidget(rtspPlay);
        connect(rtspPlay, &QPushButton::clicked, this, &recordCameraWidget::rtspPlayClicked);   

        QPushButton *rtspStop = new QPushButton(tr("停止"));
        h->addWidget(rtspStop);
        connect(rtspStop, &QPushButton::clicked, this, &recordCameraWidget::rtspStopClicked);
    }
    {
        QHBoxLayout *h = new QHBoxLayout();
        vlayout->addLayout(h);

        QLabel *startLabel = new QLabel(tr("起始时间: "));
        h->addWidget(startLabel);

        mStartTimeEdit = new QDateTimeEdit(this);
        h->addWidget(mStartTimeEdit);
        mStartTimeEdit->setCalendarPopup(true);
        mStartTimeEdit->setDisplayFormat("yyyy/MM/dd HH:mm:ss");
        QDateTime date = QDateTime::currentDateTime();
        QString datetime = date.toString("yyyy/MM/dd");
        qDebug() << datetime;
        datetime = datetime + " 00:00:00";
        date = QDateTime::fromString(datetime, "yyyy/MM/dd HH:mm:ss");
        mStartTimeEdit->setDateTime(date);

        h->addSpacing(50);
        QLabel *rtspLabel = new QLabel(tr("通道: "));
        h->addWidget(rtspLabel);
        rtspLabel->setMaximumWidth(100);

        mRtspLEdit = new QLineEdit(this);
        // mRtspLEdit->setText("rtsp://username:password@0.0.0.0:554/Streaming/tracks/1101?");
        mRtspLEdit->setMinimumWidth(200);
        h->addWidget(mRtspLEdit);
        mRtspLEdit->setMaximumWidth(100);
        h->addStretch();
    }
    // {
    //     QHBoxLayout *h = new QHBoxLayout();
    //     vlayout->addLayout(h);

    //     QLabel *startLabel = new QLabel(tr("终止时间"));
    //     h->addWidget(startLabel);

    //     mEndTimeEdit = new QDateTimeEdit(this);
    //     h->addWidget(mEndTimeEdit);
    //     mEndTimeEdit->setCalendarPopup(true);
    //     mEndTimeEdit->setDisplayFormat("yyyy/MM/dd HH:mm:ss");
    // } 
    
}

void recordCameraWidget::rtspPlayClicked()
{
    QString rtspPre = "rtsp://username:password@0.0.0.0:554/Streaming/tracks/";
    QString rtspBack = "01?";
    QString startTime = mStartTimeEdit->text();
    // QString endTime = mEndTimeEdit->text();
    QString rtspStr = mRtspLEdit->text();

    if (rtspStr.isEmpty())
    {
        QMessageBox::warning(this, tr("播放"), tr("通道不能为空"));
        return;
    }

    QStringList startDatePart = getDatePart(startTime);
    // QStringList endDatePart = getDatePart(endTime);
    // qDebug() << startTime << " " << endTime;

    QString formatTIme = startDatePart[0]+startDatePart[1]+startDatePart[2]+'T'
                        +startDatePart[3]+startDatePart[4]+startDatePart[5]+"Z";
                        // +'&'+endDatePart[0]+endDatePart[1]+endDatePart[2]+'T'
                        // +endDatePart[3]+endDatePart[4]+endDatePart[5]+'Z';

    rtspStr = rtspPre + rtspStr + rtspBack + formatTIme;
    qDebug() << rtspStr;

    // rtspStr = "/home/sd-robot/Downloads/00000000500000000.mp4";
    mMediaPlayer->setMedia(QUrl::fromLocalFile(rtspStr));
    mMediaPlayer->play();

    if (mMediaPlayer->state() == QMediaPlayer::PlayingState)
    {
        QMessageBox::information(this, tr("播放视频"), tr("播放成功"));
    }
}

QStringList recordCameraWidget::getDatePart(QString str)
{
    QStringList datePart = str.split(' ');
    QStringList dateList = datePart[0].split('/');
    QStringList timeList = datePart[1].split(':');

    QStringList returnList = dateList + timeList;
    return returnList;
}

void recordCameraWidget::rtspStopClicked()
{
    if (mMediaPlayer->state() == QMediaPlayer::StoppedState)
    {
        mMediaPlayer->stop();
    }    
}
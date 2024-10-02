#ifndef RECORD_CAMERA_H
#define RECORD_CAMERA_H

#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsVideoItem>
#include <QMediaPlayer>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>

class recordCameraWidget : public QWidget
{
    Q_OBJECT

public:
    recordCameraWidget(QWidget *parent = nullptr);
    ~recordCameraWidget();

    void createSetting(QVBoxLayout *vlayout);
    QStringList getDatePart(QString str);
private slots:
    void rtspPlayClicked();
    void rtspStopClicked();

private:
    QGraphicsView *mView = nullptr;
    QGraphicsScene *mScene = nullptr;
    QGraphicsVideoItem *mVideoItem = nullptr;
    QMediaPlayer *mMediaPlayer = nullptr;
    QLineEdit *mRtspLEdit = nullptr;
    QDateTimeEdit *mStartTimeEdit = nullptr;
    QDateTimeEdit *mEndTimeEdit = nullptr;
};

#endif
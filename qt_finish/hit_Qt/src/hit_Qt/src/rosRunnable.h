#ifndef ROS_RUNNABLE_H
#define ROS_RUNNABLE_H

#include <QThread>
// #include <QRunnable>
#include <QWidget>

class recordRunnable : public QThread
{
Q_OBJECT
public:
    explicit recordRunnable();
    void stop();
    void run();
signals:
    void emitRecordMsg();

private:
    
};

class lidarRunnable : public QThread
{
Q_OBJECT
public:
    explicit lidarRunnable();
    void stop();
    void run();
signals:
    void emitLidarMsg();
private:
    
};


class cameraRunnable : public QThread
{
Q_OBJECT
public:
    explicit cameraRunnable();
    void stop();
    void run();
signals:
    void emitCameraMsg();
private:
    
};


#endif 

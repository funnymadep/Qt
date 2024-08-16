#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QPushButton>
#include <QVBoxLayout>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startStream();

private:
    QMediaPlayer *mediaPlayer;
    QVideoWidget *videoWidget;
    QPushButton *startButton;
};

#endif // MAINWINDOW_H


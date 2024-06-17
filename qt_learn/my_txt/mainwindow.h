#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QTextEdit>
#include <QAction>
#include <QFile>
#include <QFileDialog>
#include <QFontDialog>
#include <QColorDialog>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QAction *file_act[3], *edit_act[3];
    QToolBar *tool;
    QTextEdit *te;
    QMenu *me[3];
    QStatusBar *stat;
private slots:
    void new_act();
    void open_act();
    void close_act();
    void search();
    void change_font();
    void change_color();

};
#endif // MAINWINDOW_H

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QStringList item = {"文件", "编辑", "查看",
                        "新建文件", "打开文件", "关闭文件",
                        "新建文件...", "打开文件...", "关闭文件...",
                       "查找", "替换字体", "改变颜色",
                       "查找...", "替换...", "转到..."};
    stat = statusBar();
    for(int i = 0; i < 3; i++){
        me[i] = menuBar()->addMenu(item.at(i));
        file_act[i] = new QAction(item.at(i+3));
        file_act[i]->setStatusTip(item.at(i+6));
        edit_act[i] = new QAction(item.at(i+9));
        edit_act[i]->setStatusTip(item.at(i+12));
        me[0]->addAction(file_act[i]);
    }

    for(int i = 0; i < 3; i++)
        me[1]->addAction(edit_act[i]);
    te = new QTextEdit;
    te->setMinimumSize(640, 480);
    setCentralWidget(te);



    connect(file_act[0], &QAction::triggered, this, &MainWindow::new_act);
    connect(file_act[1], &QAction::triggered, this, &MainWindow::open_act);
    connect(file_act[2], &QAction::triggered, this, &MainWindow::close_act);
    connect(edit_act[0], &QAction::triggered, this, &MainWindow::search);
    connect(edit_act[1], &QAction::triggered, this, &MainWindow::change_font);
    connect(edit_act[2], &QAction::triggered, this, &MainWindow::change_color);

}

MainWindow::~MainWindow()
{
}

void MainWindow::new_act()
{
    te->clear();
}

void MainWindow::open_act()
{
    QString filename = QFileDialog
            ::getOpenFileName(this, "打开文件", ".", "Texts(*.txt *.h *.cpp *.c)");
    if (filename.isEmpty())
        return;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly|QIODevice::Text))
    te->setText("文件打开失败：" + file.errorString());
    te->append(file.readAll());
    file.close();
}

void MainWindow::close_act()
{
    this->close();
}

void MainWindow::search()
{
    /*QString str = Find
    te->find();*/
}

void MainWindow::change_font()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, QFont("Helvetica [Cronyx]", 20)
                                      , this, "选择字体");
    if(ok)
    te->setCurrentFont(font);
}

void MainWindow::change_color()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "改变颜色");
    if (color.isValid())
        te->setTextColor(color);
}


#include "recordWidget.h"
#include "point_cloud_subscriber.h"
#include <QPushButton>
// #include <QLineEdit>
#include <pcl/compression/octree_pointcloud_compression.h>
#include <QThread>
#include <iostream>
#include <QDateTime>
#include <QThreadPool>
#include <QDir>
#include <QMessageBox>
#include <QHeaderView>

QString rosbagPath = "/home/sd-robot/hql_test/hit_Qt/src/ros2bag";

recordWidget::recordWidget(QWidget *parent) {
    QVBoxLayout *vlayout = new QVBoxLayout();
    setLayout(vlayout);
    createSetting(vlayout);
    createStackedWidget(vlayout);
}

recordWidget::~recordWidget() {
//    mRecord->stop();
//    mBagPlay->terminate(); 
    recordSwitch = 0;
}

void recordWidget::createSetting(QVBoxLayout *vlayout)
{
    mBagPlay = new QProcess();

    mPageComb = new QComboBox(this);
    vlayout->addWidget(mPageComb);
    mPageComb->addItems(QStringList() << tr("显示界面") << tr("查询界面") << tr("记录界面"));
    mPageComb->setCurrentText(tr("显示界面"));
    connect(mPageComb, &QComboBox::currentTextChanged, this, &recordWidget::pageChanged);

}

void recordWidget::pageChanged(QString str)
{
    if (str == "显示界面")
    {
        if(mSearchWgt)
        {
            mStackerWgt->removeWidget(mSearchWgt);
            mSearchWgt->deleteLater();
            mSearchWgt = nullptr;
        }

        if(mRecordWgt)
        {
            mStackerWgt->removeWidget(mRecordWgt);
            mRecordWgt->deleteLater();
            mRecordWgt = nullptr;
        }

        mStackerWgt->setCurrentWidget(mViewerWgt);
    }
    else if (str == "查询界面")
    {
        qDebug() << "cha";
        if(mRecordWgt)
        {
            qDebug() << "1";
            mStackerWgt->removeWidget(mRecordWgt);
            qDebug() << "2";
            mRecordWgt->deleteLater();
            qDebug() << "3";
            mRecordWgt = nullptr;
        }
        qDebug() << "xun";
        createSearch();
        mStackerWgt->setCurrentWidget(mSearchWgt);
    }
    else if (str == "记录界面")
    {
        if(mSearchWgt)
        {
            mStackerWgt->removeWidget(mSearchWgt);
            mSearchWgt->deleteLater();
            mSearchWgt = nullptr;
        }
        createRecord();
        mStackerWgt->setCurrentWidget(mRecordWgt);
    }
}

void recordWidget::topicCombChange(QString str)
{
    if (str == "电气房左侧激光")
    {
        recordTopic = RECORD_EL;
        qDebug() << "el";
    }
    else if (str == "电气房右侧激光")
    {
        recordTopic = RECORD_ER;
        qDebug() << "er";
    }
    else if (str == "动力房左侧激光")
    {
        recordTopic = RECORD_PL;  
        qDebug() << "pl";
    }
    else if (str == "动力房右侧激光")
    {
        recordTopic = RECORD_PR;
        qDebug() << "pr";
    }
}

void recordWidget::createStackedWidget(QVBoxLayout *vlayout)
{
    mStackerWgt = new QStackedWidget(this);
    vlayout->addWidget(mStackerWgt);

    createViewer();

    // PointThread *thread = new PointThread;
    // connect(thread, &PointThread::pointCloudReceived, this, &lidarWidget::handlePointCloudReceived);
    // thread->start(); 
}

void recordWidget::onPlayButtonClicked()
{
    QList<QTableWidgetItem *> selectedItems = mTableWgt->selectedItems();
    QString dirName;
    if (!selectedItems.isEmpty()) {
        if (selectedItems.size() == 6) {  // 确保选中了6项
            dirName = QString("%1_%2_%3-%4_%5_%6")
                .arg(selectedItems[0]->text())
                .arg(selectedItems[1]->text())
                .arg(selectedItems[2]->text())
                .arg(selectedItems[3]->text())
                .arg(selectedItems[4]->text())
                .arg(selectedItems[5]->text());
            qDebug() << dirName;
        } 
       
    }
    playBag(dirName);
}

void recordWidget::mvRecordClicked()
{
    QList<QTableWidgetItem *> selectedItems = mTableWgt->selectedItems();
    QString dirName;
    if (!selectedItems.isEmpty()) {
        if (selectedItems.size() == 6) {  // 确保选中了6项
            dirName = QString("%1_%2_%3-%4_%5_%6")
                .arg(selectedItems[0]->text())
                .arg(selectedItems[1]->text())
                .arg(selectedItems[2]->text())
                .arg(selectedItems[3]->text())
                .arg(selectedItems[4]->text())
                .arg(selectedItems[5]->text());
            qDebug() << dirName;
        } 
       
    }
    writeRecordTxt(dirName);
   
}

void recordWidget::writeRecordTxt(QString txt)
{
    QString recordPathTxt = rosbagPath + "/record.txt";
    // qDebug() << txt;
    QStringList recordList = getRecordList();
    if (recordList.contains(txt))
    {
        return;
    }

    // 打开文件以追加模式写入
    QFile file(recordPathTxt);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << txt << "\n";
        file.close();
        QMessageBox::information(this, "Success", "record success!");
    } else {
        QMessageBox::warning(this, "Error", "Failed to record!");
    } 
}

void recordWidget::createViewer()
{

    mViewerWgt = new QWidget(this);
    mStackerWgt->addWidget(mViewerWgt);

    QVBoxLayout *v = new QVBoxLayout();
    mViewerWgt->setLayout(v);
    {
        vtkWidget = new QVTKOpenGLNativeWidget(this);
        v->addWidget(vtkWidget);

        {
            QHBoxLayout *h = new QHBoxLayout();
            v->addLayout(h);
            dateTimeEdit = new QDateTimeEdit(this);
            h->addWidget(dateTimeEdit);
            QStringList names = getDirList();
            qDebug() << names;
            if (names.isEmpty())
            {
                QMessageBox::warning(this, tr("bag包"), tr("未找到bag包"));
                return;
            }
            QStringList datelist = getDirPartList(names.first());
            QString name = QString("%1/%2/%3 %4:%5")
                .arg(datelist.at(0))
                .arg(datelist.at(1))
                .arg(datelist.at(2))
                .arg(datelist.at(3))
                .arg(datelist.at(4));
            //    .arg(datelist.at(5));
            qDebug() << name;
            QDateTime datetime = QDateTime::fromString(name, "yyyy/MM/dd HH:mm");
            dateTimeEdit->setDateTime(datetime);
            dateTimeEdit->setDisplayFormat("yyyy/MM/dd HH:mm");

            
            QPushButton *recordBag = new QPushButton(tr("回放激光"));
            h->addWidget(recordBag);
            connect(recordBag, &QPushButton::clicked, this, &recordWidget::recordBagClicked);
        }
        {
            mTopicComb = new QComboBox(this);
            v->addWidget(mTopicComb);
            mTopicComb->addItems(QStringList() << "电气房左侧激光" << "电气房右侧激光" << "动力房左侧激光" << "动力房右侧激光");
            connect(mTopicComb, &QComboBox::currentTextChanged, this, &recordWidget::topicCombChange);
        }
    }
    // initRos();
    initializeViewer();
}

void recordWidget::createSearch()
{
    // qDebug() << "1";
    mSearchWgt = new QWidget(this);
    mStackerWgt->addWidget(mSearchWgt);

    QVBoxLayout *v = new QVBoxLayout();
    mSearchWgt->setLayout(v);

    mTableWgt = new QTableWidget(this);
    v->addWidget(mTableWgt);

    mTableWgt->setColumnCount(6);
    mTableWgt->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mTableWgt->setHorizontalHeaderLabels(QStringList() << tr("年") << tr("月") << tr("日") << tr("时") << tr("分") << tr("秒"));
    mTableWgt->horizontalHeader()->setStretchLastSection(true);
    mTableWgt->setSelectionBehavior(QAbstractItemView::SelectRows);

    QStringList names = getDirList();
    QString name, subName;
    foreach(name, names)
    {
        // qDebug() << name;
        QStringList datePart = getDirPartList(name);
        int row = mTableWgt->rowCount();
        mTableWgt->insertRow(row);
        for (int column = 0; column < datePart.size(); column++) {
            QTableWidgetItem* item = new QTableWidgetItem(datePart.at(column));
            mTableWgt->setItem(row, column, item);
            // qDebug() << datePart.at(column);
        }
    }


    {
        QHBoxLayout *h = new QHBoxLayout();
        v->addLayout(h);

        QPushButton *playButton = new QPushButton("播放", this);
        h->addWidget(playButton);
        connect(playButton, &QPushButton::clicked, this, &recordWidget::onPlayButtonClicked);

        QPushButton *mvRecord = new QPushButton("记录", this);
        h->addWidget(mvRecord);
        connect(mvRecord, &QPushButton::clicked, this, &recordWidget::mvRecordClicked);
    }



    mStackerWgt->setCurrentWidget(mSearchWgt);
    // qDebug() << "1";
}

void recordWidget::createRecord()
{
    mRecordWgt = new QWidget(this);
    mStackerWgt->addWidget(mRecordWgt);

    QVBoxLayout *v = new QVBoxLayout();
    mRecordWgt->setLayout(v);

    mRecordTableWgt = new QTableWidget(this);
    v->addWidget(mRecordTableWgt);

    mRecordTableWgt->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mRecordTableWgt->setColumnCount(1);
    mRecordTableWgt->setHorizontalHeaderLabels(QStringList() << tr("时间"));
    mRecordTableWgt->horizontalHeader()->setStretchLastSection(true);
    mRecordTableWgt->setSelectionBehavior(QAbstractItemView::SelectRows);   

    {
        QHBoxLayout *h = new QHBoxLayout();
        v->addLayout(h);

        QPushButton *recordPlay = new QPushButton(tr("播放"));
        h->addWidget(recordPlay);
        connect(recordPlay, &QPushButton::clicked, this, &recordWidget::recordPlayClicked);

        QPushButton *delRecord = new QPushButton(tr("删除记录"));
        h->addWidget(delRecord);
        connect(delRecord, &QPushButton::clicked, this, &recordWidget::delRecordClicked);
    } 

    QStringList lines = getRecordList();

    // 输出读取的字符串列表，作为调试
    foreach (const QString &line, lines)
    {
        QStringList datelist = getDirPartList(line);
        QString name = QString("%1/%2/%3 %4:%5")
                .arg(datelist.at(0))
                .arg(datelist.at(1))
                .arg(datelist.at(2))
                .arg(datelist.at(3))
                .arg(datelist.at(4));
            //    .arg(datelist.at(5));
            // qDebug() << name;
        int row = mRecordTableWgt->rowCount();
        mRecordTableWgt->insertRow(row);
        QTableWidgetItem *item = new QTableWidgetItem(name); 
        mRecordTableWgt->setItem(row, 0, item);
    }

}

void recordWidget::recordPlayClicked()
{
    QList<QTableWidgetItem *> selectedItems = mRecordTableWgt->selectedItems();
    if (!selectedItems.isEmpty()) {
        if (selectedItems.size() == 1) {  // 确保选中了6项
            QString dbName = selectedItems.first()->text();
            // qDebug() << dbName;
            QStringList filePart = dbName.split(' ');
            QStringList datepart = filePart[0].split('/');
            QStringList timepart = filePart[1].split(':');

            QString selectFileName = datepart[0] + '_' + datepart[1] + '_' + datepart[2] + '-'
                            + timepart[0] + '_' + timepart[1];

            // qDebug() << selectFileName;
            QStringList recordtxt = getRecordList();
            foreach(QString name, recordtxt)
            {
                if(name.contains(selectFileName))
                {
                    // qDebug() << name;
                    playBag(name);
                }

            }
        } 
       
    }    
}

void recordWidget::delRecordClicked()
{
    QList<QTableWidgetItem *> selectedItems = mRecordTableWgt->selectedItems();
    if (!selectedItems.isEmpty()) {
        if (selectedItems.size() == 1) {  // 确保选中了6项
            QString dbName = selectedItems.first()->text();
            // 指定要删除的字符串
            qDebug() << dbName;
            delRecordTxt(dbName);
            // mRecordTableWgt->viewport()->update();
            mRecordTableWgt->removeRow(selectedItems.first()->row());
        } 
       
    } 
 
}

void recordWidget::delRecordTxt(QString txt)
{
    // 打开文件以读取
    QString recordPathTxt = rosbagPath + "/record.txt";
    QFile file(recordPathTxt);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Failed to open file for reading!");
        return;
    }

    QStringList lines;
    QTextStream in(&file);

    // 逐行读取文件内容，并排除包含指定字符串的行
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (!line.contains(txt)) {
            lines << line;
        }
    }
    file.close();

    // 重新打开文件以写入模式覆盖原文件内容
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(this, "Error", "Failed to open file for writing!");
        return;
    }

    QTextStream out(&file);
    for (const QString &line : lines) {
        out << line << "\n";
    }
    file.close();

    QMessageBox::information(this, "Success", "delete record date sucess");    
}

QStringList recordWidget::getRecordList()
{
    QStringList lines;
    QString recordPathTxt = rosbagPath + "/record.txt";
    // 打开文件以只读模式读取
    QFile file(recordPathTxt);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (line == "\n" && line == "")
            {
                continue;
            }
            lines << line;
        }
        file.close();
        // QMessageBox::information(this, "Success", "Read from file completed!");
        return lines;
    } else {
        QMessageBox::warning(this, "Error", "Failed to open file for reading!");
        return QStringList();
    }    
}

void recordWidget::initRos()
{  
    mRecord = new recordRunnable();
    mRecord->start();
    connect(mRecord, &recordRunnable::emitRecordMsg, this, &recordWidget::handlePointCloudReceived);
}

void recordWidget::initializeViewer() {
    renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    vtkWidget->setRenderWindow(renderWindow);

    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderWindow->AddRenderer(renderer);

    viewer.reset(new pcl::visualization::PCLVisualizer(renderer, renderWindow, "record_viewer", false));
    vtkWidget->setRenderWindow(viewer->getRenderWindow());
    viewer->setupInteractor(vtkWidget->interactor(), vtkWidget->renderWindow());

    viewer->setBackgroundColor(0.1, 0.1, 0.1);
    viewer->addCoordinateSystem(1.0);
    viewer->initCameraParameters();
    viewer->setCameraPosition(-15, 0, 10,
        0, 0, 0,
        0, 0, 1);
}

void recordWidget::recordBagClicked()
{
    QDateTime dateTime = dateTimeEdit->dateTime();
    QString selectFileName = dateTime.toString("yyyy/MM/dd HH:mm");
    // qDebug() << selectFileName;
    QStringList filePart = selectFileName.split(' ');
    QStringList datepart = filePart[0].split('/');
    QStringList timepart = filePart[1].split(':');

    selectFileName = datepart[0] + '_' + datepart[1] + '_' + datepart[2] + '-'
                        + timepart[0] + '_' + timepart[1];
    QStringList dirname = getDirList();
    foreach(QString name, dirname)
    {
        if (name.contains(selectFileName))
            selectFileName = name;        
    }

    qDebug() << selectFileName;

    playBag(selectFileName);
    // foreach (QString dirName, names) {
    //     // qDebug() << "111";
    //     if (dirName == selectFileName)
    //     {
            
    //     }
    // }
}

void recordWidget::playBag(QString selectFileName)
{
    QString path = rosbagPath; // 替换为你要查找的目录路径

    QStringList names = getDirList(); // 获取所有文件名


    if (names.contains(selectFileName))
    {
        // qDebug() << QApplication::applicationDirPath();     
        if (mBagPlay->state() == QProcess::Running)
        {
            mBagPlay->terminate();
            mRecord->stop();
        }      

        QString selectedDirPath = QString("%1/%2").arg(path, selectFileName);

        compressZSTD(selectedDirPath);

        QString db3File = QString("%1/%2/%2_0.db3").arg(path, selectFileName);
        // mBagPlay->setWorkingDirectory(path);
        qDebug() << db3File;
        mBagPlay->start("ros2", QStringList() 
            << "bag" <<"play" << db3File << "-l" << "--remap" 
            << "/livox/lidar_3GGDLCR00200131:=/livox/lidar_el"
            << "/livox/lidar_3GGDLCR00200171:=/livox/lidar_er" 
            << "/livox/lidar_3GGDLCR00200321:=/livox/lidar_pl"
            << "/livox/lidar_3GGDLCR00200371:=/livox/lidar_pr"
        );

        initRos();

        if (!mBagPlay->waitForStarted()) {
            QMessageBox::warning(this, tr("回放"), tr("回放启动失败"));
            // qDebug() << "Failed to start process";
            return;
        }

        if (mBagPlay->state() == QProcess::Running)
        {
            QMessageBox::information(this, tr("回放"), tr("回放成功"));
            // sleep(2);
        }

    }
    else
    {
        QMessageBox::warning(this, tr("回放"), tr("请输入正确的时间"));
        // qDebug() << "Failed to start process";
        return;
    }
}

void recordWidget::compressZSTD(QString selectedDirPath)
{
    QDir selectedDir(selectedDirPath);

    if (!selectedDir.exists()) {
        QMessageBox::warning(this, tr("错误"), tr("目录不存在"));
        return;
    }

    QStringList fileNames = selectedDir.entryList(QDir::Files); // 获取该目录下所有文件的文件名

    // 打印出文件名
    qDebug() << "Files in directory:" << fileNames;

    // 解压 .zstd 文件并删除
    for (const QString& fileName : fileNames)
    {
        if (fileName.endsWith(".zstd"))
        {
            QString fullFilePath = selectedDirPath + "/" + fileName;
            QString decompressedFilePath = fullFilePath;
            decompressedFilePath.chop(5); // 去掉 ".zstd" 后缀

            // 调用 zstd 解压命令
            QProcess process;
            QStringList arguments;
            arguments << "-d" << fullFilePath << "-o" << decompressedFilePath; // 解压到指定输出文件
            process.start("zstd", arguments);
            process.waitForFinished();

            if (process.exitCode() == 0)
            {
                qDebug() << "Decompressed: " << fileName;

                // 解压成功后删除 .zstd 文件
                if (QFile::remove(fullFilePath))
                {
                    qDebug() << "Deleted: " << fullFilePath;
                }
                else
                {
                    qDebug() << "Failed to delete: " << fullFilePath;
                }
            }
            else
            {
                qDebug() << "Failed to decompress: " << fileName;
                QMessageBox::warning(this, tr("错误"), tr("解压失败: ") + fileName);
            }
        }
    }
}

void recordWidget::handlePointCloudReceived()
{
    // record_cloud->clear();
    if (recordTopic == RECORD_EL)
    {
        record_cloud = record_cloud_el;
    }
    else if (recordTopic == RECORD_ER)
    {
        record_cloud = record_cloud_er;
    }
    else if (recordTopic == RECORD_PL)
    {
        record_cloud = record_cloud_pl;
    }
    else if (recordTopic == RECORD_PR)
    {
        record_cloud = record_cloud_pr;
        // qDebug()
    }

    std::string color = "intensity";
    // std::unique_lock<std::mutex> lock(recordmtx);
    if (record_cloud && !record_cloud->empty()) {
        cloudQueue.push_back(record_cloud);
        std::string id_string = "cloud" + std::to_string(id++);
        // QString str = QString::fromStdString(id_string) ;
        idsQueue.push_back(id_string);
        // pcl::PointCloud<pcl::PointXYZI>::Ptr accumulatedCloud(new pcl::PointCloud<pcl::PointXYZI>);
        pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZI> CloudColorHandler(record_cloud, color);
        // qDebug() << str;
        viewer->addPointCloud(record_cloud , CloudColorHandler, id_string);
        if (cloudQueue.size() > maxCloudCount) {
            // std::cout << id << " " << cloudQueue.size()<< std::endl;
            viewer->removePointCloud(idsQueue.front());
                // viewer->removeAllPointClouds();
            cloudQueue.pop_front();
            idsQueue.pop_front();
            if (id == maxCloudCount+1)
            {
                id = 0;
            }
        }
        // std::cout << id_string << " " << std::endl;
    }

    // if (!record_vector.empty())
    // {
    //     viewer->removeAllPointClouds();
    //     std::unique_lock<std::mutex> lock(recordmtx);
    //     // pcl::PointCloud<pcl::PointXYZI>::Ptr cloud;
    //     if (!record_vector.front()->empty())
    //     {
    //         qDebug() << record_vector.size();
    //         // *cloud = record_vector.at(i);
    //         std::string id_string = "cloud" + std::to_string(id++);
    //         pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZI> CloudColorHandler(record_vector.front(), color);
    //         viewer->addPointCloud(record_vector.front() , CloudColorHandler, id_string);
    //         record_vector.pop_front();
    //     }
    //     record_vector.clear();
    //     id = 0;
    // }
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    vtkWidget->update();
    renderWindow->Render();
}


QStringList recordWidget::getDirList()
{
    QString path = rosbagPath; // 替换为你要查找的目录路径
    QDir dir(path);

    if (!dir.exists()) {
        // qDebug() << "Directory does not exist!";
        QMessageBox::warning(this, tr("bag路径"), tr("bag包路径不存在!"));
        return QStringList();
    }

    QStringList names = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot) ; // 获取所有文件名    
    return names;
}

QStringList recordWidget::getDirPartList(QString name)
{
    QStringList dateTimeParts = name.split(QRegExp("[_\\-]"));
    return dateTimeParts;
}
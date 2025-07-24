#ifndef LIBOTACONTROLLER_H
#define LIBOTACONTROLLER_H

// #include "libOTAController_global.h"
#include <QtCore/qglobal.h>
#include <QFile>
#include <QObject>
#include <QString>
#include <QTimer>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrlQuery>
#include <QFile>
#include <QString>
#include <QVector>
#include <QTimer>

#if defined(LIBOTACONTROLLER_LIBRARY)
#define LIBOTACONTROLLER_EXPORT Q_DECL_EXPORT
#else
#define LIBOTACONTROLLER_EXPORT Q_DECL_IMPORT
#endif

class LIBOTACONTROLLER_EXPORT LibOTAController : public QObject
{
    Q_OBJECT
public:
    LibOTAController();

private:
    //下载状态枚举变量定义
    enum class DownloadStatus {
        NotStarted,
        Downloading,
        Completed,
        Error
    };

    QNetworkAccessManager *m_networkManager;// 网络管理器
    //downLoad
    QString m_downloadStatusCheckerurl; // 上报下载状态服务器链接
    QString m_upgradeStatusCheckerurl; // 上报更新状态服务器链接
    QString m_url; // 下载链接
    QString m_deviceid; // 当前机器编号
    QString m_currentversion; // 控制器端当前版本
    bool m_networkStatus;  //当前网络状态
    QString m_filePath; // 文件保存路径
    QString m_fileName; // 文件名
    QString m_md5; // MD5校验码
    QVector<QFile*> m_parts; // 分片文件列表
    QVector<bool> m_partsStatus; // 用于跟踪每个分片的下载状态
    int m_partSize; // 分片大小
    qint64 m_totalSize; // 文件大小
    int m_totalParts; // 总分片数
    qint64 m_downloadedBytes; // 已下载字节数
    int m_attempt; //重发次数
    DownloadStatus m_downloadStatus; //标记下载状态
    QTimer *timer;  //网络监测定时器
    int m_value; //刷新升级进度用
public:
    void setParameter(const QString &deviceid, const QString &currentversion);

    //getUpdateInfo
    void getOTAInfo(const QString &deviceId, const QString &currentVersion, const QString &OTAInfourl);

    //getDownLoadAddress
    void getOTAAddressInfo(const QString &deviceId, const QString &downLoadAddressurl, const QString &filePath, int partSize, const QString &downloadStatusCheckerurl);

    //downLoad
    void gethandleHead(); //获取头信息
    void startDownload(); // 启动下载
    void downloadPart(int partIndex); // 下载分片
    void mergeParts();  //合并分片

    //downloadStatus
    void downloadStatusChecker(const QString &deviceId,const QString &downloadCode,const QString &fileName);

    //upgradeStatus
    void upgradeStatusChecker(const QString &deviceId, const QString &upgradeCode, const QString &version, const QString &upgradeStatusCheckerurl);

private slots:
    //getUpdateInfo
    void onGetOTAInfoFinished(QNetworkReply *reply);   //回调处理响应，解析JSON数据并发出信号。
    //getDownLoadAddress
    void onGetOTAAddressInfoFinished(QNetworkReply *reply);
    //downLoad
    void handleHeadResponse(QNetworkReply *reply); // 处理获得文件头的响应
    void onDownloadPartFinished(int partIndex,QNetworkReply *reply); // 回复完成处理
    //CompleteDownload
    void onDownloadStatusCheckFinished(QNetworkReply *reply, const QString &deviceId, const QString &downloadCode, const QString &fileName); //下载成功失败回调处理响应，解析JSON数据并发出信号。
    //CompleteUpgrade
    void onUpgradeStatusCheckFinished(QNetworkReply *reply, const QString &deviceId, const QString &upgradeCode, const QString &version);

signals:
    //显示更新包信息
    void getOTAInfoFinished(bool success, const QString &info, bool isHave, const QString &fileName, const QString &fileDesc);
    //显示下载完成（失败/成功）界面
    void downLoadFinished(bool success);
    // 发出下载进度信号
    void downloadProgress(qint64 downloadedBytes, qint64 totalSize, int partIndex);

//    void DownloadStatusChanged(DownloadStatus downloadStatus);

};

#endif // LIBOTACONTROLLER_H

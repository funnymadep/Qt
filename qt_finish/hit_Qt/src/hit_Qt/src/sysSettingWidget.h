#ifndef SYS_SETTING_WIDGET_H
#define SYS_SETTING_WIDGET_H

#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

class sysSettingWidget : public QWidget
{
    Q_OBJECT

public:
    sysSettingWidget(QWidget *parent = nullptr);
    ~sysSettingWidget();

    void createStatus(QVBoxLayout *vlayout);
    void createSetting(QVBoxLayout *vlayout);
    void sysBypassChecked();
    void sysReboot();
    void systemReboot();
private slots:
    void SettingButtonGroupClicked(int id);
    void updateStatus();
private:
    QLabel *mCpuTemperature     = nullptr;                  // cpu温度
    QLabel *mGpuTemperature     = nullptr;                  // gpu温度
    QLabel *mMemoryFootprint    = nullptr;                  // 内存占用
    QLabel *mGraphicsOccupancy  = nullptr;                  // 显存占用
    QLabel *mIsAnticollision    = nullptr;                  // 是否防撞
    QLabel *mProgramStatus      = nullptr;                  // 程序状态
    QLabel *mPCLStatus          = nullptr;                  // plc状态

    QPushButton *sysBypass      = nullptr;
};

#endif
#include "sysSettingWidget.h"

#include <QHBoxLayout>
#include <QButtonGroup>
#include <QApplication>
#include <QProcess>
#include <QMessageBox>
#include <QDebug>

sysSettingWidget::sysSettingWidget(QWidget *parent)
{
    QVBoxLayout *vlayout = new QVBoxLayout();
    setLayout(vlayout);

    createStatus(vlayout);
    createSetting(vlayout);
}

sysSettingWidget::~sysSettingWidget()
{

}

void sysSettingWidget::createStatus(QVBoxLayout *vlayout)
{
    QHBoxLayout *h = new QHBoxLayout();
    vlayout->addLayout(h);
    {
        QVBoxLayout *v = new QVBoxLayout();
        h->addLayout(v);
        mCpuTemperature = new QLabel(tr("CPU温度: 56°"));
        v->addWidget(mCpuTemperature);

        mGpuTemperature = new QLabel(tr("GPU温度: 80°"));
        v->addWidget(mGpuTemperature);

        mMemoryFootprint = new QLabel(tr("内存占用: 55%"));
        v->addWidget(mMemoryFootprint);

        mGraphicsOccupancy = new QLabel(tr("显存占用: 60°"));
        v->addWidget(mGraphicsOccupancy);

        v->addStretch();
    }
    {
        QVBoxLayout *v = new QVBoxLayout();
        h->addLayout(v);
        mIsAnticollision = new QLabel(tr("是否开启了防撞: 是"));
        v->addWidget(mIsAnticollision);

        mProgramStatus = new QLabel(tr("程序状态： 正常"));
        v->addWidget(mProgramStatus);

        mPCLStatus = new QLabel(tr("PLC状态: 正常"));
        v->addWidget(mPCLStatus);

        v->addStretch();
    }
                     
}

void sysSettingWidget::createSetting(QVBoxLayout *vlayout)
{
    QWidget *setting = new QWidget();
    QVBoxLayout *v = new QVBoxLayout(setting);
    vlayout->addWidget(setting);

    QButtonGroup *buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(false);

    sysBypass = new QPushButton(tr("系统旁路: 关闭"));
    buttonGroup->addButton(sysBypass, 1);
    v->addWidget(sysBypass);

    QPushButton *sysReboot = new QPushButton(tr("系统重启"));
    buttonGroup->addButton(sysReboot, 2);
    v->addWidget(sysReboot);

    QPushButton *stationReboot = new QPushButton(tr("工作站重启"));
    buttonGroup->addButton(stationReboot, 3);
    v->addWidget(stationReboot);

    v->addStretch();
    connect(buttonGroup, &QButtonGroup::idClicked, this, &sysSettingWidget::SettingButtonGroupClicked);
}

void sysSettingWidget::sysReboot()
{
    qApp->exit(10);
}

void sysSettingWidget::systemReboot()
{
    QProcess reboot;
    reboot.start("sudo", QStringList() << tr("reboot"));
}

void sysSettingWidget::SettingButtonGroupClicked(int id)
{
    switch (id)
    {
    case 1:
        sysBypassChecked();
        break;
    case 2:
        sysReboot();
        break;
    case 3:
        systemReboot();
        break;
    default:
        QMessageBox::critical(this, tr("button id"), tr("button id error"));
        break;
    }

}

void sysSettingWidget::sysBypassChecked()
{
    if (sysBypass->text().contains(tr("关闭")))
    {
        sysBypass->setText(tr("系统旁路: 打开"));
        qDebug() << "系统旁路打开";

    }
    else
    {
        sysBypass->setText(tr("系统旁路: 关闭"));
        qDebug() << "系统旁路关闭" ;
    }
}
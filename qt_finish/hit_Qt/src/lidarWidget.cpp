#include "lidarWidget.h"


lidarWidget::lidarWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *hlayout = new QHBoxLayout();
    setLayout(hlayout);

    QVBoxLayout *vLeft = new QVBoxLayout();
    hlayout->addLayout(vLeft);
    createStatus(vLeft);
    createCloudPoint(vLeft);
    createSetting(hlayout);
}

lidarWidget::~lidarWidget()
{
    
}

void lidarWidget::createStatus(QVBoxLayout *vLeft)
{
    QVBoxLayout *v = new QVBoxLayout();
    vLeft->addLayout(v);
    {
        QHBoxLayout *h = new QHBoxLayout();
        v->addLayout(h);

        mLabelStatus = new QLabel(tr("激光状态: 正常"),this);
        mLabelStatus->setMaximumSize(150, 32);
        h->addWidget(mLabelStatus);
        
        h->addSpacing(50);

        mLabelIsHide = new QLabel(tr("是否遮挡: 是"),this);
        mLabelIsHide->setMaximumSize(150, 32);
        h->addWidget(mLabelIsHide);

        h->addStretch();
    }
    {
        QHBoxLayout *h = new QHBoxLayout();
        v->addLayout(h);

        mLabelIsBlock = new QLabel(tr("是否存在障碍物: 否"),this);
        mLabelIsBlock->setMaximumSize(150, 32);
        h->addWidget(mLabelIsBlock);

        h->addSpacing(30);

        mLabelBlockLen = new QLabel(tr("最近障碍物距离: 100CM"),this);
        mLabelBlockLen->setMaximumSize(150, 32);
        h->addWidget(mLabelBlockLen);

        h->addStretch();
    }
    {
        QHBoxLayout *h = new QHBoxLayout();
        v->addLayout(h);

        mLabelAntiCollisionMode = new QLabel(tr("防撞模式: 自动"),this);
        mLabelAntiCollisionMode->setMaximumSize(150, 32);
        h->addWidget(mLabelAntiCollisionMode);
        h->addStretch();
    }
    // v->addStretch();

}

void lidarWidget::createCloudPoint(QVBoxLayout *vLeft)
{
    pointCloudWidget *pointWidget = new pointCloudWidget(this);
    vLeft->addWidget(pointWidget);

    // Client client(pointWidget);
}

void lidarWidget::createSetting(QHBoxLayout *hlayout)
{
    QVBoxLayout *v = new QVBoxLayout();
    hlayout->addLayout(v);

    v->addStretch();
    comb = new QComboBox(this);
    v->addWidget(comb);

    QStringList items;
    items << tr("基于车道线解算") << tr("自定义区域");
    comb->addItems(items);
    comb->setCurrentText(tr("基于车道线解算"));

    {
        QHBoxLayout *h = new QHBoxLayout();
        v->addLayout(h);
        QLabel *lateralDistanceLabel = new QLabel(tr("防撞横向距离: "));
        h->addWidget(lateralDistanceLabel);

        lateralDistanceEdit = new QLineEdit(this);
        lateralDistanceEdit->setEnabled(false);
        h->addWidget(lateralDistanceEdit);
    }
    {
        QHBoxLayout *h = new QHBoxLayout();
        v->addLayout(h);
        QLabel *LongitudinalDistanceLabel = new QLabel(tr("防撞纵向距离: "));
        h->addWidget(LongitudinalDistanceLabel);

        QLineEdit *LongitudinalDistanceEdit = new QLineEdit(this);
        LongitudinalDistanceEdit->setEnabled(false);
        h->addWidget(LongitudinalDistanceEdit);
    }

    v->addStretch();
}
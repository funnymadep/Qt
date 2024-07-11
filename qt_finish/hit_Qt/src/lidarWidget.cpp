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

        mLabelStatus = new QLabel(tr("激光状态: "),this);
        mLabelStatus->setMaximumSize(150, 32);
        h->addWidget(mLabelStatus);

        mLabelIsHide = new QLabel(tr("是否遮挡: "),this);
        mLabelIsHide->setMaximumSize(150, 32);
        h->addWidget(mLabelIsHide);

    }
    {
        QHBoxLayout *h = new QHBoxLayout();
        v->addLayout(h);

        mLabelIsBlock = new QLabel(tr("是否遮挡: "),this);
        mLabelIsBlock->setMaximumSize(150, 32);
        h->addWidget(mLabelIsBlock);

        mLabelBlockLen = new QLabel(tr("是否遮挡: "),this);
        mLabelBlockLen->setMaximumSize(150, 32);
        h->addWidget(mLabelBlockLen);

    }
    {
        QHBoxLayout *h = new QHBoxLayout();
        v->addLayout(h);

        mLabelAntiCollisionMode = new QLabel(tr("是否遮挡: "),this);
        mLabelAntiCollisionMode->setMaximumSize(150, 32);
        h->addWidget(mLabelAntiCollisionMode);
    }
    // v->addStretch();

}

void lidarWidget::createCloudPoint(QVBoxLayout *vLeft)
{
    QLabel * test = new QLabel(tr("点云显示部分 还未完成"));
    vLeft->addWidget(test);
}

void lidarWidget::createSetting(QHBoxLayout *hlayout)
{
    QVBoxLayout *v = new QVBoxLayout();
    hlayout->addLayout(v);

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


}
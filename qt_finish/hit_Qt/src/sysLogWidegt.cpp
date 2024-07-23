#include "sysLogWidegt.h"

#include <QPushButton>
#include <QCheckBox>
#include <QButtonGroup>
#include <QDebug>
#include <QDateTimeEdit>
#include <QTime>
#include <QTimeEdit>


sysLogWidget::sysLogWidget(QWidget *parent)
{
    QVBoxLayout *vlayout = new QVBoxLayout();
    createSearch(vlayout);
    createSearchList(vlayout);
    this->setLayout(vlayout);
}

sysLogWidget::~sysLogWidget()
{
    
}

void sysLogWidget::createSearch(QVBoxLayout *vlayout)
{
    QVBoxLayout *v = new QVBoxLayout();
    vlayout->addLayout(v);

    QButtonGroup *buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(false);

    {
        QHBoxLayout *h = new QHBoxLayout();
        v->addLayout(h);

        QDateTimeEdit *dateTimeEdit = new QDateTimeEdit(this);
        h->addWidget(dateTimeEdit);
        dateTimeEdit->setDisplayFormat("yyyy-MM-dd");

        QDateTime minDateTime(QDate(2024, 1, 1), QTime(12, 0));
        dateTimeEdit->setMinimumDateTime(minDateTime);
        dateTimeEdit->setMaximumDateTime(QDateTime::currentDateTime());
        dateTimeEdit->setCalendarPopup(true);

        QTimeEdit *timeEdit = new QTimeEdit(this);
        h->addWidget(timeEdit);
        timeEdit->setMaximumTime(QTime::currentTime());
        timeEdit->setCalendarPopup(true);

        QCheckBox *alarmTime = new QCheckBox(tr("报警时间"), this);
        h->addWidget(alarmTime);
        buttonGroup->addButton(alarmTime, 1);
    }

    QCheckBox *blockLenth = new QCheckBox(tr("障碍物距离"), this);
    v->addWidget(blockLenth);
    buttonGroup->addButton(blockLenth, 2);

    QCheckBox *alarmLocation = new QCheckBox(tr("报警位置"), this);
    v->addWidget(alarmLocation);
    buttonGroup->addButton(alarmLocation, 3);

    mSearchCriteria = new QPushButton("查询条件", this);
    v->addWidget(mSearchCriteria);
    connect(mSearchCriteria, &QPushButton::clicked, this, &sysLogWidget::searchCriteriaButtonClick);

    mResetsearchCriteria = new QPushButton(tr("重置条件"), this);
    v->addWidget(mResetsearchCriteria);
    connect(mResetsearchCriteria, &QPushButton::clicked, this, &sysLogWidget::resetsearchCriteriaButtonClick);
}

void sysLogWidget::searchCriteriaButtonClick()
{
    QButtonGroup *buttonGroup = this->findChild<QButtonGroup*>();

    QList<QAbstractButton*> buttons = buttonGroup->buttons();
    foreach(QAbstractButton *button, buttons) {
        if(button->isChecked()) {
            if(buttonGroup->id(button) == 1) {
                qDebug() << "Performing action for Option 1";
            } else if(buttonGroup->id(button) == 2) {
                qDebug() << "Performing action for Option 2";
            } else if(buttonGroup->id(button) == 3) {
                qDebug() << "Performing action for Option 3";
            }
        }
    }
}

void sysLogWidget::resetsearchCriteriaButtonClick()
{
    QButtonGroup *buttonGroup = this->findChild<QButtonGroup*>();

    QList<QAbstractButton*> buttons = buttonGroup->buttons();
    foreach(QAbstractButton *button, buttons) {
        button->setChecked(false);
    }
}

void sysLogWidget::createSearchList(QVBoxLayout *vlayout)
{
    mSearchList = new QTableWidget();
    vlayout->addWidget(mSearchList);
    mSearchList->setColumnCount(3);
    mSearchList->setHorizontalHeaderLabels(QStringList() << tr("报警时间") << tr("报警位置")
        << tr("障碍物距离"));
    
    mSearchList->setEditTriggers(QAbstractItemView::NoEditTriggers);

}




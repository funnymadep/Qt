#ifndef SYS_LOG_WIDGET_H
#define SYS_LOG_WIDGET_H

#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QWidget>

class sysLogWidget : public QWidget
{
    Q_OBJECT

public:
    sysLogWidget(QWidget *parent = nullptr);
    ~sysLogWidget();

    void createSearch(QVBoxLayout *vlayout);
    void createSearchList(QVBoxLayout *vlayout);
private slots:
    void searchCriteriaButtonClick();
    void resetsearchCriteriaButtonClick();
private:
    QPushButton *mSearchCriteria;        //查询条件
    QPushButton *mResetsearchCriteria;   //重置查询条件

    QTableWidget *mSearchList;
};

#endif
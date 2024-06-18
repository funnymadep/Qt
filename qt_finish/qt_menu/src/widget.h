#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QProcess>
#include <QFileInfo>
#include <QGroupBox>
#include <QLabel>
#include <QDoubleSpinBox>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void mStartBtnClicked();
    void mDataRecordBtnClicked();
    void mDataPlaybackBtnClicked();
    void mDataSaveBtnClicked();
    // void mDataOpenDirRecordBtnC();

private:
    QPushButton *mStartBtn;
    QPushButton *mDataRecordBtn;
    QPushButton *mDataPlaybackBtn;
    QPushButton *mDataSaveBtn;

    QLineEdit *mDataRecodeEdit;
    QDoubleSpinBox *mDataIntervalSpin;

    QComboBox *mDataTypeCombo;
    QComboBox *mDataSelectCombo;
    
    QString savePath = nullptr;
};
#endif // WIDGET_H

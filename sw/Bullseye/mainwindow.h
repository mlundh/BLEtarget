#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QTimer>

#include <QFile>
#include <QStringList>
#include <QDebug>

#include "hitdata.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class SettingsDialog;
class menu;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    void openSerialPort();

    void closeSerialPort();
    void save();
    void clear();
    void readData();

    void handleError(QSerialPort::SerialPortError error);

    void heartbeatTimeout();
    void heartbeatReceived();
    void startHeartbeatTimer();

signals:
    void newHit(int x, int y, int speedX, int speedY);

private:
    Ui::MainWindow *ui;
    SettingsDialog *mSettings = nullptr;
    menu *mMenu = nullptr;
    QSerialPort *mSerial;
    QByteArray mSerialDataBuff;
    bool mFoundStart;
    QTimer mHeartbeatTimer;
    QVector<hitData> mHitData;
};
#endif // MAINWINDOW_H

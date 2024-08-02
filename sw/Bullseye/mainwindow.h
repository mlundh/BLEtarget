#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QTimer>

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
    void about();
    void writeData(const QByteArray &data);
    void readData();

    void handleError(QSerialPort::SerialPortError error);

    void heartbeatTimeout();
    void heartbeatReceived();
    void startHeartbeatTimer();

signals:
    void newHit(int x, int y, int speed);

private:
    Ui::MainWindow *ui;
    SettingsDialog *mSettings = nullptr;
    menu *mMenu = nullptr;
    QSerialPort *mSerial;
    QByteArray mSerialDataBuff;
    bool mFoundStart;
    QTimer mHeartbeatTimer;
};
#endif // MAINWINDOW_H

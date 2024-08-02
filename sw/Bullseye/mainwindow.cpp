#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QSerialPort>
#include "menu.h"
#include <QMessageBox>
#include "settingsdialog.h"
#include "slippacket.h"
#include "serialization.h"

typedef enum{
  hitData = 0,
  heartbeat = 1
}messageId_t;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mMenu(new menu(this))
    , mSettings(new SettingsDialog(this))
    , mSerial(new QSerialPort(this))
    , mFoundStart(false)
{
    ui->setupUi(this);
    connect(ui->menuButton, &QPushButton::clicked, this, [=](){this->mMenu->show();});
    connect(ui->clearButton, &QPushButton::clicked, ui->bullseye, &Bullseye::clear);
    connect(mMenu, &menu::settingsButton, this, [=](){this->mSettings->show();});
    connect(mMenu, &menu::connectButtion, this, &MainWindow::openSerialPort);
    connect(mMenu, &menu::disconnectButton, this, &MainWindow::closeSerialPort);
    connect(mMenu, &menu::aboutButton, this, &MainWindow::about);
    connect(mMenu, &menu::settingsButton, mSettings, &SettingsDialog::updatePortInfo);
    connect(mSerial, &QSerialPort::readyRead, this, &MainWindow::readData);
    connect(this, &MainWindow::newHit, ui->bullseye, &Bullseye::addHit);
    connect(&mHeartbeatTimer, &QTimer::timeout, this, &MainWindow::heartbeatTimeout);

    // TODO add file to save previous configruation.
    //Try to open with default parameters.
    openSerialPort();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mMenu;
    delete mSettings;
}

void MainWindow::openSerialPort()
{
    const SettingsDialog::Settings p = mSettings->settings();
    mSerial->setPortName(p.name);
    mSerial->setBaudRate(p.baudRate);
    mSerial->setDataBits(p.dataBits);
    mSerial->setParity(p.parity);
    mSerial->setStopBits(p.stopBits);
    mSerial->setFlowControl(p.flowControl);
    if (mSerial->open(QIODevice::ReadWrite)) {
        //QMessageBox::information(this, tr("Info"), "Port open");
        qDebug() << "Port open";
        ui->connection->setText("Connected");
        startHeartbeatTimer();
    } else {
        QMessageBox::critical(this, tr("Error"), mSerial->errorString() + " Device: " + mSerial->portName());
        ui->connection->setText("Error" + mSerial->errorString());
    }
}

void MainWindow::closeSerialPort()
{
    if (mSerial->isOpen())
        mSerial->close();
    ui->connection->setText("Closed");
    mHeartbeatTimer.stop();
    //QMessageBox::information(this, tr("Info"), "Disconnected");
}


void MainWindow::about()
{
    QMessageBox::about(this, tr("About Bullseye"),
                       tr("The Center ring represents a ring with 5mm radius. each subsequent ring has a raduis which is 5mm larger."));
}

void MainWindow::readData()
{
    char data = 0;
    while(mSerial->read(&data, 1) == 1)
    {
        if(data == SlipPacket::frame_boundary_octet)
        {
            if(mFoundStart) // end of package.
            {
                try
                {
                    mSerialDataBuff.append(data);   // slip package includes the frame_boundary_octet
                    SlipPacket packet(mSerialDataBuff, false);
                    QByteArray data = packet.GetPayload();

                    // TODO make a proper parser, and allow debug messages as well.

                    if(data.size() == 4*sizeof(int32_t))
                    {
                        uint8_t* toDeserialize = (uint8_t*)data.data();
                        qDebug() << mSerialDataBuff.toHex();
                        uint32_t size = data.size();

                        int32_t messageId = 0;
                        toDeserialize = serialization::deserialize_int32_t(toDeserialize, &size, &messageId);

                        if(messageId == hitData)
                        {
                            int32_t xValue=0;
                            int32_t yValue=0;
                            int32_t speedValue=0;

                            toDeserialize = serialization::deserialize_int32_t(toDeserialize, &size, &xValue);
                            toDeserialize = serialization::deserialize_int32_t(toDeserialize, &size, &yValue);
                            serialization::deserialize_int32_t(toDeserialize, &size, &speedValue);

                            emit newHit(xValue, yValue, speedValue);
                            qDebug() << "New hit. X: " << xValue << " Y: " << yValue << " speed: " << speedValue;
                            heartbeatReceived();// new data is also a proof that the connection works.
                        }
                        else if (messageId == heartbeat)
                        {
                            heartbeatReceived();
                        }

                    }
                    else
                    {
                        qDebug() << "Unexpected data size in serial package.";
                    }
                    mSerialDataBuff.clear(); // clear in preparation for next data chunk.
                    mFoundStart = false; // prepare for next data chunk.


                } catch (const std::exception& e) {
                    qDebug() << e.what();
                }
            }
            else // start of package.
            {
                mSerialDataBuff.clear(); // make sure buffer is empty
                mSerialDataBuff.append(data);
                mFoundStart = true;
            }
        }
        else if(mFoundStart)
        {
            mSerialDataBuff.append(data);
        }
        else if(!mFoundStart)
        {
            qDebug() << "Discarding data" << data;
        }
        else
        {
            QMessageBox::critical(this, tr("Error"), "Error parsing the message."); // error! some bug in the code above...
        }
    }


}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), mSerial->errorString());
        closeSerialPort();
    }
}

void MainWindow::heartbeatTimeout()
{
    mHeartbeatTimer.stop();
    QMessageBox::information(this, tr("Heartbeat timeout"), "Heartbeat signal timeout, please check target power and position.");
    startHeartbeatTimer(); // restart once the message box returns.
}

void MainWindow::heartbeatReceived()
{
    startHeartbeatTimer();
    qDebug() << "Heartbeat received.";
}


void MainWindow::startHeartbeatTimer()
{
    mHeartbeatTimer.start(4000);
}


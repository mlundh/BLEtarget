#include "menu.h"
#include "qpushbutton.h"
#include "ui_menu.h"

menu::menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
    connect(ui->exitButton, &QPushButton::clicked, this, &QApplication::quit);
    connect(ui->configurationButton, &QPushButton::clicked, this, [=](){emit this->settingsButton();});
    connect(ui->closeButton, &QPushButton::clicked, this, &QDialog::hide);
    connect(ui->connectButton, &QPushButton::clicked, this, [=](){emit this->connectButtion();});
    connect(ui->disconnectButton, &QPushButton::clicked, this, [=](){emit this->disconnectButton();});
    connect(ui->aboutButton, &QPushButton::clicked, this, [=](){emit this->aboutButton();});
}

menu::~menu()
{
    delete ui;
}


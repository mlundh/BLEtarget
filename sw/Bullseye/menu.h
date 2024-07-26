#ifndef MENU_H
#define MENU_H

#include <QDialog>
namespace Ui {
class menu;
}

class menu : public QDialog
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = nullptr);
    ~menu();

signals:
    void settingsButton();
    void connectButtion();
    void disconnectButton();
    void aboutButton();
private:
    Ui::menu *ui;
};

#endif // MENU_H

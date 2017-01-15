#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include "VirtualController.hpp"

#include <string>
#include <functional>
#include <iostream>

namespace Ui {

    class LoginWindow;

}

class LoginWindow : public QMainWindow{
    Q_OBJECT
    VirtualController* vc = nullptr;

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

    bool setController(VirtualController* vc);

    void loginFailed();

private:
    Ui::LoginWindow *ui;

    void loginButtonClicked();

};

#endif // MAINWINDOW_H

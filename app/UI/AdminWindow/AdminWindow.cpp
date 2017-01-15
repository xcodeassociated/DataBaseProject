#include "AdminWindow.hpp"
#include "ui_AdminWindow.h"

AdminWindow::AdminWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

bool AdminWindow::setController(VirtualController* vc){
    if (vc != nullptr){
        this->vc = vc;
        return true;
    }else
        return false;
}

void AdminWindow::setup_view() {
    
}

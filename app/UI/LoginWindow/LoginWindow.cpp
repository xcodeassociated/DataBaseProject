#include "LoginWindow.h"
#include "ui_LoginWindow.h"

LoginWindow::LoginWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::LoginWindow){
    this->ui->setupUi(this);

        std::cout << "MainWindow Constructor" << std::endl;

    connect(this->ui->loginButton, &QPushButton::clicked, [&](void){
        this->loginButtonClicked();
    });

    //this->ui->ClickButton->disconnect();
}

LoginWindow::~LoginWindow(){
    delete ui;
}

bool LoginWindow::setController(VirtualController* vc){
    if (vc != nullptr){
        this->vc = vc;
        return true;
    }else
        return false;
}

void LoginWindow::loginButtonClicked(){
    std::cout << "click" << "\n";
    if (!this->ui->loginField->text().toStdString().empty()) {
        auto data = std::pair<std::string, std::string>(this->ui->loginField->text().toStdString(),
                                                        this->ui->passwordField->text().toStdString());
        this->vc->loginCheck(data);
    }else{
        std::cerr << "empty login window" << "\n";
    }
}

void LoginWindow::loginFailed() {
    this->ui->loginField->clear();
    this->ui->passwordField->clear();
    
    std::cerr << "login has failed" << "\n";
    this->ui->infobox->setText({"Wprowadzone dane sa niepoprawne!"});
}

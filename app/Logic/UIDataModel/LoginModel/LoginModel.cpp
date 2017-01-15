//
// Created by jm on 15.01.17.
//

#include "LoginModel.hpp"

void LoginModel::checkLoginData(std::pair<std::string, std::string>& data){
    // data check...
    if (data.first == "r.login" && data.second == "rpass"){
        this->vController->loginInfo(true, Window::PatientRegistrationWindow);
    }else if (data.first == "d.login" && data.second == "dpass"){
        this->vController->loginInfo(true, Window::DoctorsWindow);
    }else if (data.first == "a.login" && data.second == "apass") {
        this->vController->loginInfo(true, Window::AdminWindow);
    }else
        this->vController->loginInfo(false, Window::None);
}
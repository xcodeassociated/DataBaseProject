//
// Created by jm on 15.01.17.
//

#ifndef SYSMED_LOGINMODEL_HPP
#define SYSMED_LOGINMODEL_HPP

#include "Model.hpp"
    
class LoginModel : public Model {
public:
    using Model::Model;
    void checkLoginData(std::pair<std::string, std::string>&);
    ~LoginModel() = default;
};



#endif //SYSMED_LOGINMODEL_HPP

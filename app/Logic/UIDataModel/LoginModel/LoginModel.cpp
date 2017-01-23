//
// Created by jm on 15.01.17.
//

#include "LoginModel.hpp"

void LoginModel::update_data() {
    this->update_patients(PatientQueryOrder::Id, QuerySort::ASC);
    this->update_staff();
    this->update_pexams(PExamsQueryOrder::ID, QuerySort::ASC);
    this->update_pmedrecords();
    this->update_pprescriptions();
    this->update_pexamresults();
}

void LoginModel::checkLoginData(std::pair<std::string, std::string>& data) {
    
    sql::PreparedStatement *stmt = nullptr;
    sql::ResultSet *res = nullptr;
    
    std::string name, lastname, pesel_str;
    std::size_t id, pesel;
    OwnerType otype = OwnerType::None;
    
    
    if (data.first[0] == 's') {
        stmt = this->connection->prepareStatement(
                "SELECT \n"
                        "`SysMed`.`Staff`.`id` as `ID`, `name` as `Name`, `lastname` as `Lastname`, `pesel` as `PESEL`\n"
                        "FROM `SysMed`.`Staff`\n"
                        "\tINNER JOIN `SysMed`.`Login`\n"
                        "\tON `SysMed`.`Staff`.`id` = `SysMed`.`Login`.`id_staff`\n"
                        "    WHERE `SysMed`.`Login`.`login` = (?) AND `SysMed`.`Login`.`pass` = (?) LIMIT 1;"
        );
        stmt->setString(1, data.first);
        stmt->setString(2, data.second);
        otype = OwnerType::Staff;
    } else if (data.first[0] == 'd') {
        stmt = this->connection->prepareStatement(
                "SELECT \n"
                        "`SysMed`.`Doctors`.`id` as `ID`, `name` as `Name`, `lastname` as `Lastname`, `pesel` as `PESEL`\n"
                        "FROM `SysMed`.`Doctors`\n"
                        "\tINNER JOIN `SysMed`.`Login`\n"
                        "\tON `SysMed`.`Doctors`.`id` = `SysMed`.`Login`.`id_doctor`\n"
                        "    WHERE `SysMed`.`Login`.`login` = (?) AND `SysMed`.`Login`.`pass` = (?) LIMIT 1;"
        );
        stmt->setString(1, data.first);
        stmt->setString(2, data.second);
        otype = OwnerType::Doctor;
    } else {
        this->vController->loginInfo(false, Window::None);
        return;
    }
    
    res = stmt->executeQuery();
    
    if (res->rowsCount() == 0) {
        this->vController->loginInfo(false, Window::None);
        delete stmt;
        delete res;
        return;
    }
    
    while (res->next()) {
        id = static_cast<std::size_t >(res->getInt(1));
        name = res->getString("Name");
        lastname = res->getString("Lastname");
        pesel_str = res->getString("PESEL");
        std::stringstream sstream(pesel_str);
        sstream >> pesel;
    }

    Model::owner = {name, lastname, id, pesel};
    Model::ownerType = otype;
    
    delete stmt;
    delete res;
    
    if (Model::ownerType == Model::OwnerType::Staff){
        this->vController->loginInfo(true, Window::PatientRegistrationWindow);
    }else if (Model::ownerType == Model::OwnerType::Doctor){
        this->vController->loginInfo(true, Window::DoctorsWindow);
    }else if (Model::ownerType == Model::OwnerType::Admin) {
        this->vController->loginInfo(true, Window::AdminWindow);
    }
        
}
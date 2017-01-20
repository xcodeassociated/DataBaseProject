//
// Created by jm on 15.01.17.
//

#include "RegistrationModel.hpp"

void RegistrationModel::update_data() {
    this->update_patients();
    this->update_staff();
    this->update_pexams();
    this->update_pmedrecords();
    this->update_pprescriptions();
    this->update_pexamresults();
}

bool RegistrationModel::addPatient(patient& p, patient_medinfo_reg& data){
    sql::PreparedStatement *stmt = nullptr;
    sql::ResultSet *res = nullptr;
    
    try {
        auto savepoint = this->create_transaction();
        
        auto adr = std::get<4>(p);
        
        stmt = this->connection->prepareStatement(
                "INSERT INTO `SysMed`.`Patients` (`id`, `name`, `lastname`, `pesel`)"
                        "VALUES (null, (?), (?), (?));"
                        
        );
        stmt->setString(1, std::get<0>(p));
        stmt->setString(2, std::get<1>(p));
        stmt->setString(3, std::to_string(std::get<3>(p)));
        res = stmt->executeQuery();
        delete res;
        delete stmt;
        
        stmt = this->connection->prepareStatement("SELECT getNewInsertedPatientsID() as 'LastInsertedPatientsID';"); //("SELECT `id` FROM `SysMed`.`Patients` ORDER BY `id` DESC LIMIT 1;");
        res = stmt->executeQuery();
        assert(res->rowsCount() == 1);
        res->next();
        std::size_t inserted_id = static_cast<std::size_t>(res->getInt(1));
        delete res;
        delete stmt;
    
        stmt = this->connection->prepareStatement(
                "INSERT INTO `SysMed`.`PersonAddress` (`id_patient`, `id_doctor`, `id_staff`, `city`, `street`, `house_nr`, `flat_nr`, `postal_code`)"
                        "VALUES ((?), null, null, (?), (?), (?), (?), (?));"
        );
        stmt->setInt(1, inserted_id);
        stmt->setString(2, std::get<0>(adr));
        stmt->setString(3, std::get<1>(adr));
        
        std::stringstream ss{std::get<2>(adr)};
        int house_nr;
        ss >> house_nr;
        stmt->setInt(4, house_nr);
        
        if (std::get<3>(adr).size() > 0) {
            int flat_nr;
            std::stringstream ss2{std::get<3>(adr)};
            ss2 >> flat_nr;
            stmt->setInt(5, flat_nr);
        }else{
            stmt->setNull(5, 0);
        }
        
        stmt->setString(6, std::get<4>(adr));
        
        res = stmt->executeQuery();
        delete res;
        delete stmt;
    
        for (std::tuple<std::string, std::string, std::string>& e : data) {
            if (!std::get<0>(e).empty() && !std::get<1>(e).empty()) {
                stmt = this->connection->prepareStatement(
                        "INSERT INTO `SysMed`.`PatientMedicalInfo` (`id_patient`, `disease_date`, `disease_type`, `disease_other_info`)"
                                "VALUES ((?), (?), (?), (?));"
                );
                stmt->setInt(1, inserted_id);
                stmt->setDateTime(2, std::get<0>(e));
                stmt->setString(3, std::get<1>(e));
                stmt->setString(4, std::get<2>(e));
    
                res = stmt->executeQuery();
                delete res;
                delete stmt;
            }
        }
        
        this->commit_transaction();
        
        this->update_patients();
        this->update_pmedrecords();
        
    }catch (sql::SQLException &e){
        std::cerr << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cerr << "SQL ERR: " << e.what() << std::endl;
        delete res;
        delete stmt;
        return false;
    }
    return true;
}

bool RegistrationModel::addPatientExam(patient_id& p, patient_exam_reg& data){

    sql::PreparedStatement *stmt = nullptr;
    sql::ResultSet *res = nullptr;
    
    try{
        auto savepoint = this->create_transaction();
        std::cerr << "-1\n";
        stmt = this->connection->prepareStatement(
                "INSERT INTO `SysMed`.`PatientExamDate` (`id_patient`, `id_doctor`, `exam_date`, `other_examdate_info`)"
                        "VALUES ((?), (?), ( select cast( (cast((?) as datetime) + cast((?) as time)) as datetime)  ), (?));"
        );
        stmt->setInt(1, p);
        stmt->setInt(2, std::get<0>(data));
        stmt->setString(3, std::get<1>(data));
        stmt->setString(4, std::get<2>(data));
        stmt->setString(5, std::get<3>(data));
        
        res = stmt->executeQuery();
        std::cerr << "-11\n";
        delete res;
        delete stmt;
    
        this->commit_transaction();
  
        this->update_pexams();
        
    }catch (sql::SQLException &e){
        std::cerr << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cerr << "SQL ERR: " << e.what() << std::endl;
        delete res;
        delete stmt;
        return false;
    }
    return true;
}

bool RegistrationModel::deletePatient(patient_id& p_id){
    sql::PreparedStatement *stmt = nullptr;
    sql::ResultSet *res = nullptr;
    
    try{
        auto savepoint = this->create_transaction();
    
        sql::PreparedStatement *stmt = nullptr;
        sql::ResultSet *res = nullptr;
    
        /* This query will delete patient with given id as well as other data related with this patient id thanks to "CASCADE DELETE"*/
        stmt = this->connection->prepareStatement("DELETE FROM `SysMed`.`Patients`"
                                                          "WHERE `SysMed`.`Patients`.`id` = (?); ");
        stmt->setInt(1, p_id);
        res = stmt->executeQuery();
        
        delete res;
        delete stmt;
        
        this->commit_transaction();
        
        this->update_data();
        
    }catch (sql::SQLException &e){
        std::cerr << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cerr << "SQL ERR: " << e.what() << std::endl;
        delete res;
        delete stmt;
        return false;
    }
    return true;
}

bool RegistrationModel::deleteExam(exam_id& e_id){
    sql::PreparedStatement *stmt = nullptr;
    sql::ResultSet *res = nullptr;
    
    try{
        auto savepoint = this->create_transaction();
    
        stmt = this->connection->prepareStatement("DELETE FROM `SysMed`.`PatientExamDate`"
                                                          "WHERE `SysMed`.`PatientExamDate`.`id_patient_exam` = (?); ");
        stmt->setInt(1, e_id);
        res = stmt->executeQuery();
        
        delete res;
        delete stmt;
        
        this->commit_transaction();
        
        this->update_pexams();
        
    }catch (sql::SQLException &e){
        std::cerr << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cerr << "SQL ERR: " << e.what() << std::endl;
        delete res;
        delete stmt;
        return false;
    }
    return true;
}


bool RegistrationModel::editPatientExam(patient_id& p, patient_exam_reg& data, std::size_t e_id){
    sql::PreparedStatement *stmt = nullptr;
    sql::ResultSet *res = nullptr;
    
    try{
        auto savepoint = this->create_transaction();
    
        stmt = this->connection->prepareStatement(
                "UPDATE `SysMed`.`PatientExamDate` SET"
                        "`id_patient` = (?), "
                        "`id_doctor` = (?), "
                        "`exam_date` = (select cast( (cast((?) as datetime) + cast((?) as time)) as datetime)),"
                        "`other_examdate_info` = (?)"
                        "WHERE `SysMed`.`PatientExamDate`.`id_patient_exam` = (?);"
        );
        stmt->setInt(1, static_cast<int>(p));
        stmt->setInt(2, static_cast<int>(std::get<0>(data)));
        stmt->setString(3, std::get<1>(data));
        stmt->setString(4, std::get<2>(data));
        stmt->setString(5, std::get<3>(data));
        stmt->setInt(6, static_cast<int>(e_id));
        
        res = stmt->executeQuery();
        
        delete res;
        delete stmt;
        
        this->commit_transaction();
        
        this->update_pexams();
        
    }catch (sql::SQLException &e){
        std::cerr << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cerr << "SQL ERR: " << e.what() << std::endl;
        delete res;
        delete stmt;
        return false;
    }
    return true;
}

bool RegistrationModel::editPatient(patient& p, patient_medinfo_reg& data){
    sql::PreparedStatement *stmt = nullptr;
    sql::ResultSet *res = nullptr;
    
    try {
        auto savepoint = this->create_transaction();
        
        auto p_id = std::get<2>(p);
        patient_adr adr = std::get<4>(p);
    
        stmt = this->connection->prepareStatement(
                "UPDATE `SysMed`.`Patients` SET"
                        "`name` = (?), "
                        "`lastname` = (?),"
                        "`pesel` = (?)"
                        "WHERE `SysMed`.`Patients`.`id` = (?);"
    
        );
        stmt->setString(1, std::get<0>(p));
        stmt->setString(2, std::get<1>(p));
        stmt->setString(3, std::to_string(std::get<3>(p)));
        stmt->setInt(4, static_cast<int>(p_id));
        res = stmt->executeQuery();
        delete res;
        delete stmt;
    
        stmt = this->connection->prepareStatement(
                "UPDATE `SysMed`.`PersonAddress` SET "
                        "`city` = (?),"
                        "`street` = (?), "
                        "`house_nr` = (?), "
                        "`flat_nr` = (?),"
                        "`postal_code` = (?)"
                        "WHERE `SysMed`.`PersonAddress`.`id_patient` = (?);"
        );
        stmt->setString(1, std::get<0>(adr));
        stmt->setString(2, std::get<1>(adr));
    
        std::stringstream ss{std::get<2>(adr)};
        int house_nr;
        ss >> house_nr;
        stmt->setInt(3, house_nr);
    
        if (std::get<3>(adr).size() > 0) {
            int flat_nr;
            std::stringstream ss2{std::get<3>(adr)};
            ss2 >> flat_nr;
            stmt->setInt(4, flat_nr);
        }else{
            stmt->setNull(4, 0);
        }
    
        stmt->setString(5, std::get<4>(adr));
        stmt->setInt(6, static_cast<int>(p_id));
        res = stmt->executeQuery();
        delete res;
        delete stmt;
    
        stmt = this->connection->prepareStatement(
                "DELETE FROM `SysMed`.`PatientMedicalInfo` "
                        "WHERE `SysMed`.`PatientMedicalInfo`.`id_patient` = (?) "
        );
        stmt->setInt(1, static_cast<int>(p_id));
        res = stmt->executeQuery();
        delete res;
        delete stmt;
        
        for (std::tuple<std::string, std::string, std::string>& e : data) {
            if (!std::get<0>(e).empty() && !std::get<1>(e).empty()) {
                stmt = this->connection->prepareStatement(
                        "INSERT INTO `SysMed`.`PatientMedicalInfo` (`id_patient`, `disease_date`, `disease_type`, `disease_other_info`)"
                                "VALUES ((?), (?), (?), (?));"
                );
                stmt->setInt(1, static_cast<int>(p_id));
                stmt->setDateTime(2, std::get<0>(e));
                stmt->setString(3, std::get<1>(e));
                stmt->setString(4, std::get<2>(e));
    
                res = stmt->executeQuery();
                delete res;
                delete stmt;
            }
        }
        
        this->commit_transaction();
        
        this->update_patients();
        this->update_pmedrecords();
        
    }catch (sql::SQLException &e){
        std::cerr << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cerr << "SQL ERR: " << e.what() << std::endl;
        delete res;
        delete stmt;
        return false;
    }
    return true;
    
}
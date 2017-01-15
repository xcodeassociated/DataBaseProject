//
// Created by jm on 15.01.17.
//

#include "RegistrationModel.hpp"

bool RegistrationModel::addPatient(patient& p, patient_medinfo_reg& data){
    std::size_t newIndex = this->patients.size();
    auto adr = std::get<4>(p);
    Patient newPatient{{std::get<0>(p), std::get<1>(p), newIndex, std::get<2>(p)},
                       std::make_tuple(std::get<0>(adr), std::get<1>(adr), std::get<2>(adr), std::get<3>(adr), std::get<4>(adr))};
    this->patients.push_back(newPatient);
    return true;
}

bool RegistrationModel::addPatientExam(patient_id& p, patient_exam_reg& data){
    // !!!
    std::size_t p_id = p, d_id = std::get<0>(data);
    std::size_t newIndex = this->pExams.size();
    PatientExamDate pe{newIndex, p_id, d_id, std::get<1>(data), std::get<2>(data), std::get<3>(data)};
    this->pExams.push_back(pe);
    return true;
}

bool RegistrationModel::deletePatient(patient_id& p_id){
    auto it = std::find_if(this->patients.begin(), this->patients.end(), [p_id](const Patient& p){
        return p.id == p_id;
    });
    if (it != this->patients.end()){
        this->patients.erase(it);
    }else{
        // error ...
    }
    return true;
}

bool RegistrationModel::deleteExam(exam_id& e_id){
    auto it = std::find_if(this->pExams.begin(), this->pExams.end(), [e_id](const PatientExamDate e){
        return e.exam_id == e_id;
    });
    if (it != this->pExams.end()){
        this->pExams.erase(it);
    }else{
        // error ...
    }
    return true;
}

bool RegistrationModel::editPatientExam(patient_id& p, patient_exam_reg& data, std::size_t e_id){
    std::size_t p_id = p, d_id = std::get<0>(data);
    auto it = std::find_if(this->pExams.begin(), this->pExams.end(), [e_id](const PatientExamDate& pe){
        return e_id == pe.exam_id;
    });
    if (it == this->pExams.end())
        return false;
    else{
        PatientExamDate& eexam = *it;
        eexam.patient_id = p;
        eexam.doctor_id = std::get<0>(data);
        eexam.date = std::get<1>(data);
        eexam.date_hour = std::get<2>(data);
        eexam.other_info = std::get<3>(data);
        
        return true;
    }
}

bool RegistrationModel::editPatient(patient& p, patient_medinfo_reg& data){
    auto p_id = std::get<2>(p);
    auto it = std::find_if(this->patients.begin(), this->patients.end(), [p_id](const Patient& p){
        return p_id == p.id;
    });
    if (it == this->patients.end())
        return false;
    else{
        patient_adr adr = std::get<4>(p);
        Patient& edit = *it;
        edit.name = std::get<0>(p);
        edit.lastname = std::get<1>(p);
        edit.pesel = std::get<2>(p);
        edit.address = {std::get<0>(adr), std::get<1>(adr), std::get<2>(adr), std::get<3>(adr), std::get<4>(adr)};
        return true;
    }
}
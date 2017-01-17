//
// Created by jm on 15.01.17.
//

#include "DoctorsModel.hpp"


void DoctorsModel::update_data() {
    this->update_patients();
    this->update_staff();
    this->update_pexams();
    this->update_pmedrecords();
    this->update_pprescriptions();
    this->update_pexamresults();
}


bool DoctorsModel::addPrescription(patient_id p_id, doctor_id d_id, date d, std::vector<patient_prescription_element>& pelem, std::string& other){
    std::size_t  newId = this->prescriptions.size();
    this->prescriptions.push_back({newId, p_id, d_id, d, pelem, other});
    return true;
}

bool DoctorsModel::addExam(patient_id p_id, doctor_id d_id, date d, patient_symptoms s, diagnosis diag, patient_medical_permit permit){
    std::size_t newId = this->examsResults.size();
    this->examsResults.push_back({newId, p_id, d_id, d, s, diag, permit});
    return true;
}

#include "Model.hpp"

Model::Model(VirtualController *vc) : vController{vc}, patients{},
                                      staff{}, pExams{}, pMedRecords{},
                                      adresses{}, prescriptions{}, examsResults{} {
    ;
}
Model::~Model() {
    ;
}

Person::~Person() {
    ;
}

patient Model::getPatient(patient_id& p_id) {
    auto it = std::find_if(this->patients.begin(), this->patients.end(), [p_id](const Patient& p){
        return p.id == p_id;
    });
    if (it != this->patients.end())
        return *it;
    else
        return {};
}

std::vector<patient> Model::getPatients(std::string& query) {
    if (query == "all"){
        return this->patients;
    }
    return {};
}

std::vector<doctor> Model::getDoctors(std::string& query){
    if (query == "all"){
        return this->staff;
    }else
        return {};
}

doctor Model::getDoctor(doctor_id& d_id){
    auto it = std::find_if(this->staff.doctors.begin(), this->staff.doctors.end(), [d_id](const Doctor& d){
        return d_id == d.id;
    });
    if (it != this->staff.doctors.end())
        return *it;
    else
        return {};
}

std::vector<exam> Model::getExams(std::string& query){
    if (query == "all")
        return this->pExams;
    else
        return {};
}

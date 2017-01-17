//
// Created by jm on 15.01.17.
//

#ifndef SYSMED_DOCTORSMODEL_HPP
#define SYSMED_DOCTORSMODEL_HPP

#include "Model.hpp"

class DoctorsModel : public Model{
public:
    using Model::Model;
    ~DoctorsModel() = default;
    
    bool addPrescription(patient_id, doctor_id, date, std::vector<patient_prescription_element>&, std::string&);
    bool addExam(patient_id, doctor_id, date, patient_symptoms, diagnosis, patient_medical_permit);
    
    virtual void update_data() override;
};


#endif //SYSMED_DOCTORSMODEL_HPP

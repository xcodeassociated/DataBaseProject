//
// Created by jm on 15.01.17.
//

#ifndef SYSMED_REGISTRATIONMODEL_HPP
#define SYSMED_REGISTRATIONMODEL_HPP

#include "Model.hpp"

class RegistrationModel : public Model {
public:
    using Model::Model;
    ~RegistrationModel() = default;
    
    bool addPatient(patient&, patient_medinfo_reg&);
    bool addPatientExam(patient_id&, patient_exam_reg&);
    bool editPatient(patient&, patient_medinfo_reg&);
    bool editPatientExam(patient_id&, patient_exam_reg&, std::size_t);
    bool deletePatient(patient_id&);
    bool deleteExam(exam_id&);
    
    virtual void update_data() override;
    
};

#endif //SYSMED_REGISTRATIONMODEL_HPP

#ifndef MODEL_H
#define MODEL_H

#include "VirtualController.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <utility>
#include <memory>

#include "Doctor.hpp"
#include "Patient.hpp"
#include "Person.hpp"
#include "Personel.hpp"
#include "Staff.hpp"

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using PatientsMedicalRecords = std::vector<PatientMedicalInfo>;
using PatientsPrescriptions = std::vector<PatientPrescription>;
using PatientsExamsResults = std::vector<PatientExamResult>;
using Persons_Adresses = std::vector<person_addess>;

class Model{
protected:
    VirtualController* vController = nullptr;
    Patients patients;
    Staff staff;
    PatientsExams pExams;
    PatientsMedicalRecords pMedRecords;
    Persons_Adresses adresses;
    PatientsPrescriptions prescriptions;
    PatientsExamsResults examsResults;
    
    static sql::Driver* driver;
    static sql::Connection* connection;
    static std::size_t arc;
    
public:
    
    std::string db_name = "SysMed";
    
    Model(VirtualController* vController);
    virtual ~Model();
    
    patient getPatient(patient_id&); // returns patient by id
    std::vector<patient> getPatients(std::string&); // returns patients by at last one patient data
    std::vector<doctor> getDoctors(std::string&);
    doctor getDoctor(doctor_id&);
    std::vector<exam> getExams(std::string&);
    PatientPrescription prescription;
    PatientExamResult examResults;
};

#endif // MODEL_H

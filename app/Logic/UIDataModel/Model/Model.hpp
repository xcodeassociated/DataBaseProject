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
#include <sstream>

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
#include <cppconn/prepared_statement.h>
#include <cppconn/datatype.h>

using PatientsMedicalRecords = std::vector<PatientMedicalInfo>;
using PatientsPrescriptions = std::vector<PatientPrescription>;
using PatientsExamsResults = std::vector<PatientExamResult>;

class Model{
protected:
    VirtualController* vController = nullptr;
    Patients patients;
    Staff staff;
    PatientsExams pExams;
    PatientsMedicalRecords pMedRecords;
    PatientsPrescriptions prescriptions;
    PatientsExamsResults examsResults;
    
    static sql::Driver* driver;
    static sql::Connection* connection;
    static std::size_t arc;
    
    struct DBInfo {
        const std::string db_name = "SysMed";
        const std::string address = "tcp://localhost:3306";
        const std::string log = "root";
        const std::string pass = "root";
    };
    
    DBInfo dbinfo;
    
    enum class OwnerType{
        None = 0,
        Staff = 1,
        Doctor = 2,
        Admin = 3
    };
    
    static Person owner;
    static OwnerType ownerType;
    
    virtual void update_data() = 0;
    void create_snapshot();
    void commit();
    void update_patients();
    void update_staff();
    void update_pexams();
    void update_pmedrecords();
    void update_pprescriptions();
    void update_pexamresults();
    
public:

    Model(VirtualController* vController) throw(sql::SQLException);
    virtual ~Model();
    
    patient getPatient(patient_id&); // returns patient by id
    std::vector<patient> getPatients(std::string&); // returns patients by at last one patient data
    patient_medinfo_reg getPatientMedInfo(patient_id&);
    std::vector<doctor> getDoctors(std::string&);
    doctor getDoctor(doctor_id&);
    std::vector<exam> getExams(std::string&);

};

#endif // MODEL_H

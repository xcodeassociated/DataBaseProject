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
    
    struct QueryParser {
        enum class QueryType {
            NONE = -1,
            NAME = 0,
            NAME_ONLY = 1,
            LASTNAME = 2,
            PESEL = 3
        };
        static std::pair<QueryType, std::string> parse(std::string);
    };
    
    using QType = QueryParser::QueryType;

    std::string parsePatientQueryOrder(PatientQueryOrder);

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
    
    std::string create_transaction();
    void commit_transaction();
    
    void update_patients();
    void update_patients(std::string&, PatientQueryOrder, QuerySort);
    void update_staff();
    void update_pexams();
    void update_pexams(std::string&, PExamsQueryOrder , QuerySort);
    void update_pmedrecords();
    void update_pprescriptions();
    void update_pexamresults();
    
public:

    Model(VirtualController* vController) throw(sql::SQLException);
    virtual ~Model();
    
    patient getPatient(patient_id&); // returns patient by id
    std::vector<patient> getPatients(std::string&, PatientQueryOrder, QuerySort); // returns patients by at last one patient data
    patient_medinfo_reg getPatientMedInfo(patient_id&);
    std::vector<doctor> getDoctors(std::string&);
    doctor getDoctor(doctor_id&);
    std::vector<exam> getExams(std::string&, PExamsQueryOrder , QuerySort);

};

#endif // MODEL_H

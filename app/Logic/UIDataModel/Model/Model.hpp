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

class Model {

    struct QueryParserPatient {
        enum class QueryTypePatient {
            NONE = -1,
            NAME = 0,
            NAME_ONLY = 1,
            LASTNAME = 2,
            PESEL = 3
        };

        static std::pair<QueryTypePatient, std::string> parse(std::string);

        static std::string parsePatientQueryOrder(PatientQueryOrder);
    };

    using QTypePatient = QueryParserPatient::QueryTypePatient;


    struct QueryParserExams {
        enum class QueryTypeExams {
            NONE = -1,
            PATIENT = 2,
            PATIENT_NAME_ONLY = 3,
            PATIENT_LASTNAME_ONLY = 4,
            PATIENT_PESEL = 5,
            DOCTOR = 6,
            DOCTOR_NAME_ONLY = 7,
            DOCTOR_LASTNAME_ONLY = 8
        };

        static std::pair<QueryTypeExams, std::string> parse(std::string);

        static std::string parsExamQueryOrderSearch(PExamsQueryOrder);
        static std::string parsExamQueryOrder(PExamsQueryOrder);

    };

    using QTypeExam = QueryParserExams::QueryTypeExams;

    struct QueryParserOperant {
        enum class QueryOperant {
            NONE = -1,
            AND = 1,
            OR = 2
        };

        static std::tuple<std::string, std::string, QueryOperant> parseQueryOperant(std::string);
    };

    using QOperant = QueryParserOperant::QueryOperant;

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
    
    void update_patients(PatientQueryOrder, QuerySort);
    void update_patients(std::string&, PatientQueryOrder, QuerySort);
    void update_staff();
    void update_pexams(PExamsQueryOrder , QuerySort);
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

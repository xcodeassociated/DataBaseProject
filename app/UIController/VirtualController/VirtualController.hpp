#ifndef VIRTUALCONTROLLER_H
#define VIRTUALCONTROLLER_H

#include <string>
#include <utility>
#include <tuple>
#include <string>
#include <vector>

#include <QListWidgetItem>
#include <QString>

enum class PermitType {
    NORMAL = 0,
    L4 = 1
};

enum class Window{
    PatientRegistrationWindow,
    DoctorsWindow,
    AdminWindow,
    None
};

enum class ReportType {
    TYPE1,
    TYPE2
};

enum class ReportFormat {
    PDF
};

enum class PatientQueryOrder {
    Id = 0,
    Name = 1,
    Lastname = 2,
    Pesel = 3
};

enum class PExamsQueryOrder {
    ID = 0,
    Patient = 1,
    Doctor = 2,
    Date = 3
};

enum class QuerySort {
    ASC = 0,
    DESC = 1
};

using patient_id = std::size_t;
using doctor_id = std::size_t;
using person_id = std::size_t;
using exam_id = std::size_t;
using date = std::string;
using diagnosis = std::string;
using pesel = std::size_t;
using patient_adr = std::tuple<std::string, std::string, std::string, std::string, std::string>;
using patient = std::tuple<std::string, std::string, std::size_t, pesel, patient_adr>;
using patient_med_record = std::tuple<std::string, std::string, std::string>;
using patient_medinfo_reg = std::vector<patient_med_record>;
using patient_exam_reg = std::tuple<doctor_id, std::string, std::string, std::string>;
using patient_symptoms = std::vector<std::pair<std::string, std::string>>;
using patient_medical_permit = std::tuple<PermitType, date, date>;
using patient_prescription_element = std::tuple<std::string, std::string, std::string>;
using person_addess = std::tuple<std::string, std::string, std::string, std::string, std::string>;
using doctor = std::tuple<std::string, std::string, std::size_t, std::string>;
using exam = std::tuple<patient_id, doctor_id, std::string, std::string, std::string, std::size_t>;

class QListWidgetItemBundle  : public QListWidgetItem{
public:
    using QListWidgetItem::QListWidgetItem;
    std::size_t id = 0;
};

class QStringBundel : public QString {
public:
    using QString::QString;
    std::size_t id = 0;
};

class VirtualController{
public:
    virtual void loginCheck(std::pair<std::string, std::string>&) = 0;
    virtual void loginInfo(bool, Window) = 0;
    virtual void showPatientRegistrationWindow() = 0;
    virtual void showDoctorsWindow() = 0;
    virtual void showAdminWindow() = 0;
    
    virtual patient getPatient(patient_id&) = 0; // returns patient by id
    virtual std::vector<patient> getPatients(std::string&, PatientQueryOrder, QuerySort) = 0; // returns patients by at last one patient data
    virtual patient_medinfo_reg getPatientMedInfo(patient_id&) = 0;
    virtual std::vector<doctor> getDoctors(std::string&) = 0;
    virtual doctor getDoctor(doctor_id&) = 0;
    virtual std::vector<exam> getExams(std::string&, PExamsQueryOrder, QuerySort) = 0;
    
    virtual bool addPatient(patient&, patient_medinfo_reg&) = 0;
    virtual bool addPatientExam(patient_id&, patient_exam_reg&) = 0;
    virtual bool editPatient(patient&, patient_medinfo_reg&) = 0;
    virtual bool editPatientExam(patient_id&, patient_exam_reg&, std::size_t) = 0;
    virtual bool deletePatient(patient_id&) = 0;
    virtual bool deleteExam(exam_id&) = 0;
    
    virtual bool addPrescription(patient_id, doctor_id, date, std::vector<patient_prescription_element>&, std::string&) = 0; // other_info - last string
    virtual bool addExam(patient_id, doctor_id, date, patient_symptoms, std::string, patient_medical_permit) = 0;
    
    virtual std::string generateReport(ReportType, std::pair<std::string, std::string>, ReportFormat) = 0;

};

#endif // VIRTUALCONTROLLER_H

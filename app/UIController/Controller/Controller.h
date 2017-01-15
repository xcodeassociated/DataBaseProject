#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "VirtualController.h"
#include "Model.h"
#include "LoginWindow.h"
#include "PatientRegistrationWindow.h"
#include "AdminWindow.h"
#include "DoctorsWindow.h"

#include <string>
#include <QString>
#include <iostream>
#include <cassert>

class Controller : public VirtualController{
    LoginModel* loginModel = nullptr;
    AdminModel* adminModel = nullptr;
    RegistrationModel* registrationModel = nullptr;
    DoctorsModel* doctorsModel = nullptr;
    
    LoginWindow* loginWindow = nullptr;
    PatientRegistrationWindow* pRegistrationWindow = nullptr;
    DoctorsWindow*  doctorsWindow = nullptr;
    AdminWindow*    adminWindow = nullptr;
    
    static std::size_t arc;

    Controller();
    
    Window current_window = Window::None;
    Model* genericModel = nullptr;
    
public:
    
    static Controller* instance();

    ~Controller();

    void showLogin();
    void failLogin();
    virtual void loginCheck(std::pair<std::string, std::string>&) override;
    virtual void loginInfo(bool, Window w) override;
    virtual void showPatientRegistrationWindow() override;
    virtual void showDoctorsWindow() override;
    virtual void showAdminWindow() override;
    
    virtual patient getPatient(patient_id&) override; // returns patient by id
    virtual std::vector<patient> getPatients(std::string&) override; // returns patients by at last one patient data
    virtual std::vector<doctor> getDoctors(std::string&) override;
    virtual doctor getDoctor(doctor_id&) override;
    virtual std::vector<exam> getExams(std::string&) override;
    
    virtual bool addPatient(patient&, patient_medinfo_reg&) override;
    virtual bool addPatientExam(patient_id&, patient_exam_reg&) override;
    virtual bool editPatient(patient&, patient_medinfo_reg&) override;
    virtual bool editPatientExam(patient_id&, patient_exam_reg&, std::size_t) override;
    virtual bool deletePatient(patient_id&) override;
    virtual bool deleteExam(exam_id&) override;
    
    virtual bool addPrescription(patient_id, doctor_id, date, std::vector<patient_prescription_element>&, std::string&) override;
    virtual bool addExam(patient_id, doctor_id, date, patient_symptoms, std::string, patient_medical_permit) override;
    
    virtual std::string generateReport(ReportType, std::pair<std::string, std::string>, ReportFormat) override;
    
};

#endif // CONTROLLER_H

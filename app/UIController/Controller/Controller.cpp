#include "Controller.h"

Controller::Controller(){
    std::cout << "Controller Contructor" << std::endl;
    this->loginModel = new LoginModel(static_cast<VirtualController*>(this));
    this->loginWindow = new LoginWindow;
    this->loginWindow->setController(static_cast<VirtualController*>(this));
}

Controller* Controller::instance(){
    Controller::arc++;
    static Controller* instance_ptr = new Controller();
    return instance_ptr;
}

Controller::~Controller(){
    if (Controller::arc == 0){
        //clean up code...
    }else
        Controller::arc--;
}

void Controller::showLogin() {
    this->loginWindow->show();
}

void Controller::loginCheck(std::pair<std::string, std::string>& data) {
    this->loginModel->checkLoginData(data);
}

void Controller::loginInfo(bool result, Window w) {
    if (result){
        switch (w){
            case Window::PatientRegistrationWindow:
                this->showPatientRegistrationWindow();
                break;
            case Window::DoctorsWindow:
                this->showDoctorsWindow();
                break;
            case Window::AdminWindow:
                this->showAdminWindow();
                break;
            default:
                break;
        }
    }else{
        this->failLogin();
    }
        
}

void Controller::failLogin() {
    this->loginWindow->loginFailed();
}

void Controller::showPatientRegistrationWindow() {
    this->pRegistrationWindow = new PatientRegistrationWindow();
    this->pRegistrationWindow->setController(this);
    
    this->registrationModel = new RegistrationModel(this);
    this->current_window = Window::PatientRegistrationWindow;
    this->genericModel = this->registrationModel;
    
    this->loginWindow->close();
    this->pRegistrationWindow->show();
    this->pRegistrationWindow->setup_view();
}

void Controller::showDoctorsWindow() {
    this->doctorsWindow = new DoctorsWindow();
    this->doctorsWindow->setController(this);
    
    this->doctorsModel = new DoctorsModel(this);
    this->current_window = Window::DoctorsWindow;
    this->genericModel = this->doctorsModel;
    
    this->loginWindow->close();
    this->doctorsWindow->show();
    this->doctorsWindow->setup_view();
}

void Controller::showAdminWindow() {
    this->adminWindow = new AdminWindow();
    this->adminWindow->setController(this);
    
    this->adminModel = new AdminModel(this);
    this->current_window = Window::AdminWindow;
    this->genericModel = this->adminModel;
    
    this->loginWindow->close();
    this->adminWindow->show();
    this->adminWindow->setup_view();
}

patient Controller::getPatient(patient_id& p_id) {
    assert(this->genericModel != nullptr);
    return this->genericModel->getPatient(p_id);
}

std::vector<patient> Controller::getPatients(std::string& query) {
    assert(this->genericModel != nullptr);
    return this->genericModel->getPatients(query);
}

std::vector<doctor> Controller::getDoctors(std::string& query){
    assert(this->genericModel != nullptr);
    return this->genericModel->getDoctors(query);
}

doctor Controller::getDoctor(doctor_id& d_id){
    assert(this->genericModel != nullptr);
    return this->genericModel->getDoctor(d_id);
}

std::vector<exam> Controller::getExams(std::string& query){
    assert(this->genericModel != nullptr);
    return this->genericModel->getExams(query);
}

bool Controller::addPatient(patient& p, patient_medinfo_reg& data) {
    assert(this->current_window == Window::PatientRegistrationWindow);
    return this->registrationModel->addPatient(p, data);
}

bool Controller::addPatientExam(patient_id& p, patient_exam_reg& data) {
    assert(this->current_window == Window::PatientRegistrationWindow);
    return this->registrationModel->addPatientExam(p, data);
}

bool Controller::deletePatient(patient_id& p_id){
    assert(this->current_window == Window::PatientRegistrationWindow);
    return this->registrationModel->deletePatient(p_id);
}

bool Controller::deleteExam(exam_id& e_id){
    assert(this->current_window == Window::PatientRegistrationWindow);
    return this->registrationModel->deleteExam(e_id);
}

bool Controller::editPatient(patient& p, patient_medinfo_reg& data) {
    assert(this->current_window == Window::PatientRegistrationWindow);
    return this->registrationModel->editPatient(p, data);
}

bool Controller::editPatientExam(patient_id& p_id, patient_exam_reg& data, std::size_t e_id){
    assert(this->current_window == Window::PatientRegistrationWindow);
    return this->registrationModel->editPatientExam(p_id, data, e_id);
}

bool Controller::addPrescription(patient_id p_id, doctor_id d_id, date d, std::vector<patient_prescription_element>& elems, std::string& other) {
    assert(this->current_window == Window::DoctorsWindow);
    return this->doctorsModel->addPrescription(p_id, d_id, d, elems, other);
}
bool Controller::addExam(patient_id p_id, doctor_id d_id, date d, patient_symptoms symptoms, std::string diag, patient_medical_permit permit) {
    assert(this->current_window == Window::DoctorsWindow);
    return this->doctorsModel->addExam(p_id, d_id, d, symptoms, diag, permit);
}

std::string Controller::generateReport(ReportType rtype, std::pair<std::string, std::string> time_peroid, ReportFormat rformat) {
    assert(this->current_window == Window::AdminWindow);
    return this->adminModel->generateReport(rtype, time_peroid, rformat);
}

std::size_t Controller::arc = 0;

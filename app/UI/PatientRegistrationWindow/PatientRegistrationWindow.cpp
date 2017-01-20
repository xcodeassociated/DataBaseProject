#include "PatientRegistrationWindow.hpp"
#include "ui_PatientRegistrationWindow.h"

PatientRegistrationWindow::PatientRegistrationWindow(QWidget *parent) :
    QDialog(parent), patients{}, patienListElements{}, doctors{}, exams{}, pSelects{}, dSelect{},
    ui(new Ui::PatientRegistrationWindow)
{
    ui->setupUi(this);
    
    this->currentTab = static_cast<CurrentTab>(this->ui->tabWidget->currentIndex());
    connect(this->ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabChange()));
    
    connect(this->ui->patientList, SIGNAL(itemSelectionChanged()), this, SLOT(selectPatientInList()));
    
    connect(this->ui->searchField, SIGNAL(textChanged(const QString &)), this, SLOT(searchFieldChanged(const QString &)));
    
    connect(this->ui->addMedRow, SIGNAL(clicked()), this, SLOT(addNewMedInfoRow()));
    connect(this->ui->removeMedRow, SIGNAL(clicked()), this, SLOT(removeMedInfoRow()));
    connect(this->ui->patientAccept, SIGNAL(clicked()), this, SLOT(addPatientToSystem()));
    connect(this->ui->patientClear, SIGNAL(clicked()), this, SLOT(cleanPatientRegUi()));
    connect(this->ui->visitAccept, SIGNAL(clicked()), this, SLOT(addExamToSystem()));
    connect(this->ui->visitClear, SIGNAL(clicked()), this, SLOT(cleanExamRegUI()));
    connect(this->ui->editAccept, SIGNAL(clicked()), this, SLOT(editPatientInSystem()));
    connect(this->ui->editClear, SIGNAL(clicked()), this, SLOT(cleanEditPatientUI()));
    connect(this->ui->addMedRowEdit, SIGNAL(clicked()), this, SLOT(addNewEditMedRow()));
    connect(this->ui->removeRowEdit, SIGNAL(clicked()), this, SLOT(removeEditMedRow()));
    connect(this->ui->visitAccept_2, SIGNAL(clicked()), this, SLOT(editExamInSystem()));
    connect(this->ui->visitClear_2, SIGNAL(clicked()), this, SLOT(cleanExamEditUI()));
    connect(this->ui->removePatientButton, SIGNAL(clicked()), this, SLOT(deletePatient()));
    connect(this->ui->removeExamButton, SIGNAL(clicked()), this, SLOT(deleteExam()));

    connect(this->ui->sortByCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(sortByChanged(int)));
    connect(this->ui->DESC, SIGNAL(clicked()), this, SLOT(radioBChanged()));
    connect(this->ui->ASC, SIGNAL(clicked()), this, SLOT(radioBChanged()));

}

PatientRegistrationWindow::~PatientRegistrationWindow()
{
    delete ui;
}

void PatientRegistrationWindow::updateDoctors(){
    std::string doctors_query = "all";
    this->doctors = this->vc->getDoctors(doctors_query);
}


void PatientRegistrationWindow::tabChange(){
    this->currentTab = static_cast<CurrentTab>(this->ui->tabWidget->currentIndex());
    
    this->setup_view();
}

void PatientRegistrationWindow::addPatientToSystem() {
    assert(this->currentTab == CurrentTab::P_REG_TAB);
    
    std::cerr << "Add patient {" << "\n";
    
    if (this->ui->nameInput->text().toStdString().empty() ||
        this->ui->surnameInput->text().toStdString().empty() ||
        this->ui->PESELInput->text().toStdString().empty() ||
        this->ui->locationInput->text().toStdString().empty() ||
        this->ui->streetInput->text().toStdString().empty() ||
        this->ui->houseNumberInput->text().toStdString().empty() ||
        this->ui->postalCodeInput->text().toStdString().empty()) {
        
        QMessageBox::information(this, "Niepoprawne dane", {"Proszę wypełnić wszystkie pola tesktowe formularza."});
        
        std::cerr << "incomplete data!" << "\n";
        return;
    }
    patient p;
    std::string name = this->ui->nameInput->text().toStdString(),
            lastname = this->ui->surnameInput->text().toStdString(),
            city = this->ui->locationInput->text().toStdString(),
            street = this->ui->streetInput->text().toStdString(),
            houseNR = this->ui->houseNumberInput->text().toStdString(),
            flatNR = this->ui->flatNumberInput->text().toStdString(),
            postl = this->ui->postalCodeInput->text().toStdString();
    
    std::stringstream sstream(this->ui->PESELInput->text().toStdString());
    std::size_t pesel;
    sstream >> pesel;
    p = std::make_tuple(name, lastname, 0, pesel, std::make_tuple(city, street, houseNR, flatNR, postl));
    
    std::cerr << "  * name: " << name << "\n";
    std::cerr << "  * lastname: " << lastname << "\n";
    std::cerr << "  * pesel: " << pesel << "\n";
    std::cerr << "  * Med info: " << "\n";
    
    patient_medinfo_reg medInfo{};
    for (int row = 0; row < this->ui->medicTable->rowCount(); row++) {
        std::vector<std::string> rec(this->ui->medicTable->columnCount());
        for (int col = 0; col < this->ui->medicTable->columnCount(); col++) {
            if (this->ui->medicTable->item(row, col)) {
                rec[col] = (this->ui->medicTable->item(row, col)->text().toStdString());
            }
        }
        std::cerr << "      " << rec[0] << " " << rec[1] << " " << rec[2] << "\n";
        medInfo.push_back(std::make_tuple(rec[0], rec[1], rec[2]));
    }
    
    std::cerr << "}" << "\n";
    
    if (this->vc->addPatient(p, medInfo)){
        std::stringstream msg;
        msg << "Dodano pacjenta: " << name << " " << lastname << "\n";
        QMessageBox::information(this, "Informacja", {msg.str().c_str()});
        this->ui->listWidget->addItem({msg.str().c_str()});
    
        this->setup_view();
        
            std::cerr << "Patient added!" << "\n";
    }else{
        std::cerr << "Error in adding patient!" << "\n";
    }
}

void PatientRegistrationWindow::cleanPatientRegUi(){
    assert(this->currentTab == CurrentTab::P_REG_TAB);
    
    this->ui->nameInput->clear();
    this->ui->surnameInput->clear();
    this->ui->PESELInput->clear();
    this->ui->locationInput->clear();
    this->ui->streetInput->clear();
    this->ui->houseNumberInput->clear();
    this->ui->flatNumberInput->clear();
    this->ui->postalCodeInput->clear();
    this->ui->medicTable->clear();
    this->ui->medicTable->setHorizontalHeaderLabels({"Data", "Choroba", "Inne"});
    
    this->current_editing_exam = -1;
    this->current_editing_patient = -1;
}

void PatientRegistrationWindow::addExamToSystem(){
    std::cerr << "1\n";
    auto pSelIndex = this->ui->selectPatient->currentIndex();
    auto dSelIndex = this->ui->selectDoctor->currentIndex();
    
    std::size_t p_id = std::get<2>(this->patients[pSelIndex]);
    std::size_t d_id = std::get<2>(this->doctors[dSelIndex]);
 
    std::cerr << "patient: " << std::get<0>(this->patients[pSelIndex]) << " " << std::get<1>(this->patients[pSelIndex]) << " index: " << p_id << "\n";
    std::cerr << "doctor: " << std::get<0>(this->doctors[dSelIndex]) << " " << std::get<1>(this->doctors[dSelIndex]) <<" index: " << d_id << "\n";
    
    std::string date, time;
    date = this->ui->dateEdit->date().toString("yyyy-MM-dd").toStdString();
    time = this->ui->timeEdit->time().toString("HH:mm:ss").toStdString();
    
    std::cerr << "date: " << date << " time: " << time;
    patient_exam_reg e = std::make_tuple(d_id, date, time, this->ui->visiOther->toPlainText().toStdString());
    
    if (this->vc->addPatientExam(p_id, e)){
        this->setup_view();
        std::stringstream msg;
        msg << "Zarejestrowano: " << std::get<0>(this->patients[pSelIndex]) << " " << std::get<1>(this->patients[pSelIndex]) << "\n"
            << "   do doktora: " << std::get<0>(this->doctors[dSelIndex]) << " " << std::get<1>(this->doctors[dSelIndex]) << "\n";
        this->ui->listWidget->addItem({msg.str().c_str()});
        
        QMessageBox::information(this, "Informacja", {msg.str().c_str()});
    }
}

void PatientRegistrationWindow::cleanExamRegUI(){
    this->ui->visiOther->clear();
    this->ui->dateEdit->setDate(QDate::currentDate());
    this->ui->timeEdit->setTime(QTime::currentTime());
}

void PatientRegistrationWindow::editPatientInSystem(){
    this->ui->patientList->clearSelection();
    
    if (this->ui->nameEdit->text().toStdString().empty() ||
        this->ui->surnameEdit->text().toStdString().empty() ||
        this->ui->PESELEdit->text().toStdString().empty() ||
        this->ui->locationEdit->text().toStdString().empty() ||
        this->ui->streetEdit->text().toStdString().empty() ||
        this->ui->houseNumberEdit->text().toStdString().empty() ||
        this->ui->postalCodeEdit->text().toStdString().empty()) {
        QMessageBox::information(this, "Niepoprawne dane", {"Proszę wypełnić wszystkie pola tesktowe formularza."});
        std::cerr << "incomplete data!" << "\n";
        return;
    }
    
    if (this->current_editing_patient == -1){
        QMessageBox::information(this, "Niepoprawne dane", {"Proszę wybrać pacjenta!"});
        return;
    }
    
    std::string name = this->ui->nameEdit->text().toStdString(),
            lastname = this->ui->surnameEdit->text().toStdString(),
            city = this->ui->locationEdit->text().toStdString(),
            street = this->ui->streetEdit->text().toStdString(),
            houseNR = this->ui->houseNumberEdit->text().toStdString(),
            flatNR = this->ui->flatNumberEdit->text().toStdString(),
            postl = this->ui->postalCodeEdit->text().toStdString();
    
    std::stringstream sstream(this->ui->PESELEdit->text().toStdString());
    std::size_t pesel;
    sstream >> pesel;
    
    patient_medinfo_reg medInfo{};
    for (int row = 0; row < this->ui->medicTableEdit->rowCount(); row++) {
        std::vector<std::string> rec(this->ui->medicTableEdit->columnCount());
        for (int col = 0; col < this->ui->medicTableEdit->columnCount(); col++) {
            if (this->ui->medicTableEdit->item(row, col)) {
                rec[col] = (this->ui->medicTableEdit->item(row, col)->text().toStdString());
            }
        }
        medInfo.push_back(std::make_tuple(rec[0], rec[1], rec[2]));
    }
    patient p;
    p = std::make_tuple(name, lastname, this->current_editing_patient, pesel,
                         std::make_tuple(city, street, houseNR, flatNR, postl));
    
    std::stringstream msg, msg_h;
    msg << "Zmodyfikować dane pacjenta: " << this->ui->nameEdit->text().toStdString() << " " << this->ui->surnameEdit->text().toStdString() << "?";
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Edycja Danych Pacjenta", {msg.str().c_str()}, QMessageBox::Yes|QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        if (this->vc->editPatient(p, medInfo)) {
            msg_h << "Zmodyfikowano dane pacjenta: " << this->ui->nameEdit->text().toStdString() << " " << this->ui->surnameEdit->text().toStdString() << "\n";
            this->ui->listWidget->addItem({msg_h.str().c_str()});
            this->current_editing_patient = -1;
            
            this->setup_view();
        } else {
            std::cerr << "error in patient edit!" << "\n";
        }
    }
}

void PatientRegistrationWindow::deletePatient(){
    if (this->current_editing_patient != -1){
        patient p = this->vc->getPatient(this->current_editing_patient);
        std::string name = std::get<0>(p), lastname = std::get<1>(p);
        std::stringstream msg;
        msg << "Czy usunąć pacjenta: " << name << " " << lastname << "?";
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Potwierdzenie", {msg.str().c_str()}, QMessageBox::Yes|QMessageBox::No);
        
        if (reply == QMessageBox::Yes) {
            if (this->vc->deletePatient(this->current_editing_patient)) {
                std::stringstream msg_h;
                msg_h << "Usunięto pacjenta: " << name << " " << lastname << "\n";
                this->ui->listWidget->addItem({msg_h.str().c_str()});
                this->current_editing_patient = -1;
                
                this->setup_view();
            }else{
                // ...
            }
        }
    }else{
        QMessageBox::information(this, "Niepoprawne dane", {"Proszę wybrać pacjenta!"});
    }
}

void PatientRegistrationWindow::deleteExam(){
    if (this->current_editing_exam != -1) {
        auto it = std::find_if(this->exams.begin(), this->exams.end(), [this](const exam& e){
            return this->current_editing_exam == std::get<5>(e);
        });
        if (it != this->exams.end()) {
            patient p = this->vc->getPatient(std::get<0>(*it));
            std::string p_name = std::get<0>(p);
            std::stringstream msg;
            msg << "Czy chces usunać wizytę pacjenta: " << p_name << "?";
            QMessageBox::StandardButton reply = QMessageBox::question(this, "Potwierdzenie", {msg.str().c_str()}, QMessageBox::Yes|QMessageBox::No);
    
            if (reply == QMessageBox::Yes) {
                if (this->vc->deleteExam(this->current_editing_exam)) {
                    std::stringstream msg_h;
                    msg_h << "Usunięto wizytę pacjenta: " << p_name << "\n";
                    this->ui->listWidget->addItem({msg_h.str().c_str()});
                    this->current_editing_exam = -1;
                    
                    this->setup_view();
                } else {
                    // ...
                }
            }
        }else{
            // ..
        }
    }else{
        QMessageBox::information(this, "Niepoprawne dane", {"Proszę wybrać wizytę!"});
    }
}


void PatientRegistrationWindow::cleanEditPatientUI(){
    this->ui->patientList->clearSelection();
    this->ui->nameEdit->clear();
    this->ui->surnameEdit->clear();
    this->ui->locationEdit->clear();
    this->ui->streetEdit->clear();
    this->ui->houseNumberEdit->clear();
    this->ui->flatNumberEdit->clear();
    this->ui->postalCodeEdit->clear();
    
    this->ui->medicTableEdit->clear();
    this->ui->medicTableEdit->setHorizontalHeaderLabels({"Data", "Choroba", "Inne"});
    
    this->current_editing_exam = -1;
    this->current_editing_patient = -1;
}
void PatientRegistrationWindow::addNewMedInfoRow(){
    this->ui->medicTable->insertRow(this->ui->medicTable->rowCount());
}

void PatientRegistrationWindow::removeMedInfoRow(){
    if (this->ui->medicTable->rowCount() > 1)
        this->ui->medicTable->removeRow(this->ui->medicTable->rowCount() - 1 );
}

void PatientRegistrationWindow::addNewEditMedRow(){
    this->ui->medicTableEdit->insertRow(this->ui->medicTableEdit->rowCount());
}

void PatientRegistrationWindow::removeEditMedRow(){
    if (this->ui->medicTableEdit->rowCount() > 1)
        this->ui->medicTableEdit->removeRow(this->ui->medicTableEdit->rowCount() - 1 );
}

void PatientRegistrationWindow::editExamInSystem(){
    this->ui->patientList->clearSelection();
    
    if (this->current_editing_exam == -1){
        QMessageBox::information(this, "Niepoprawne dane", {"Proszę wybrać wizytę!"});
        return;
    }
        
    auto pSelIndex = this->ui->selectPatient_2->currentIndex();
    auto dSelIndex = this->ui->selectDoctor_2->currentIndex();
    
    std::size_t p_id = std::get<2>(this->patients[pSelIndex]);
    std::size_t d_id = std::get<2>(this->doctors[dSelIndex]);
    
    std::cerr << "patient: " << std::get<0>(this->patients[pSelIndex]) << " " << std::get<1>(this->patients[pSelIndex]) << " index: " << p_id << "\n";
    std::cerr << "doctor: " << std::get<0>(this->doctors[dSelIndex]) << " " << std::get<1>(this->doctors[dSelIndex])<<" index: " << d_id << "\n";
    
    std::string date, time;
    date = this->ui->dateEdit_2->date().toString("dd.MM.yyyy").toStdString();
    time = this->ui->timeEdit_2->time().toString("HH.mm").toStdString();
    
    std::cerr << "date: " << date << " time: " << time;
    patient_exam_reg e = std::make_tuple(d_id, date, time, this->ui->visiOther_2->toPlainText().toStdString());
    
    std::stringstream msg, msg_h;
    msg << "Dokonać edycji terminu wizyty pacjenta: " << std::get<0>(this->patients[pSelIndex]) << " " << std::get<1>(this->patients[pSelIndex]) << "?";
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Edycja badania", {msg.str().c_str()}, QMessageBox::Yes|QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        if (this->vc->editPatientExam(p_id, e, this->current_editing_exam)) {
            msg_h << "Dokonano edycji terminu wizyty pacjenta: " << std::get<0>(this->patients[pSelIndex]) << " " << std::get<1>(this->patients[pSelIndex]) << "\n";
            this->ui->listWidget->addItem({msg_h.str().c_str()});
            this->current_editing_exam = -1;
            
            this->setup_view();
        } else {
            std::cerr << "error in editing exam" << this->current_editing_exam << "\n";
        }
    }
}

void PatientRegistrationWindow::cleanExamEditUI(){
    this->ui->patientList->clearSelection();
    this->ui->visiOther_2->clear();
    this->ui->dateEdit_2->setDate(QDate::currentDate());
    this->ui->timeEdit_2->setTime(QTime::currentTime());
    
    this->current_editing_exam = -1;
    this->current_editing_patient = -1;
}

void PatientRegistrationWindow::selectPatientInList(){
    if( this->ui->patientList->selectedItems().empty())
        return;
    
    if (this->currentTab == CurrentTab::P_EDIT_TAB) {
        QListWidgetItemBundle *selected_item = static_cast<QListWidgetItemBundle *>(this->ui->patientList->selectedItems().back());
        auto patient_id = selected_item->id;
        std::cerr << "selected: " << selected_item->text().toStdString() << " id: " << patient_id << "\n";
        this->current_editing_patient = patient_id;
        patient selected_patient = this->vc->getPatient(patient_id);
        
        this->ui->nameEdit->setText({std::get<0>(selected_patient).c_str()});
        this->ui->surnameEdit->setText({std::get<1>(selected_patient).c_str()});
        this->ui->PESELEdit->setText({std::to_string(std::get<3>(selected_patient)).c_str()});
        this->ui->locationEdit->setText({std::get<0>(std::get<4>(selected_patient)).c_str()});
        this->ui->streetEdit->setText(std::get<1>(std::get<4>(selected_patient)).c_str());
        this->ui->houseNumberEdit->setText(std::get<2>(std::get<4>(selected_patient)).c_str());
        this->ui->flatNumberEdit->setText(std::get<3>(std::get<4>(selected_patient)).c_str());
        this->ui->postalCodeEdit->setText(std::get<4>(std::get<4>(selected_patient)).c_str());
        
        patient_medinfo_reg medinfo = this->vc->getPatientMedInfo(patient_id);
        std::cerr << "medinfo count: " << medinfo.size() << "\n";
        this->ui->medicTableEdit->setRowCount(medinfo.size());
        
        int i = 0;
        for (patient_med_record& elem : medinfo){
            std::vector<std::string> text{};
            
            text.push_back(std::get<0>(elem));
            text.push_back(std::get<1>(elem));
            text.push_back(std::get<2>(elem));
            
            for (int j = 0; j < 3; j++){
                //i hope that clear in tablewidget delets heap memory for items
                QTableWidgetItem *newItem = new QTableWidgetItem(text[j].c_str());
                this->ui->medicTableEdit->setItem(i, j, newItem);
            }
            i++;
        }
        
    }else if (this->currentTab == CurrentTab::E_EDIT_TAB){
        QListWidgetItemBundle *selected_item = static_cast<QListWidgetItemBundle *>(this->ui->patientList->selectedItems().back());
        auto exam_id = selected_item->id;
        std::cerr << "exam id: " << exam_id << "\n";
        this->current_editing_exam = exam_id;
        
        const exam& e = *std::find_if(this->exams.begin(), this->exams.end(), [exam_id](const exam& elem){
            return std::get<5>(elem) == exam_id;
        });
        
        this->ui->visiOther_2->document()->setPlainText({std::get<4>(e).c_str()});
    }
}

void PatientRegistrationWindow::radioBChanged(){
    this->searchFieldChanged(this->ui->searchField->text());
}

void PatientRegistrationWindow::sortByChanged(int index){
    this->searchFieldChanged(this->ui->searchField->text());
}

void PatientRegistrationWindow::searchFieldChanged(const QString& text){
    auto sb = this->ui->sortByCombo->currentText().toStdString();
    bool desc = this->ui->DESC->isChecked();
    QuerySort qs = (desc) ? QuerySort::DESC : QuerySort::ASC;


    std::cerr << "Search filed changed: " << text.toStdString() << " sb: " << sb << " desc: " << desc << "\n";

    if (this->currentTab == CurrentTab::P_REG_TAB || this->currentTab == CurrentTab::P_EDIT_TAB) {
        PatientQueryOrder pqo;

        if (sb == "imie")
            pqo = PatientQueryOrder::Name;
        else if (sb == "nazwisko")
            pqo = PatientQueryOrder::Lastname;
        else if (sb == "pesel")
            pqo = PatientQueryOrder::Pesel;

        this->cleanLeftList();

        this->updatePatients(text.toStdString(), pqo, qs);

        this->fillPatientsList();
    }else{
        PExamsQueryOrder peqo;

        if (sb == "pacjent")
            peqo = PExamsQueryOrder::Patient;
        else if (sb == "lekarz")
            peqo = PExamsQueryOrder::Doctor;
        else if (sb == "termin")
            peqo = PExamsQueryOrder::Date;

        this->cleanLeftList();

        this->updateExams(text.toStdString(), peqo, qs);

        this->fillExamsList();
    }
}


bool PatientRegistrationWindow::setController(VirtualController* vc){
    if (vc != nullptr){
        this->vc = vc;
        return true;
    }else
        return false;
}

void PatientRegistrationWindow::cleanLeftList(){
    this->ui->patientList->clearSelection();
    
    if (this->ui->patientList->count() > 0){
        while (this->patienListElements.size() > 0) {
            this->ui->patientList->takeItem(0);
            delete this->patienListElements.back();
            this->patienListElements.pop_back();
        }
        while (this->ui->patientList->count() > 0) {
            this->ui->patientList->takeItem(0);
        }
        assert(this->patienListElements.empty() && this->ui->patientList->count() == 0);
    }
}

void PatientRegistrationWindow::cleanSelectors(){
    this->ui->selectPatient->clear();
    this->ui->selectDoctor->clear();
    this->ui->selectPatient_2->clear();
    this->ui->selectDoctor_2->clear();
    this->ui->sortByCombo->clear();
}

void PatientRegistrationWindow::updatePatients(){
    std::string query = "all";
    this->patients = this->vc->getPatients(query, PatientQueryOrder::Name, QuerySort::ASC);
}

void PatientRegistrationWindow::updatePatients(std::string query, PatientQueryOrder pqo, QuerySort qs){
    this->patients = this->vc->getPatients(query, pqo, qs);
}

void PatientRegistrationWindow::updateExams(){
    std::string query = "all";
    this->exams = this->vc->getExams(query, PExamsQueryOrder::ID, QuerySort::ASC);
}

void PatientRegistrationWindow::updateExams(std::string query, PExamsQueryOrder peq, QuerySort qs){
    this->exams = this->vc->getExams(query, peq, qs);
}

void PatientRegistrationWindow::fillPatientsList() {
    
    if (!this->patients.empty()){
        for (auto e : this->patients){
            std::string p = std::get<0>(e) + " " + std::get<1>(e);
            QListWidgetItemBundle* item = new QListWidgetItemBundle;
            item->id = std::get<2>(e);
            item->setText(QString(p.c_str()));
            this->ui->patientList->addItem(item);
            this->patienListElements.push_back(item);
        }
    }else{
        std::cerr << "empty patients!" << "\n";
    }
}

void PatientRegistrationWindow::fillExamsList(){
    if (!this->exams.empty()){
        for (auto e : this->exams){
            patient p = this->vc->getPatient(std::get<0>(e));
            doctor_id d_id = std::get<1>(e);
            doctor d = this->vc->getDoctor(d_id);
            std::string p_str = std::get<0>(p) + " " + std::get<1>(p) + " -> " + std::get<0>(d) + " " + std::get<1>(d);
            QListWidgetItemBundle* item = new QListWidgetItemBundle;
            item->id = std::get<5>(e); //exam id
            item->setText(QString(p_str.c_str()));
            this->ui->patientList->addItem(item);
            this->examListElements.push_back(item);
        }
    }else
        std::cerr << "empty exams!" << "\n";
}

void PatientRegistrationWindow::fillEditMedInfoTable(){
    
}

void PatientRegistrationWindow::setup_view() {
    this->cleanSelectors();
    this->cleanLeftList();
    this->pSelects.clear();
    this->dSelect.clear();
    
    switch (this->currentTab) {
        case CurrentTab::P_REG_TAB:
            this->ui->patientList->setEnabled(true);
            this->ui->infoBox->setText({"Pacjent:"});
            this->cleanPatientRegUi();
            this->updatePatients();
            this->fillPatientsList();

            for (const auto& s : psortby)
                this->ui->sortByCombo->addItem({s.c_str()});

            break;
            
        case CurrentTab::E_REG_TAB:
            std::cerr << "Tab changed to E_REG_TAB" << "\n";
            
            this->ui->patientList->setEnabled(true);
            this->ui->infoBox->setText({"Wizyta:"});
            this->cleanExamRegUI();
            this->updatePatients();
            this->updateDoctors();
            this->updateExams();
            this->fillExamsList();
            
            assert(!this->patients.empty());
            assert(!this->doctors.empty());
        
            for (patient p : this->patients) {
                std::string pItem = std::get<0>(p) + " " + std::get<1>(p);
                QStringBundel e = QStringBundel(pItem.c_str());
                e.id = std::get<2>(p);
                this->ui->selectPatient->addItem(e);
                this->pSelects.push_back(e);
            }
            
            for (doctor d : this->doctors){
                std::string dItem = std::get<0>(d) + " " + std::get<1>(d);
                QStringBundel e = QStringBundel(dItem.c_str());
                e.id = std::get<2>(d);
                this->ui->selectDoctor->addItem(e);
                this->dSelect.push_back(e);
            }

            for (const auto& s : esortby)
                this->ui->sortByCombo->addItem({s.c_str()});

            break;
    
        case CurrentTab::P_EDIT_TAB:
            this->ui->patientList->setEnabled(true);
            this->ui->infoBox->setText({"Pacjent:"});
            this->cleanEditPatientUI();
            this->updatePatients();
            this->fillPatientsList();

            this->fillEditMedInfoTable();

            for (const auto& s : psortby)
                this->ui->sortByCombo->addItem({s.c_str()});

            break;
    
        case CurrentTab::E_EDIT_TAB:
            this->ui->patientList->setEnabled(true);
            this->ui->infoBox->setText({"Wizyta:"});
            this->cleanExamEditUI();
            this->updatePatients();
            this->updateDoctors();
            this->updateExams();
            this->fillExamsList();
        
            for (patient p : this->patients) {
                std::string pItem = std::get<0>(p) + " " + std::get<1>(p);
                QStringBundel e = QStringBundel(pItem.c_str());
                e.id = std::get<2>(p);
                this->ui->selectPatient_2->addItem(e);
                this->pSelects.push_back(e);
            }
        
            for (doctor d : this->doctors){
                std::string dItem = std::get<0>(d) + " " + std::get<1>(d);
                QStringBundel e = QStringBundel(dItem.c_str());
                e.id = std::get<2>(d);
                this->ui->selectDoctor_2->addItem(e);
                this->dSelect.push_back(e);
            }

            for (const auto& s : esortby)
                this->ui->sortByCombo->addItem({s.c_str()});

            break;
    }
}
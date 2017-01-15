#include "DoctorsWindow.hpp"
#include "ui_DoctorsWindow.h"

DoctorsWindow::DoctorsWindow(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DoctorsWindow)
{
	ui->setupUi(this);
  
    this->currentTab = static_cast<CurrentTab>(this->ui->tabWidget->currentIndex());
	connect(this->ui->patientAccept, SIGNAL(clicked()), this, SLOT(doneExamination()));
	connect(this->ui->generateL4cb, SIGNAL(clicked()), this, SLOT(toggleL4()));
	connect(this->ui->prescriptionCreate, SIGNAL(clicked()), this, SLOT(generatePrescription()));
	connect(this->ui->prescriptionClear, SIGNAL(clicked()), this, SLOT(clearPrescription()));
	connect(this->ui->patientClear, SIGNAL(clicked()), this, SLOT(clearExamination()));
	connect(this->ui->addPatRow, SIGNAL(clicked()), this, SLOT(addSymptomRow()));
	connect(this->ui->removePatRow, SIGNAL(clicked()), this, SLOT(removeSymptomRow()));
	connect(this->ui->addMedRow, SIGNAL(clicked()), this, SLOT(addDrugRow()));
	connect(this->ui->removeMedRow, SIGNAL(clicked()), this, SLOT(removeDrugRow()));
}

DoctorsWindow::~DoctorsWindow()
{
	delete ui;
}

bool DoctorsWindow::setController(VirtualController* vc){
	if (vc != nullptr){
		this->vc = vc;
		return true;
	}else
		return false;
}

void DoctorsWindow::setup_view() {
	this->ui->patientList->clearSelection();
	this->ui->patientList->setCurrentRow(-1);
	this->updatePatients();
	this->fillPatientsList();
	this->ui->L4start->setEnabled(this->ui->generateL4cb->checkState());
	this->ui->L4stop->setEnabled(this->ui->generateL4cb->checkState());
	this->ui->examinationDate->setDate(QDate::currentDate());
	this->ui->examinationDate->setTime(QTime::currentTime());
	
	this->ui->symptomTable->setColumnWidth(0,150);
	this->ui->symptomTable->setColumnWidth(1,317);
	this->ui->drugs->setColumnWidth(0,110);
	this->ui->drugs->setColumnWidth(2,300);
}

void DoctorsWindow::fillPatientsList() {
    if (!this->patients.empty()){
		if (this->ui->patientList->count() == 0)
			for (auto e : this->patients){
				std::string p = std::get<0>(e) + " " + std::get<1>(e);
				QListWidgetItemBundle* item = new QListWidgetItemBundle;
				item->id = std::get<2>(e);
				item->setText(QString(p.c_str()));
				this->ui->patientList->addItem(item);
			}
    }else{
        std::cerr << "empty patients!" << "\n";
    }
}

void DoctorsWindow::updatePatients(){
    std::string query = "all";
    this->patients = this->vc->getPatients(query);
}

void DoctorsWindow::doneExamination(){
    auto pSelIndex = this->ui->patientList->currentRow();
	
	if (pSelIndex == -1) {
		QMessageBox::information(this, "Błąd!", "Nie wybrano pacjenta.");
		return;
	}
	
    std::size_t p_id = std::get<2>(this->patients[pSelIndex]);
 
    std::cerr << "patient: " << std::get<0>(this->patients[pSelIndex]) << " " << std::get<1>(this->patients[pSelIndex]) << " index: " << p_id << "\n";
    
    std::string date, time;
    date = this->ui->examinationDate->date().toString("dd.MM.yyyy").toStdString();
    time = this->ui->examinationDate->time().toString("HH.mm").toStdString();
    std::cerr << "date: " << date << " time: " << time << "\n";
	
    std::string L4from, L4to;
    L4from = this->ui->L4start->date().toString("dd.MM.yyyy").toStdString();
    L4to = this->ui->L4stop->date().toString("dd.MM.yyyy").toStdString();
	std::cerr << "L4: " << L4from << " - " << L4to << "\n";
	
	std::vector<std::pair<std::string, std::string>> symptoms;
	for (int i=0; i<this->ui->symptomTable->rowCount(); i++) {
		if (this->ui->symptomTable->item(i,0) != nullptr && this->ui->symptomTable->item(i,1) != nullptr) {
			symptoms.push_back(std::make_pair(this->ui->symptomTable->item(i,0)->text().toStdString(), this->ui->symptomTable->item(i,1)->text().toStdString()));
		}
	}
	
	if (symptoms.empty()) {
		QMessageBox::information(this, "Błąd!", "Tabela objawów pusta.");
		return;
	}
	
	patient_medical_permit pmp;
	if (this->ui->generateL4cb->checkState())
		pmp = std::make_tuple(PermitType::L4, L4from, L4to);
	else
		pmp = std::make_tuple(PermitType::NORMAL, L4from, L4to);
	
	doctor_id d_id = 0; //ma się ustawiać przy logowaniu czy coś
	std::string diag = this->ui->diagnosis->toPlainText().toStdString();
    
    if (this->vc->addExam(p_id, d_id, date ,symptoms ,diag , pmp)){
		std::stringstream msg_h;
		msg_h << "Pomyślne zarejestrowano przebieg badania pacjenta " << this->ui->patientList->item(pSelIndex)->text().toStdString() << ".\n";
        QMessageBox::information(this, "Sukces!", msg_h.str().c_str());
		this->ui->listWidget->addItem({msg_h.str().c_str()});
        this->clearExamination();
    }
}

void DoctorsWindow::toggleL4(){
	this->ui->L4start->setEnabled(this->ui->generateL4cb->checkState());
	this->ui->L4stop->setEnabled(this->ui->generateL4cb->checkState());
}

void DoctorsWindow::generatePrescription(){
    auto pSelIndex = this->ui->patientList->currentRow();
	
	if (pSelIndex == -1) {
		QMessageBox::information(this, "Błąd!", "Nie wybrano pacjenta.");
		return;
	}
	
    std::size_t p_id = std::get<2>(this->patients[pSelIndex]);
	
 
    std::cerr << "patient: " << std::get<0>(this->patients[pSelIndex]) << " " << std::get<1>(this->patients[pSelIndex]) << " index: " << p_id << "\n";
	
	std::vector<patient_prescription_element> drugz;
	for (int i=0; i<this->ui->drugs->rowCount(); i++) {
		if (this->ui->drugs->item(i,0) != nullptr && this->ui->drugs->item(i,1) != nullptr && this->ui->drugs->item(i,2) != nullptr) {
			patient_prescription_element ppe = std::make_tuple(this->ui->drugs->item(i,0)->text().toStdString(), this->ui->drugs->item(i,1)->text().toStdString(), this->ui->drugs->item(i,2)->text().toStdString());
			drugz.push_back(ppe);
		}
	}
	
	if (drugz.empty()) {
		QMessageBox::information(this, "Błąd!", "Tabela leków pusta.");
		return;
	}
	
	doctor_id d_id = 0; //to co wyżej
	std::string additional = this->ui->additionalInfo->toPlainText().toStdString();
    
    if (this->vc->addPrescription(p_id, d_id, QDate::currentDate().toString("dd.MM.yyyy").toStdString(), drugz, additional)){
		std::stringstream msg_h;
		msg_h << "Pomyślne zapisano receptę dla pacjenta " << this->ui->patientList->item(pSelIndex)->text().toStdString() << " i jest gotowa do wydrukowania.\n";
        QMessageBox::information(this, "Sukces!", msg_h.str().c_str());
		this->ui->listWidget->addItem({msg_h.str().c_str()});
        this->clearPrescription();
    }
}

void DoctorsWindow::clearPrescription(){
    this->ui->drugs->clear();
    this->ui->drugs->setHorizontalHeaderLabels(QStringList{"Lek", "Dawka", "Uwagi"});
    this->ui->additionalInfo->clear();
	this->ui->patientList->clearSelection();
	this->ui->patientList->setCurrentRow(-1);
}

void DoctorsWindow::clearExamination(){
    this->ui->generateL4cb->setCheckState(Qt::Unchecked);
    this->ui->symptomTable->clear();
    this->ui->symptomTable->setHorizontalHeaderLabels(QStringList{"Objaw", "Opis"});
    this->ui->diagnosis->clear();
	this->ui->L4start->setEnabled(this->ui->generateL4cb->checkState());
	this->ui->L4stop->setEnabled(this->ui->generateL4cb->checkState());
	this->ui->examinationDate->setDate(QDate::currentDate());
	this->ui->examinationDate->setTime(QTime::currentTime());
	this->ui->patientList->clearSelection();
	this->ui->patientList->setCurrentRow(-1);
}

void DoctorsWindow::addSymptomRow(){
    this->ui->symptomTable->insertRow(this->ui->symptomTable->rowCount());
}

void DoctorsWindow::removeSymptomRow(){
    if (this->ui->symptomTable->rowCount() > 1)
        this->ui->symptomTable->removeRow(this->ui->symptomTable->rowCount() - 1 );
}

void DoctorsWindow::addDrugRow(){
    this->ui->drugs->insertRow(this->ui->drugs->rowCount());
}

void DoctorsWindow::removeDrugRow(){
    if (this->ui->drugs->rowCount() > 1)
        this->ui->drugs->removeRow(this->ui->drugs->rowCount() - 1 );
}
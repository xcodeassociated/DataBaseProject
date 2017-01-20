#ifndef PATIENTREGISTRATIONWINDOW_H
#define PATIENTREGISTRATIONWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <tuple>
#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <array>

#include "VirtualController.hpp"

namespace Ui {
class PatientRegistrationWindow;
}

class PatientRegistrationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PatientRegistrationWindow(QWidget *parent = 0);
    ~PatientRegistrationWindow();
    
    bool setController(VirtualController* vc);
    void setup_view();
    
private:
    Ui::PatientRegistrationWindow *ui;
    VirtualController* vc = nullptr;
    
    std::vector<patient> patients;
    std::vector<QListWidgetItemBundle*> patienListElements;
    std::vector<QListWidgetItemBundle*> examListElements;
    std::vector<QStringBundel> pSelects;
    std::vector<QStringBundel> dSelect;
    std::vector<doctor> doctors;
    std::vector<exam> exams;
    patient_id current_editing_patient = -1;
    exam_id current_editing_exam = -1;
    
    void fillPatientsList();
    void cleanLeftList();
    
    void updateDoctors();
    void updatePatients();
    void updatePatients(std::string, PatientQueryOrder, QuerySort);
    void updateExams();
    void updateExams(std::string, PExamsQueryOrder, QuerySort);
    void fillExamsList();
    void fillEditMedInfoTable();
    
    void cleanSelectors();
    
    enum class CurrentTab{
        P_REG_TAB = 0,
        E_REG_TAB = 1,
        P_EDIT_TAB = 2,
        E_EDIT_TAB = 3
    };
    
    CurrentTab currentTab;

    std::array<std::string, 3> psortby{"imie", "nazwisko", "pesel"};
    std::array<std::string, 3> esortby{"pacjent", "lekarz", "termin"};

private Q_SLOTS:
    void tabChange();
    
    void cleanPatientRegUi();
    void cleanExamRegUI();
    void cleanEditPatientUI();
    void cleanExamEditUI();
    
    void addPatientToSystem();
    void addNewMedInfoRow();
    void removeMedInfoRow();
    void deletePatient();
    
    void addExamToSystem();
    
    void editPatientInSystem();
    void addNewEditMedRow();
    void removeEditMedRow();
    
    void editExamInSystem();
    void deleteExam();
    
    void selectPatientInList();
    
    void searchFieldChanged(const QString&);
    void sortByChanged(int);
    void radioBChanged();
};

#endif // PATIENTREGISTRATIONWINDOW_H

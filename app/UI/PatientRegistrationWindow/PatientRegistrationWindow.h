#ifndef PATIENTREGISTRATIONWINDOW_H
#define PATIENTREGISTRATIONWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <tuple>
#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>

#include "VirtualController.h"

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
    void cleanPatientList();
    void updateDoctors();
    void updatePatients();
    void updateExams();
    void fillExamsList();
    void cleanSelectors();
    
    enum class CurrentTab{
        P_REG_TAB = 0,
        E_REG_TAB = 1,
        P_EDIT_TAB = 2,
        E_EDIT_TAB = 3
    };
    
    CurrentTab currentTab;
    
private Q_SLOTS:
    void tabChange();
    
    void addPatientToSystem();
    void cleanPatientRegUi();
    void addNewMedInfoRow();
    void removeMedInfoRow();
    void deletePatient();
    
    void addExamToSystem();
    void cleanExamRegUI();
    
    void editPatientInSystem();
    void revertEditPatient();
    void addNewEditMedRow();
    void removeEditMedRow();
    
    void editExamInSystem();
    void revertExamEdit();
    void deleteExam();
    
    void selectPatientInList();
    
    void searchFieldChanged(const QString&);
};

#endif // PATIENTREGISTRATIONWINDOW_H

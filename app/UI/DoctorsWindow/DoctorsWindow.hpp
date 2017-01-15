#ifndef DOCTORSWINDOW_H
#define DOCTORSWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include "VirtualController.hpp"
#include <iostream>
#include <sstream>

namespace Ui {
class DoctorsWindow;
}

class DoctorsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DoctorsWindow(QWidget *parent = 0);
    ~DoctorsWindow();
    
    bool setController(VirtualController* vc);
    void setup_view();

private:
    Ui::DoctorsWindow *ui;
    VirtualController* vc = nullptr;
    std::vector<patient> patients;

    void updatePatients();
    void fillPatientsList();
    
    enum class CurrentTab{
        E_SUMMARY_TAB = 0,
        P_CREATOR_TAB = 1,
    };
    
    CurrentTab currentTab;
    
private Q_SLOTS:
    void doneExamination();
    void toggleL4();
    void generatePrescription();
    void clearPrescription();
    void clearExamination();
    void addSymptomRow();
    void removeSymptomRow();
    void addDrugRow();
    void removeDrugRow();
};

#endif // DOCTORSWINDOW_H

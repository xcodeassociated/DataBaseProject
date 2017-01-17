//
// Created by jm on 15.01.17.
//

#include "AdminModel.hpp"

std::string AdminModel::generateReport(ReportType r_type, std::pair<std::string, std::string> time_peroid, ReportFormat r_format){
    return {};
}

void AdminModel::update_data() {
    this->update_patients();
    this->update_staff();
    this->update_pexams();
    this->update_pmedrecords();
    this->update_pprescriptions();
    this->update_pexamresults();
}
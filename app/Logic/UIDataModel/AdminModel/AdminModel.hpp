//
// Created by jm on 15.01.17.
//

#ifndef SYSMED_ADMINMODEL_HPP
#define SYSMED_ADMINMODEL_HPP

#include "Model.hpp"

class AdminModel : public Model{
public:
    using Model::Model;
    ~AdminModel() = default;
    
    std::string generateReport(ReportType, std::pair<std::string, std::string>, ReportFormat);
};


#endif //SYSMED_ADMINMODEL_HPP

//
// Created by jm on 15.01.17.
//

#ifndef SYSMED_STAFF_HPP
#define SYSMED_STAFF_HPP

#include "Personel.hpp"
#include "Doctor.hpp"

struct Staff {
    std::vector<Doctor> doctors;
    std::vector<Personel> personel;
    Staff() = default;
    
    operator std::vector<doctor>() const {
        std::vector<doctor> data{};
        for (Doctor d : this->doctors){
            data.push_back(static_cast<doctor>(d));
        }
        return data;
    };
};

#endif //SYSMED_STAFF_HPP

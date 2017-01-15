//
// Created by jm on 15.01.17.
//

#ifndef SYSMED_STAFF_HPP
#define SYSMED_STAFF_HPP

#include "Personel.hpp"
#include "Doctor.hpp"

struct Staff {
    std::vector<Doctor> doctors{ {"Adam", "Jankowski", 10, 857463748, Doctor::Title::LEKMED},
                                 {"Magdalena", "Maj", 11, 232463467, Doctor::Title::DOCTOR},
                                 {"Stefan", "Gips", 12, 647364859, Doctor::Title::PROF} };
    
    std::vector<Personel> personel{ {"Maria", "Dorowska", 0, 885937283, Personel::Position::RECEPTION},
                                    {"Joanna", "Opikela", 1, 694038495, Personel::Position::NURCE} };
    
    operator std::vector<doctor>() const {
        std::vector<doctor> data{};
        for (Doctor d : this->doctors){
            data.push_back(static_cast<doctor>(d));
        }
        return data;
    };
};

#endif //SYSMED_STAFF_HPP

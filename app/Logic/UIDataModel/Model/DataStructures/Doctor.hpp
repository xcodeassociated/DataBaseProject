//
// Created by jm on 15.01.17.
//

#ifndef SYSMED_DOCTOR_HPP
#define SYSMED_DOCTOR_HPP

#include "Person.hpp"

struct Doctor : public Person {
    using Person::Person;
    enum class Title  {
        LEKMED = 0,
        DOCTOR = 1,
        PROF = 2
    };
    Title title;
    Doctor(std::string name, std::string lastname, std::size_t id, std::size_t pesel, Title t) :
            Person(name, lastname, id, pesel), title{t}
    { ; }
    ~Doctor() = default;
    
    operator doctor() const {
        std::string title{};
        switch (this->title){
            case Title::LEKMED:
                title = "lek. med";
                break;
            case Title::DOCTOR:
                title = "dr";
                break;
            case Title::PROF:
                title = "prof.";
                break;
            default:
                title = "";
        }
        doctor data = std::make_tuple(this->name, this->lastname, this->id, title);
        return data;
    }
};

#endif //SYSMED_DOCTOR_HPP

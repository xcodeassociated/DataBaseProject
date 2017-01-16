//
// Created by jm on 15.01.17.
//

#ifndef SYSMED_PERSONEL_HPP
#define SYSMED_PERSONEL_HPP

#include "Person.hpp"

struct Personel : public Person {
    using Person::Person;
    enum class Position{
        RECEPTION = 0,
        NURCE = 1
    };
    Position position;
    Personel(std::string name, std::string lastname, std::size_t id, std::size_t pesel, Position p) :
            Person(name, lastname, id, pesel), position{p}
    { ; }
    ~Personel() = default;
};

#endif //SYSMED_PERSONEL_HPP

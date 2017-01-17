//
// Created by jm on 15.01.17.
//

#ifndef SYSMED_PERSON_HPP
#define SYSMED_PERSON_HPP

struct Person {
    std::string name = "",
            lastname = "";
    std::size_t id = 0,
            pesel = 0;
    Person(std::string name, std::string lastname, std::size_t id, std::size_t pesel) :
            name{name}, lastname{lastname}, id{id}, pesel{pesel}
    { ; }
    Person () = default;
    virtual ~Person();
    
};

#endif //SYSMED_PERSON_HPP

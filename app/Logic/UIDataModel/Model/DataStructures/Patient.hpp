//
// Created by jm on 15.01.17.
//

#ifndef SYSMED_PATIENT_HPP
#define SYSMED_PATIENT_HPP

#include "Person.hpp"

struct Patient : public Person {
    using Person::Person;
    Patient(Person p, patient_adr adr) : Person(p), address{std::get<0>(adr), std::get<1>(adr), std::get<2>(adr), std::get<3>(adr), std::get<4>(adr)} { ; }
    ~Patient() = default;
    
    struct patient_address{
        std::string city = "";
        std::string street = "";
        std::string housNR = "";
        std::string flatNR = "";
        std::string postalCode = "";
    };
    
    patient_address address{};
    
    operator patient() const{
        return std::make_tuple(this->name, this->lastname, this->id, this->pesel,
                               std::make_tuple(address.city, address.street, address.housNR, address.flatNR, address.postalCode));
    }
};

struct PatientMedicalInfo {
    std::size_t medinfo_id = 0;
    std::size_t patient_id = 0;
    std::string disease_date = "",
            disease_type = "",
            disease_other_info = "";
    
    //TODO! patient_med_record has to store all the values!
    operator std::tuple<std::string, std::string, std::string>() const {
        return std::make_tuple(this->disease_date, this->disease_type, this->disease_other_info);
    }
};

struct PatientExamDate {
    std::size_t exam_id = 0,
            patient_id = 0,
            doctor_id = 0;
    std::string date = "",
            date_hour = "",
            other_info = "";
    
    operator exam() const {
        return std::make_tuple(this->patient_id, this->doctor_id, this->date, this->date_hour, this->other_info, this->exam_id);
    }
};

struct PatientExamResult {
    std::size_t id = 0;
    patient_id p_id = 0;
    doctor_id d_id = 0;
    date exam_date = "";
    patient_symptoms p_symptoms{};
    diagnosis diag = "";
    patient_medical_permit permit{};
};

struct PatientPrescription{
    std::size_t id = 0;
    patient_id p_id = 0;
    doctor_id d_id = 0;
    date d = "";
    std::vector<patient_prescription_element> medicaments{};
    std::string other{};
};

struct Patients : std::vector<Patient> {
    Patients () = default;
    
    operator std::vector<patient>() const {
        std::vector<patient> data{};
        for (Patient p : *this){
            data.push_back(static_cast<patient>(p));
        }
        return data;
    }
};

struct PatientsExams : std::vector<PatientExamDate> {
    operator std::vector<exam>() const {
        std::vector<exam> data{};
        for (PatientExamDate pe : *this)
            data.push_back(static_cast<exam>(pe));
        return data;
    }
};

#endif //SYSMED_PATIENT_HPP

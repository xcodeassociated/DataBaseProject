#ifndef MODEL_H
#define MODEL_H

#include "VirtualController.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <utility>

struct Person {
    std::string name = "",
            lastname = "";
    std::size_t id = 0,
            pesel = 0;
    Person(std::string name, std::string lastname, std::size_t id, std::size_t pesel) :
            name{name}, lastname{lastname}, id{id}, pesel{pesel}
    { ; }
    virtual ~Person();
    
};

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

struct Doctor : public Person {
    using Person::Person;
    enum class Title  {
        LEKMED ,
        DOCTOR,
        PROF
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

struct Personel : public Person {
    using Person::Person;
    enum class Position{
        RECEPTION,
        NURCE
    };
    Position position;
    Personel(std::string name, std::string lastname, std::size_t id, std::size_t pesel, Position p) :
            Person(name, lastname, id, pesel), position{p}
    { ; }
    ~Personel() = default;
};

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

struct Patients : std::vector<Patient> {
    Patients () {
        std::vector<Patient> data = {
                {{"Jan", "kowalski", 100, 773849234}, std::make_tuple("Krakow", "Kwiatowa", "10", "11", "30-380")},
                {{"Anna", "Nowak", 101, 647873892}, std::make_tuple("Krakow", "Bracka", "5", "6", "31-384")},
                {{"Mateusz", "Nowicki", 102, 848920342}, std::make_tuple("Krakow", "Szewska", "4", "89", "31-351")},
                {{"Marta", "Kruk", 103, 940384829}, std::make_tuple("Krakow", "Dietla", "9", "11", "32-377")} };
        
        for (auto e : data)
            this->push_back(e);
    }
    
    operator std::vector<patient>() const {
        std::vector<patient> data{};
        for (Patient p : *this){
            data.push_back(static_cast<patient>(p));
        }
        return data;
    }
};

struct PatientMedicalInfo {
    std::size_t patient_id = 0;
    std::string disease_date = "",
            disease_type = "",
            disease_other_info = "";
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

struct PatientsExams : std::vector<PatientExamDate> {
    operator std::vector<exam>() const {
        std::vector<exam> data{};
        for (PatientExamDate pe : *this)
            data.push_back(static_cast<exam>(pe));
        return data;
    }
};

using PatientsMedicalRecords = std::vector<PatientMedicalInfo>;
using PatientsPrescriptions = std::vector<PatientPrescription>;
using PatientsExamsResults = std::vector<PatientExamResult>;
using Persons_Adresses = std::vector<person_addess>;

class Model{
protected:
    VirtualController* vController = nullptr;
    Patients patients;
    Staff staff;
    PatientsExams pExams;
    PatientsMedicalRecords pMedRecords;
    Persons_Adresses adresses;
    PatientsPrescriptions prescriptions;
    PatientsExamsResults examsResults;
    
public:
    
    Model(VirtualController* vController);
    virtual ~Model();
    
    patient getPatient(patient_id&); // returns patient by id
    std::vector<patient> getPatients(std::string&); // returns patients by at last one patient data
    std::vector<doctor> getDoctors(std::string&);
    doctor getDoctor(doctor_id&);
    std::vector<exam> getExams(std::string&);
    PatientPrescription prescription;
    PatientExamResult examResults;
};

#endif // MODEL_H

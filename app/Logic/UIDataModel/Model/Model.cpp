#include "Model.hpp"

sql::Driver* Model::driver = get_driver_instance();
sql::Connection* Model::connection = nullptr;
std::size_t Model::arc = 0;
Person Model::owner = {};
Model::OwnerType Model::ownerType = Model::OwnerType::None;

Model::Model(VirtualController *vc) throw(sql::SQLException) : vController{vc}, patients{},
                                      staff{}, pExams{}, pMedRecords{},
                                      prescriptions{}, examsResults{}, dbinfo{}
{
    if (Model::arc == 0) {
        this->connection = this->driver->connect(dbinfo.address, dbinfo.log, dbinfo.pass);
        
        //may throw if db not found
        this->connection->setSchema(dbinfo.db_name);
    }
    
    Model::arc++;
}

Model::~Model() {
    Model::arc--;
    
    if (Model::arc == 0)
        delete this->connection;
}

Person::~Person() {
    ;
}

void Model::update_patients(){
    this->patients.clear();
    
    sql::Statement *stmt = nullptr;
    sql::ResultSet *res = nullptr;
    
    stmt = this->connection->createStatement();
    res = stmt->executeQuery(
            "SELECT \n"
                    "`id` as `ID`, `name` as `Name`, `lastname` as `Lastname`, `pesel` as `PESEL`, \n"
                    "`city` as `City`, `street` as `Street`, `house_nr` as `House Number`, `flat_nr` as `Flat Number`, `postal_code` as `Postal Code`\n"
                    "FROM `SysMed`.`Patients`\n"
                    "\tLEFT OUTER JOIN `SysMed`.`PersonAddress`\n"
                    "\tON `SysMed`.`Patients`.`id` = `SysMed`.`PersonAddress`.`id_patient`;"
    );
    while (res->next()) {
        std::size_t pesel = 0;
        auto id = static_cast<std::size_t >(res->getInt(1));
        std::string name = res->getString("Name");
        std::string lastname = res->getString("Lastname");
        std::string pesel_str = res->getString("PESEL");
        
        std::stringstream sstream(pesel_str);
        sstream >> pesel;
    
        std::string city = res->getString("City");
        std::string street = res->getString("Street");
        std::string house_nr = res->getString("House Number");
        std::string flat_nr = "";
        if (!res->isNull("Flat Number"))
            flat_nr = res->getString("Flat Number");
        std::string postal = res->getString("Postal Code");
        
        Patient p{{name, lastname, id, pesel}, std::make_tuple(city, street, house_nr, flat_nr, postal)};
        this->patients.push_back(p);
    }
    
    delete stmt;
    delete res;
}

std::pair<Model::QType, std::string> Model::QueryParser::parse(std::string query) {
    std::pair<Model::QType, std::string> result{};
    
    if (std::string(query.substr(0, 5)) == "name="){
        result.first = Model::QType::NAME;
        result.second = query.substr(5, query.length());
    }else if (std::string(query.substr(0, 6)) == "!name=") {
        result.first = Model::QType::NAME_ONLY;
        result.second = query.substr(6, query.length());
    }else if (std::string(query.substr(0, 9)) == "lastname="){
        result.first = Model::QType::LASTNAME;
        result.second = query.substr(9, query.length());
    }else if (std::string(query.substr(0, 6)) == "pesel="){
        result.first = Model::QType::PESEL;
        result.second = query.substr(6, query.length());
    }else{
        result.first = Model::QType::NONE;
        result.second = "";
    }
    return result;
}

void Model::update_patients(std::string& query){
    if (query.length() == 0){
        this->update_patients();
        this->update_pexams();
        this->update_pmedrecords();
    
        this->update_pprescriptions();
        this->update_pexamresults();
    }else if (query.length() > 0 && query.length() < 5){
        return;
    }
    
    auto parsed = Model::QueryParser::parse(query);
    
    if (parsed.first == Model::QType::NONE)
        return;
    
    std::string ask = parsed.second;

    this->patients.clear();
    
    sql::PreparedStatement *stmt = nullptr;
    sql::ResultSet *res = nullptr;
    stmt = this->connection->prepareStatement("set @query = (?)");
    stmt->setString(1, ask);
    res = stmt->executeQuery();
    delete res;
    delete stmt;
    
    stmt = this->connection->prepareStatement("set @f = (?)");
    
    if (parsed.first == Model::QType::NAME)
        stmt->setString(1, "name");
    else if (parsed.first == Model::QType::NAME_ONLY)
        stmt->setString(1, "!name");
    else if (parsed.first == Model::QType::LASTNAME)
        stmt->setString(1, "lastname");
    else if (parsed.first == Model::QType::PESEL) {
        std::cerr << "sdsdsd";
        stmt->setString(1, "pesel");
    }else
        ;
        
    res = stmt->executeQuery();
    delete res;
    delete stmt;

    stmt = this->connection->prepareStatement("select find_patient(@query, @f) as count_");
    res = stmt->executeQuery();
    res->next();
    int exec_query_count = res->getInt(1);
    std::cerr << "query count: " << exec_query_count << std::endl;
    delete res;
    delete stmt;

    stmt = this->connection->prepareStatement(
            "select * from find_patient_result"
    );
    res = stmt->executeQuery();

    while (res->next()) {
        std::size_t pesel = 0;
        auto id = static_cast<std::size_t >(res->getInt(1));
        std::string name = res->getString("Name");
        std::string lastname = res->getString("Lastname");
        std::string pesel_str = res->getString("PESEL");
    
        std::stringstream sstream(pesel_str);
        sstream >> pesel;
    
        std::string city = res->getString("City");
        std::string street = res->getString("Street");
        std::string house_nr = res->getString("House Number");
        std::string flat_nr = "";
        if (!res->isNull("Flat Number"))
            flat_nr = res->getString("Flat Number");
        std::string postal = res->getString("Postal Code");
    
        Patient p{{name, lastname, id, pesel}, std::make_tuple(city, street, house_nr, flat_nr, postal)};
        this->patients.push_back(p);
    }
    
    delete res;
    delete stmt;

    this->update_pexams();
    this->update_pmedrecords();
    
    this->update_pprescriptions();
    this->update_pexamresults();

}

void Model::commit_transaction() {
    sql::Statement *stmt = nullptr;

    stmt = this->connection->createStatement();
    stmt->execute("COMMIT;");

    delete stmt;
}

void Model::update_staff(){
    this->staff.doctors.clear();
    this->staff.personel.clear();
    
    /* Doctors */
    
    sql::Statement *stmt = nullptr;
    sql::ResultSet *res = nullptr;
    
    stmt = this->connection->createStatement();
    res = stmt->executeQuery(
            "SELECT \n"
                    "`id` as `ID`, `name` as `Name`, `lastname` as `Lastname`, `pesel` as `PESEL`,\n"
                    "`city` as `City`, `street` as `Street`, `house_nr` as `House Number`, `flat_nr` as `Flat Number`, `postal_code` as `Postal Code`,\n"
                    "\t(SELECT `SysMed`.`DoctorTitle`.`title_name` FROM \n"
                    "\t\t`SysMed`.`DoctorTitle` WHERE `SysMed`.`DoctorTitle`.`id_title` = IF (`SysMed`.`Doctors`.`title` = 0, 1, `SysMed`.`Doctors`.`title`) \n"
                    "    LIMIT 1) as `TitleName`\n"
                    "FROM `SysMed`.`Doctors`\n"
                    "\tLEFT OUTER JOIN `SysMed`.`PersonAddress`\n"
                    "\tON `SysMed`.`Doctors`.`id` = `SysMed`.`PersonAddress`.`id_doctor`;"
    );
    while (res->next()) {
        std::size_t pesel = 0;
        auto id = static_cast<std::size_t >(res->getInt(1));
        auto name = res->getString("Name");
        auto lastname = res->getString("Lastname");
        auto pesel_str = res->getString("PESEL");
        Doctor::Title title;
        auto tittle_str = res->getString("TitleName");
        if (tittle_str == "lek.med")
            title = Doctor::Title::LEKMED;
        else if (tittle_str == "dr")
            title = Doctor::Title::DOCTOR;
        else if (tittle_str == "prof.")
            title = Doctor::Title::PROF;
        else
            ;
        std::stringstream sstream(pesel_str);
        sstream >> pesel;
        
        Doctor d{name, lastname, id, pesel, title};
        this->staff.doctors.push_back(d);
    }
    
    delete res;
    delete stmt;
    
    /* Staff */
    
    stmt = this->connection->createStatement();
    res = stmt->executeQuery(
            "SELECT \n"
                    "`id` as `ID`, `name` as `Name`, `lastname` as `Lastname`, `pesel` as `PESEL`, `position` as `Position`,\n"
                    "`city` as `City`, `street` as `Street`, `house_nr` as `House Number`, `flat_nr` as `Flat Number`, `postal_code` as `Postal Code`,\n"
                    "(SELECT `SysMed`.`StaffPosition`.`position_name` FROM \n"
                    "\t\t`SysMed`.`StaffPosition` WHERE `SysMed`.`StaffPosition`.`id_position` = IF (`SysMed`.`Staff`.`position` = 0, 1, `SysMed`.`Staff`.`position`) \n"
                    "    LIMIT 1) as `Position`\n"
                    "FROM `SysMed`.`Staff`\n"
                    "\tLEFT OUTER JOIN `SysMed`.`PersonAddress`\n"
                    "\tON `SysMed`.`Staff`.`id` = `SysMed`.`PersonAddress`.`id_staff`;"
    );
    while (res->next()) {
        std::size_t pesel = 0;
        auto id = static_cast<std::size_t >(res->getInt(1));
        auto name = res->getString("Name");
        auto lastname = res->getString("Lastname");
        auto pesel_str = res->getString("PESEL");
        Personel::Position pos;
        auto position_str = res->getString("Position");
        if (position_str == "RECEPTION")
            pos = Personel::Position::RECEPTION;
        else if (position_str == "NURCE")
            pos = Personel::Position::NURCE;
        else
            ;
        std::stringstream sstream(pesel_str);
        sstream >> pesel;
    
        Personel p{name, lastname, id, pesel, pos};
        this->staff.personel.push_back(p);
    }
    
    delete res;
    delete stmt;
}

void Model::update_pmedrecords() {
    this->pMedRecords.clear();
    
    for (Patient p : this->patients) {
        std::size_t p_id = p.id;
        std::size_t id_medinfo;
        std::string date;
        std::string d_type;
        std::string d_other;
        
        sql::PreparedStatement *stmt = nullptr;
        sql::ResultSet *res = nullptr;
        
        stmt = this->connection->prepareStatement(
                "SELECT \n"
                        "`id_medinfo` as `ID`, cast(`disease_date` as date) as `Disease Date`, `disease_type` as `Disease Type`, `disease_other_info` as `Other`\n"
                        "FROM `SysMed`.`PatientMedicalInfo`\n"
                        "WHERE `SysMed`.`PatientMedicalInfo`.`id_patient` = (?) ORDER BY `SysMed`.`PatientMedicalInfo`.`disease_date` DESC;"
        );
        stmt->setInt(1, p_id);
        res = stmt->executeQuery();
        while (res->next()) {
            id_medinfo = static_cast<std::size_t>(res->getInt("ID"));
            date = res->getString("Disease Date");
            d_type = res->getString("Disease Type");
            d_other = res->getString("Other");
            
            PatientMedicalInfo pmi{id_medinfo, p_id, date, d_type, d_other};
            this->pMedRecords.push_back(pmi);
        }
        delete stmt;
        delete res;
    }
}

void Model::update_pexams(){
    this->pExams.clear();
    
    for (Patient p : this->patients) {
        std::size_t p_id = p.id;
        std::size_t exam_id;
        std::size_t doctor_id;
        std::string date;
        std::string time;
        std::string other;
        
        sql::PreparedStatement *stmt = nullptr;
        sql::ResultSet *res = nullptr;
    
        stmt = this->connection->prepareStatement(
                "SELECT \n"
                        "`id_patient_exam` as `ID`, `id_patient` as `PatientID`, `id_doctor` as `DoctorID`, cast(`exam_date` as date) as `ExamDate`, cast(`exam_date` as time) as `ExamTime`, `other_examdate_info` as `Other`\n"
                        "FROM `SysMed`.`PatientExamDate`\n"
                        "WHERE `SysMed`.`PatientExamDate`.`id_patient` = (?) ORDER BY `SysMed`.`PatientExamDate`.`exam_date` ASC;"
        );
        stmt->setInt(1, p_id);
        res = stmt->executeQuery();
        while (res->next()) {
            exam_id = static_cast<std::size_t>(res->getInt("ID"));
            doctor_id = static_cast<std::size_t>(res->getInt("DoctorID"));
            date = res->getString("ExamDate");
            time = res->getString("ExamTime");
            other = res->getString("Other");
            
            PatientExamDate ped{exam_id, p_id, doctor_id, date, time, other};
            this->pExams.push_back(ped);
        }
    
        delete stmt;
        delete res;
    }
}
// TODO!
void Model::update_pprescriptions(){
    this->prescriptions.clear();
    
    sql::Statement *stmt = nullptr;
    sql::ResultSet *res = nullptr;
    
    stmt = this->connection->createStatement();
    res = stmt->executeQuery("SELECT 'Hello World!' AS _message");
    while (res->next()) {
        
    }
    
    delete stmt;
    delete res;
}
//TODO!
void Model::update_pexamresults(){
    this->examsResults.clear();
    
    sql::Statement *stmt = nullptr;
    sql::ResultSet *res = nullptr;
    
    stmt = this->connection->createStatement();
    res = stmt->executeQuery("SELECT 'Hello World!' AS _message");
    while (res->next()) {
        
    }
    
    delete stmt;
    delete res;
}

std::string Model::create_transaction() {
    sql::PreparedStatement *stmt = nullptr;
    sql::ResultSet *res = nullptr;
    stmt = this->connection->prepareStatement("select cast(now() as date) as `CurrentDate`, cast(now() as time) as `CurrentTime`;");
    res = stmt->executeQuery();
    std::string date, time;
    assert(res->rowsCount() == 1);
    while (res->next()) {
        date = res->getString("CurrentDate");
        time = res->getString("CurrentTime");
    }
    std::string snap = date + "_" + time;
    delete res;
    delete stmt;

    std::cerr << "Snap: " << snap << std::endl;

    sql::Statement *stmt2 = nullptr;
    stmt2 = this->connection->createStatement();
    stmt2->execute("START TRANSACTION;");

    delete stmt2;

    std::string q = std::string("SAVEPOINT") + std::string(" ") + snap + ";";
    std::replace(q.begin(), q.end(), '-', '_');
    std::replace(q.begin(), q.end(), ':', '_');
    std::cerr << "Snap: " << q << std::endl;

    stmt2 = this->connection->createStatement();
    stmt2->execute(q.c_str());

    delete stmt2;

    return q;
}

patient Model::getPatient(patient_id& p_id) {
    auto it = std::find_if(this->patients.begin(), this->patients.end(), [p_id](const Patient& p){
        return p.id == p_id;
    });
    if (it != this->patients.end())
        return *it;
    else
        return {};
}

std::vector<patient> Model::getPatients(std::string& query) {
    if (query == "all"){
        return this->patients;
    }
    
    this->update_patients(query);
    return this->patients;
}

std::vector<doctor> Model::getDoctors(std::string& query){
    if (query == "all"){
        return this->staff;
    }else
        return {};
}

doctor Model::getDoctor(doctor_id& d_id){
    auto it = std::find_if(this->staff.doctors.begin(), this->staff.doctors.end(), [d_id](const Doctor& d){
        return d_id == d.id;
    });
    if (it != this->staff.doctors.end())
        return *it;
    else
        return {};
}

std::vector<exam> Model::getExams(std::string& query){
    if (query == "all")
        return this->pExams;
    else
        return {};
}

patient_medinfo_reg Model::getPatientMedInfo(patient_id& p_id){
    patient_medinfo_reg result{};
    PatientsMedicalRecords temp{};
    std::copy_if(this->pMedRecords.begin(), this->pMedRecords.end(), std::back_inserter(temp), [p_id](const PatientMedicalInfo& pmi){
        return pmi.patient_id == p_id;
    });
    std::transform(temp.begin(), temp.end(), std::back_inserter(result), [](const PatientMedicalInfo&  pmi){
        return pmi;
    });
    return result;
}

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

void Model::update_patients(PatientQueryOrder pqo, QuerySort qs){
    this->patients.clear();

    std::cerr << "up: " << (int)pqo << " " << (int)qs << "\n";

    sql::PreparedStatement *stmt = nullptr;
    sql::ResultSet *res = nullptr;
    std::stringstream ss;

    switch (qs){
        case QuerySort::ASC:
            ss <<   "SELECT"
                    "  `id` as `ID`,"
                    "  `name` as `Name`,"
                    "  `lastname` as `Lastname`,"
                    "  `pesel` as `PESEL`,"
                    "  `city` as `City`,"
                    "  `street` as `Street`,"
                    "  IF(`house_nr` = null, \"\", `house_nr`)  as `House Number`,"
                    "  `flat_nr` as `Flat Number`,"
                    "  `postal_code` as `Postal Code`"
                    "FROM `SysMed`.`Patients`"
                    "LEFT OUTER JOIN `SysMed`.`PersonAddress`"
                    "ON `SysMed`.`Patients`.`id` = `SysMed`.`PersonAddress`.`id_patient`"
                    "  ORDER BY ";

            switch (pqo){
                case PatientQueryOrder::Lastname:
                    ss << "lastname ASC";
                    break;
                case PatientQueryOrder::Name:
                    ss <<  "name ASC";
                    break;
                case PatientQueryOrder::Pesel:
                    ss << "pesel ASC";
                    break;
                default:
                    ss << "lastname ASC";
                    break;
            }

            break;
        case QuerySort::DESC:

            ss <<   "SELECT"
                    "  `id` as `ID`,"
                    "  `name` as `Name`,"
                    "  `lastname` as `Lastname`,"
                    "  `pesel` as `PESEL`,"
                    "  `city` as `City`,"
                    "  `street` as `Street`,"
                    "  IF(`house_nr` = null, \"\", `house_nr`)  as `House Number`,"
                    "  `flat_nr` as `Flat Number`,"
                    "  `postal_code` as `Postal Code`"
                    "FROM `SysMed`.`Patients`"
                    "LEFT OUTER JOIN `SysMed`.`PersonAddress`"
                    "ON `SysMed`.`Patients`.`id` = `SysMed`.`PersonAddress`.`id_patient`"
                    "  ORDER BY ";

            switch (pqo){
                case PatientQueryOrder::Lastname:
                    ss << "lastname DESC";
                    break;
                case PatientQueryOrder::Name:
                    ss <<  "name DESC";
                    break;
                case PatientQueryOrder::Pesel:
                    ss << "pesel DESC";
                    break;
                default:
                    ss << "lastname DESC";
                    break;
            }

            break;
    }

    stmt = this->connection->prepareStatement(ss.str());

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
    
    delete stmt;
    delete res;

}

std::pair<Model::QTypePatient, std::string> Model::QueryParserPatient::parse(std::string query) {
    std::pair<Model::QTypePatient, std::string> result{};
    
    if (std::string(query.substr(0, 5)) == "name="){
        result.first = Model::QTypePatient::NAME;
        result.second = query.substr(5, query.length());
    }else if (std::string(query.substr(0, 6)) == "!name=") {
        result.first = Model::QTypePatient::NAME_ONLY;
        result.second = query.substr(6, query.length());
    }else if (std::string(query.substr(0, 9)) == "lastname="){
        result.first = Model::QTypePatient::LASTNAME;
        result.second = query.substr(9, query.length());
    }else if (std::string(query.substr(0, 6)) == "pesel="){
        result.first = Model::QTypePatient::PESEL;
        result.second = query.substr(6, query.length());
    }else{
        result.first = Model::QTypePatient::NONE;
        result.second = "";
    }
    return result;
}

std::string Model::QueryParserPatient::parsePatientQueryOrder(PatientQueryOrder pqo){
    std::string result{};

    switch (pqo){
        case PatientQueryOrder::Id:
            result = "id";
            break;
        case PatientQueryOrder::Name:
            result = "name";
            break;
        case PatientQueryOrder::Lastname:
            result = "lastname";
            break;
        case PatientQueryOrder::Pesel:
            result = "pesel";
            break;
    }

    return result;
}

std::pair< Model::QueryParserExams::QueryTypeExams, std::string> Model::QueryParserExams::parse(std::string query){
    std::pair< Model::QueryParserExams::QueryTypeExams, std::string> result{};

    if (std::string(query.substr(0, 6)) == "pname="){
        result.first = Model::QTypeExam::PATIENT;
        result.second = query.substr(6, query.length());
    }else if (std::string(query.substr(0, 7)) == "!pname="){
        result.first = Model::QTypeExam::PATIENT_NAME_ONLY;
        result.second = query.substr(7, query.length());
    }else if (std::string(query.substr(0, 10)) == "plastname="){
        result.first = Model::QTypeExam::PATIENT_LASTNAME_ONLY;
        result.second = query.substr(10, query.length());
    }else if (std::string(query.substr(0, 6)) == "pesel="){
        result.first = Model::QTypeExam::PATIENT_PESEL;
        result.second = query.substr(6, query.length());
    }else if (std::string(query.substr(0, 6)) == "dname="){
        result.first = Model::QTypeExam::DOCTOR;
        result.second = query.substr(6, query.length());
    }else if (std::string(query.substr(0, 7)) == "!dname="){
        result.first = Model::QTypeExam::DOCTOR_NAME_ONLY;
        result.second = query.substr(7, query.length());
    }else if (std::string(query.substr(0, 10)) == "dlastname="){
        result.first = Model::QTypeExam::DOCTOR_LASTNAME_ONLY;
        result.second = query.substr(10, query.length());
    } else {
        result.first = Model::QTypeExam::NONE;
        result.second = "";
    }

    return result;
};

std::string Model::QueryParserExams::parsExamQueryOrderSearch(PExamsQueryOrder peqo){
    std::string result{};
    switch (peqo){
        case PExamsQueryOrder::Date:
            result = "exam_date";
            break;
        case PExamsQueryOrder::Patient:
            result = "pid";
            break;
        case PExamsQueryOrder::Doctor:
            result = "did";
            break;
        case PExamsQueryOrder::ID:
            result = "exam_date";
            break;
    }
    return result;
}

std::string Model::QueryParserExams::parsExamQueryOrder(PExamsQueryOrder peqo){
    std::string result{};
    switch (peqo){
        case PExamsQueryOrder::Date:
            result = "exam_date";
            break;
        case PExamsQueryOrder::Patient:
            result = "id_patient";
            break;
        case PExamsQueryOrder::Doctor:
            result = "id_doctor";
            break;
        case PExamsQueryOrder::ID:
            result = "id_patient_exam";
            break;
    }
    return result;
}

std::tuple<std::string, std::string, Model::QueryParserOperant::QueryOperant> Model::QueryParserOperant::parseQueryOperant(std::string q){
    QueryOperant qo;
    std::string t1{}, t2{};

    auto it = std::find_if(q.begin(), q.end(), [](const char& c){
        return (c == '&' || c == '|');
    });

    if (*it == '&') {
        qo = QueryOperant::AND;
        t2 = "";
    }else if (*it == '|') {
        qo = QueryOperant::OR;
        t2 = "";
    }else
        qo = QueryOperant::NONE;

    std::copy(q.begin(), it, std::back_inserter(t1));

    if (qo == QueryOperant::NONE)
        t2 = "";
    else if (qo != QueryOperant::NONE && std::distance(it + 1, q.end()) > 0)
        std::copy(it + 1, q.end(), std::back_inserter(t2));


    std::cerr << "###t1: " << t1 << " ###t2: " << t2 << " ####qo: " << (int)qo << std::endl;
    return std::make_tuple(t1, t2, qo);
};


void Model::update_patients(std::string& query, PatientQueryOrder pqo, QuerySort qs){

    if (query.length() < 5) {
        this->update_patients(pqo, qs);
        this->update_pexams(PExamsQueryOrder::ID, QuerySort::ASC);
        this->update_pmedrecords();

        this->update_pprescriptions();
        this->update_pexamresults();
        return;
    }

    this->patients.clear();

    sql::PreparedStatement *stmt = nullptr;
    sql::ResultSet *res = nullptr;
    std::string pqo_value = Model::QueryParserPatient::parsePatientQueryOrder(pqo);
    unsigned qs_value = static_cast<unsigned>(qs);

    auto t = Model::QueryParserOperant::parseQueryOperant(query);

    if (std::get<2>(t) == QueryParserOperant::QueryOperant::NONE) {

        auto parsed = Model::QueryParserPatient::parse(std::get<0>(t));
        std::cerr << "q: " << query << "? : " << std::get<0>(t) << std::endl;
        std::cerr << "parsed: " << (int)parsed.first << "ask: " << parsed.second  << " pqo: " << pqo_value << " qs: " << qs_value << std::endl;

        if (parsed.first == Model::QTypePatient::NONE)
            return;

        std::string ask = parsed.second;

        stmt = this->connection->prepareStatement("set @query = (?)");
        stmt->setString(1, ask);
        res = stmt->executeQuery();
        delete res;
        delete stmt;

        stmt = this->connection->prepareStatement("set @query2 = (?)");
        stmt->setString(1, "");
        res = stmt->executeQuery();
        delete res;
        delete stmt;

        stmt = this->connection->prepareStatement("set @order = (?)");
        stmt->setString(1, pqo_value);
        res = stmt->executeQuery();
        delete res;
        delete stmt;

        stmt = this->connection->prepareStatement("set @p = (?)");
        stmt->setInt(1, qs_value);
        res = stmt->executeQuery();
        delete res;
        delete stmt;

        stmt = this->connection->prepareStatement("set @f = (?)");
        if (parsed.first == Model::QTypePatient::NAME)
            stmt->setString(1, "name");
        else if (parsed.first == Model::QTypePatient::NAME_ONLY)
            stmt->setString(1, "!name");
        else if (parsed.first == Model::QTypePatient::LASTNAME)
            stmt->setString(1, "lastname");
        else if (parsed.first == Model::QTypePatient::PESEL) {
            stmt->setString(1, "pesel");
        } else;

        res = stmt->executeQuery();
        delete res;
        delete stmt;

        stmt = this->connection->prepareStatement("set @f2 = (?)");
        stmt->setString(1, "");
        res = stmt->executeQuery();
        delete res;
        delete stmt;

        stmt = this->connection->prepareStatement("call find_patient_2(@query, @f, @query2, @f2, @order, @p);");
        res = stmt->executeQuery();
        delete res;
        delete stmt;

        stmt = this->connection->prepareStatement(
                "SELECT * from final_22;"
        );
        res = stmt->executeQuery();

    }else if (std::get<2>(t) == QueryParserOperant::QueryOperant::AND){

        auto parsed = Model::QueryParserPatient::parse(std::get<0>(t));
        auto parsed2 = Model::QueryParserPatient::parse(std::get<1>(t));

        if (parsed.first == Model::QTypePatient::NONE)
            return;

        std::string ask = parsed.second;
        std::string ask2 = parsed2.second;

        std::cerr << "ask: " << ask << " ask2: " << ask2 << std::endl;

        stmt = this->connection->prepareStatement("set @query = (?)");
        stmt->setString(1, ask);
        res = stmt->executeQuery();
        delete res;
        delete stmt;

        stmt = this->connection->prepareStatement("set @query2 = (?)");
        stmt->setString(1, ask2);
        res = stmt->executeQuery();
        delete res;
        delete stmt;

        stmt = this->connection->prepareStatement("set @order = (?)");
        stmt->setString(1, pqo_value);
        res = stmt->executeQuery();
        delete res;
        delete stmt;

        stmt = this->connection->prepareStatement("set @p = (?)");
        stmt->setInt(1, qs_value);
        res = stmt->executeQuery();
        delete res;
        delete stmt;

        stmt = this->connection->prepareStatement("set @f = (?)");
        if (parsed.first == Model::QTypePatient::NAME)
            stmt->setString(1, "name");
        else if (parsed.first == Model::QTypePatient::NAME_ONLY)
            stmt->setString(1, "!name");
        else if (parsed.first == Model::QTypePatient::LASTNAME)
            stmt->setString(1, "lastname");
        else if (parsed.first == Model::QTypePatient::PESEL) {
            stmt->setString(1, "pesel");
        } else { }

        res = stmt->executeQuery();
        delete res;
        delete stmt;

        stmt = this->connection->prepareStatement("set @f2 = (?)");
        if (parsed2.first == Model::QTypePatient::NAME)
            stmt->setString(1, "name");
        else if (parsed2.first == Model::QTypePatient::NAME_ONLY)
            stmt->setString(1, "!name");
        else if (parsed2.first == Model::QTypePatient::LASTNAME)
            stmt->setString(1, "lastname");
        else if (parsed2.first == Model::QTypePatient::PESEL) {
            stmt->setString(1, "pesel");
        } else {
            stmt->setString(1, "name");
        }

        res = stmt->executeQuery();
        delete res;
        delete stmt;

        stmt = this->connection->prepareStatement("call find_patient_2(@query, @f, @query2, @f2, @order, @p);");
        res = stmt->executeQuery();
        delete res;
        delete stmt;

        stmt = this->connection->prepareStatement(
                "SELECT * from final_2_and;"
        );
        res = stmt->executeQuery();

    }else if (std::get<2>(t)== QueryParserOperant::QueryOperant::OR){

        auto parsed = Model::QueryParserPatient::parse(std::get<0>(t));
        auto parsed2 = Model::QueryParserPatient::parse(std::get<1>(t));

        if (parsed.first == Model::QTypePatient::NONE)
            return;

        std::string ask = parsed.second;
        std::string ask2 = parsed2.second;

        std::cerr << "ask: " << ask << " ask2: " << ask2 << std::endl;

        stmt = this->connection->prepareStatement("set @query = (?)");
        stmt->setString(1, ask);
        res = stmt->executeQuery();
        delete res;
        delete stmt;

        stmt = this->connection->prepareStatement("set @query2 = (?)");
        stmt->setString(1, ask2);
        res = stmt->executeQuery();
        delete res;
        delete stmt;

        stmt = this->connection->prepareStatement("set @order = (?)");
        stmt->setString(1, pqo_value);
        res = stmt->executeQuery();
        delete res;
        delete stmt;

        stmt = this->connection->prepareStatement("set @p = (?)");
        stmt->setInt(1, qs_value);
        res = stmt->executeQuery();
        delete res;
        delete stmt;

        stmt = this->connection->prepareStatement("set @f = (?)");
        if (parsed.first == Model::QTypePatient::NAME)
            stmt->setString(1, "name");
        else if (parsed.first == Model::QTypePatient::NAME_ONLY)
            stmt->setString(1, "!name");
        else if (parsed.first == Model::QTypePatient::LASTNAME)
            stmt->setString(1, "lastname");
        else if (parsed.first == Model::QTypePatient::PESEL) {
            stmt->setString(1, "pesel");
        } else { }

        res = stmt->executeQuery();
        delete res;
        delete stmt;

        stmt = this->connection->prepareStatement("set @f2 = (?)");
        if (parsed2.first == Model::QTypePatient::NAME)
            stmt->setString(1, "name");
        else if (parsed2.first == Model::QTypePatient::NAME_ONLY)
            stmt->setString(1, "!name");
        else if (parsed2.first == Model::QTypePatient::LASTNAME)
            stmt->setString(1, "lastname");
        else if (parsed2.first == Model::QTypePatient::PESEL) {
            stmt->setString(1, "pesel");
        } else {
            stmt->setString(1, "");
        }

        res = stmt->executeQuery();
        delete res;
        delete stmt;

        stmt = this->connection->prepareStatement("call find_patient_2(@query, @f, @query2, @f2, @order, @p);");
        res = stmt->executeQuery();
        delete res;
        delete stmt;

        stmt = this->connection->prepareStatement(
                "SELECT * from final_22;"
        );
        res = stmt->executeQuery();
    }

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

    //this->update_pexams(PExamsQueryOrder::ID, QuerySort::ASC);
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
            "SELECT "
                    "`id` as `ID`, "
                    "`name` as `Name`, "
                    "`lastname` as `Lastname`, "
                    "`pesel` as `PESEL`,"
                    "`city` as `City`, `"
                    "street` as `Street`, "
                    "`house_nr` as `House Number`, "
                    "`flat_nr` as `Flat Number`, "
                    "`postal_code` as `Postal Code`,"
                    "(SELECT `SysMed`.`DoctorTitle`.`title_name` FROM "
                    "`SysMed`.`DoctorTitle` WHERE `SysMed`.`DoctorTitle`.`id_title` = IF (`SysMed`.`Doctors`.`title` = 0, 1, `SysMed`.`Doctors`.`title`) "
                    "    LIMIT 1) as `TitleName`"
                    "FROM `SysMed`.`Doctors`"
                    "LEFT OUTER JOIN `SysMed`.`PersonAddress`"
                    "ON `SysMed`.`Doctors`.`id` = `SysMed`.`PersonAddress`.`id_doctor`;"
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
            "SELECT "
                    "`id` as `ID`, "
                    "`name` as `Name`, "
                    "`lastname` as `Lastname`, "
                    "`pesel` as `PESEL`, "
                    "`position` as `Position`, "
                    "`city` as `City`, "
                    "`street` as `Street`,"
                    "`house_nr` as `House Number`, "
                    "`flat_nr` as `Flat Number`, "
                    "`postal_code` as `Postal Code`,"
                    "(SELECT `SysMed`.`StaffPosition`.`position_name` FROM "
                    "`SysMed`.`StaffPosition` WHERE `SysMed`.`StaffPosition`.`id_position` = IF (`SysMed`.`Staff`.`position` = 0, 1, `SysMed`.`Staff`.`position`) \n"
                    "    LIMIT 1) as `Position`"
                    "FROM `SysMed`.`Staff`"
                    "LEFT OUTER JOIN `SysMed`.`PersonAddress`"
                    "ON `SysMed`.`Staff`.`id` = `SysMed`.`PersonAddress`.`id_staff`;"
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
                "SELECT "
                        "`id_medinfo` as `ID`, "
                        "cast(`disease_date` as date) as `Disease Date`, "
                        "`disease_type` as `Disease Type`, `disease_other_info` as `Other`"
                        "FROM `SysMed`.`PatientMedicalInfo`"
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

void Model::update_pexams(PExamsQueryOrder peqo , QuerySort qs){
    std::cerr << "tttttt!!!!\n";
    this->pExams.clear();

    std::size_t p_id;
    std::size_t exam_id;
    std::size_t doctor_id;
    std::string date;
    std::string time;
    std::string other;

    sql::PreparedStatement *stmt = nullptr;
    sql::ResultSet *res = nullptr;

    std::string peqo_value = Model::QueryParserExams::parsExamQueryOrder(peqo);
    if (peqo_value == "") //????!!!!! why it crashe without it?
        peqo_value = "id_patient_exam";

    std::cerr << "\npeqo: " << peqo_value << "\n";

    std::stringstream ss{};
    ss << "SELECT "
            "`id_patient_exam` as `ID`, "
            "`id_patient` as `PatientID`,"
            "`id_doctor` as `DoctorID`, "
            "cast(`exam_date` as date) as `ExamDate`, "
            "cast(`exam_date` as time) as `ExamTime`, "
            "`other_examdate_info` as `Other`"
            "FROM `SysMed`.`PatientExamDate`"
            "ORDER BY ";
    ss << peqo_value << " ";

    switch (qs){
        case QuerySort::ASC:
            ss << " ASC";
            break;
        case QuerySort::DESC:
            ss << " DESC";
            break;
    }
    stmt = this->connection->prepareStatement(ss.str());

    res = stmt->executeQuery();
    while (res->next()) {
        std::cerr << "...\n";
        p_id = static_cast<std::size_t>(res->getInt("PatientID"));
        exam_id = static_cast<std::size_t>(res->getInt("ID"));
        doctor_id = static_cast<std::size_t>(res->getInt("DoctorID"));
        date = res->getString("ExamDate");
        time = res->getString("ExamTime");
        other = res->getString("Other");

        PatientExamDate ped{exam_id, p_id, doctor_id, date, time, other};
        if (std::find_if(this->patients.begin(), this->patients.end(), [p_id](const auto& e){
            return p_id == e.id;
        }) != this->patients.end()) {
            this->pExams.push_back(ped);
        }
    }

    delete stmt;
    delete res;

}

void Model::update_pexams(std::string& query, PExamsQueryOrder peqo , QuerySort qs) {

    if (query.length() < 6) {
        this->update_patients(PatientQueryOrder::Id, QuerySort::ASC);
        this->update_pexams(peqo, qs);
        return;
    }

    this->update_patients(PatientQueryOrder::Id, QuerySort::ASC);
    this->pExams.clear();

    sql::PreparedStatement *stmt = nullptr;
    sql::ResultSet *res = nullptr;

    std::string peqo_value = Model::QueryParserExams::parsExamQueryOrderSearch(peqo);
    unsigned qs_value = static_cast<unsigned>(qs);

    auto t = Model::QueryParserOperant::parseQueryOperant(query);

    if (std::get<2>(t) == QueryParserOperant::QueryOperant::NONE) {
        auto parsed = Model::QueryParserExams::parse(std::get<0>(t));
        std::cerr << "q: " << query << "? : " << std::get<0>(t) << std::endl;
        std::cerr << "parsed: " << (int)parsed.first << " ask: " << parsed.second  << " peqo: " << peqo_value << " qs: " << qs_value << std::endl;

        if (parsed.first == Model::QTypeExam::NONE)
            return;

        std::string ask = parsed.second;
        std::string ask2 = "";

        std::string query = "", query2 = "", f = "", f2 = "";

        if (parsed.first == QTypeExam::PATIENT) {
            query = ask;
            query2 = ask2;
            f = "pname";
            f2 = "";
        }else if (parsed.first == QTypeExam::PATIENT_NAME_ONLY) {
            query = ask;
            query2 = ask2;
            f = "!pname";
            f2 = "";
        }else if (parsed.first == QTypeExam::PATIENT_LASTNAME_ONLY) {
            query = ask;
            query2 = ask2;
            f = "plastname";
            f2 = "";
        }else if (parsed.first == QTypeExam::PATIENT_PESEL) {
            query = ask;
            query2 = ask2;
            f = "pesel";
            f2 = "";
        }else if (parsed.first == QTypeExam::DOCTOR) {
            query = ask2;
            query2 = ask;
            f = "";
            f2 = "dname";
        }else if (parsed.first == QTypeExam::DOCTOR_LASTNAME_ONLY) {
            query = ask2;
            query2 = ask;
            f = "";
            f2 = "dlastname";
        }else if (parsed.first == QTypeExam::DOCTOR_NAME_ONLY) {
            query = ask2;
            query2 = ask;
            f = "";
            f2 = "!dname";
        }else {
        }

        std::cerr << ">> q: " << query << " q2: " << query2 << " f: " << f << " f2: " << f2 << "\n";

        stmt = this->connection->prepareStatement("set @query = (?)");
        stmt->setString(1, query);
        res = stmt->executeQuery();
        delete res;
        delete stmt;

        stmt = this->connection->prepareStatement("set @query2 = (?)");
        stmt->setString(1, query2);
        res = stmt->executeQuery();
        delete res;
        delete stmt;

        stmt = this->connection->prepareStatement("set @f = (?)");
        stmt->setString(1, f);
        res = stmt->executeQuery();
        delete res;
        delete stmt;

        stmt = this->connection->prepareStatement("set @f2 = (?)");
        stmt->setString(1, f2);
        res = stmt->executeQuery();
        delete res;
        delete stmt;

        stmt = this->connection->prepareStatement("set @order = (?)");
        stmt->setString(1, peqo_value);
        res = stmt->executeQuery();
        delete res;
        delete stmt;

        stmt = this->connection->prepareStatement("set @p = (?)");
        stmt->setInt(1, qs_value);
        res = stmt->executeQuery();
        delete res;
        delete stmt;

        stmt = this->connection->prepareStatement("call find_exam(@query, @f, @query2, @f2, @order, @p);");
        res = stmt->executeQuery();
        delete res;
        delete stmt;

        stmt = this->connection->prepareStatement(
                "select `id_patient_exam` as `ID`,\n"
                        "  `pid` as `PatientID`,\n"
                        "  `did` as `DoctorID`,\n"
                        "  cast(`exam_date` as date) as `ExamDate`,\n"
                        "  cast(`exam_date` as time) as `ExamTime`,\n"
                        "  `other_examdate_info` as `Other`\n"
                        "from texam6;"
        );

    }else if (std::get<2>(t) == QueryParserOperant::QueryOperant::AND){

    }else{

    }


    res = stmt->executeQuery();
    while (res->next()) {
        std::cerr << "...\n";
        std::size_t p_id = static_cast<std::size_t>(res->getInt("PatientID"));
        std::size_t exam_id = static_cast<std::size_t>(res->getInt("ID"));
        std::size_t doctor_id = static_cast<std::size_t>(res->getInt("DoctorID"));
        std::string date = res->getString("ExamDate");
        std::string time = res->getString("ExamTime");
        std::string other = res->getString("Other");

        PatientExamDate ped{exam_id, p_id, doctor_id, date, time, other};
        if (std::find_if(this->patients.begin(), this->patients.end(), [p_id](const auto& e){
            return p_id == e.id;
        }) != this->patients.end()) {
            this->pExams.push_back(ped);
        }
    }
    std::cerr << "ZZZZ: " << this->pExams.size() << "\n";
    delete stmt;
    delete res;

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

std::vector<patient> Model::getPatients(std::string& query, PatientQueryOrder pqo, QuerySort qs) {
    std::cerr << "&&&&&&&&&&&&&: " << query << "\n";
    if (query == "all"){
        this->update_patients(pqo, qs);
        return this->patients;
    }
    
    this->update_patients(query, pqo, qs);
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

std::vector<exam> Model::getExams(std::string& query, PExamsQueryOrder peqo, QuerySort qs){
    std::cerr << "q: " << query << " " << (int)peqo << " " << (int)qs << std::endl;
    if (query == "all") {
        this->update_pexams(peqo, qs);
        return this->pExams;
    }
    this->update_pexams(query, peqo, qs);
    return this->pExams;
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

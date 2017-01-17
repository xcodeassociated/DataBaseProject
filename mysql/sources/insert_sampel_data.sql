INSERT INTO `SysMed`.`Patients` (`id`, `name`, `lastname`, `pesel`) 
	VALUES (null, "Jan", "kowalski", 773849234);
INSERT INTO `SysMed`.`Patients` (`id`, `name`, `lastname`, `pesel`) 
	VALUES (null, "Anna", "Nowak", 647873892);
INSERT INTO `SysMed`.`Patients` (`id`, `name`, `lastname`, `pesel`) 
	VALUES (null, "Mateusz", "Nowicki", 848920342);
INSERT INTO `SysMed`.`Patients` (`id`, `name`, `lastname`, `pesel`) 
	VALUES (null, "Marta", "Kruk", 940384829);
    
INSERT INTO `SysMed`.`Doctors` (`name`, `lastname`, `pesel`, `title`) 
	VALUES ("Adam", "Jankowski", 857463748, 0);
INSERT INTO `SysMed`.`Doctors` (`name`, `lastname`, `pesel`, `title`) 
	VALUES ("Magdalena", "Maj", 232463467, 1);
INSERT INTO `SysMed`.`Doctors` (`name`, `lastname`, `pesel`, `title`) 
	VALUES ("Stefan", "Gips", 647364859, 2);
    
INSERT INTO `SysMed`.`Staff` (`name`, `lastname`, `pesel`, `position`) 
	VALUES ("Maria", "Dorowska", 885937283, 0);
INSERT INTO `SysMed`.`Staff` (`name`, `lastname`, `pesel`, `position`) 
	VALUES ("Joanna", "Opikela", 694038495, 1);
    
INSERT INTO `SysMed`.`PersonAddress` (`id_patient`, `id_doctor`, `id_staff`, `city`, `street`, `house_nr`, `flat_nr`, `postal_code`) 
	VALUES (1, null, null, "Krakow", "Kwiatowa", 10, 11, "30-380");
INSERT INTO `SysMed`.`PersonAddress` (`id_patient`, `id_doctor`, `id_staff`, `city`, `street`, `house_nr`, `flat_nr`, `postal_code`)  
	VALUES (2, null, null, "Krakow", "Bracka", 5, 6, "31-384");
INSERT INTO `SysMed`.`PersonAddress` (`id_patient`, `id_doctor`, `id_staff`, `city`, `street`, `house_nr`, `flat_nr`, `postal_code`) 
	VALUES (3, null, null, "Krakow", "Szewska", 4, 89, "31-351");
INSERT INTO `SysMed`.`PersonAddress` (`id_patient`, `id_doctor`, `id_staff`, `city`, `street`, `house_nr`, `flat_nr`, `postal_code`) 
	VALUES (4, null, null, "Krakow", "Dietla", 9, 11, "32-377");
    
INSERT INTO `SysMed`.`PersonAddress` (`id_patient`, `id_doctor`, `id_staff`, `city`, `street`, `house_nr`, `flat_nr`, `postal_code`)  
	VALUES (null, 1, null, "Krakow", "Mozarta", 120, 121, "30-390");
INSERT INTO `SysMed`.`PersonAddress` (`id_patient`, `id_doctor`, `id_staff`, `city`, `street`, `house_nr`, `flat_nr`, `postal_code`) 
	VALUES (null, 2, null, "Krakow", "Filipa", 6, null, "30-385");
INSERT INTO `SysMed`.`PersonAddress` (`id_patient`, `id_doctor`, `id_staff`, `city`, `street`, `house_nr`, `flat_nr`, `postal_code`) 
	VALUES (null, 3, null, "Krakow", "Podwale", 17, 13, "30-380");
    
INSERT INTO `SysMed`.`PersonAddress` (`id_patient`, `id_doctor`, `id_staff`, `city`, `street`, `house_nr`, `flat_nr`, `postal_code`) 
	VALUES (null, null, 1, "Krakow", "Bochnia", 10, null, "30-342");
INSERT INTO `SysMed`.`PersonAddress` (`id_patient`, `id_doctor`, `id_staff`, `city`, `street`, `house_nr`, `flat_nr`, `postal_code`) 
	VALUES (null, null, 2, "Krakow", "Zielinska", 77, 90, "30-380");
    
-- YYYY-MM-DD HH:MI:SS
INSERT INTO `SysMed`.`PatientMedicalInfo` (`id_patient`, `disease_date`, `disease_type`, `disease_other_info`) 
	VALUES (1, "2016-12-07 00:00:00", "Choroba1", "Choroba1 info...");
INSERT INTO `SysMed`.`PatientMedicalInfo` (`id_patient`, `disease_date`, `disease_type`, `disease_other_info`) 
	VALUES (1, "2016-12-20 00:00:00", "Choroba2", "Choroba2 info...");
INSERT INTO `SysMed`.`PatientMedicalInfo` (`id_patient`, `disease_date`, `disease_type`, `disease_other_info`)
	VALUES (2, "2016-12-20 00:00:00", "Choroba3", "Choroba3 info...");
INSERT INTO `SysMed`.`PatientMedicalInfo` (`id_patient`, `disease_date`, `disease_type`, `disease_other_info`)
	VALUES (3, "2016-11-21 00:00:00", "Choroba4", "Choroba4 info...");
INSERT INTO `SysMed`.`PatientMedicalInfo` (`id_patient`, `disease_date`, `disease_type`, `disease_other_info`)
	VALUES (1, "2017-01-20 00:00:00", "Choroba5", "Choroba5 info...");
INSERT INTO `SysMed`.`PatientMedicalInfo` (`id_patient`, `disease_date`, `disease_type`, `disease_other_info`)
	VALUES (4, "2017-01-05 00:00:00", "Choroba6", "Choroba6 info...");
INSERT INTO `SysMed`.`PatientMedicalInfo` (`id_patient`, `disease_date`, `disease_type`, `disease_other_info`)
	VALUES (2, "2017-01-02 00:00:00", "Choroba7", "Choroba7 info...");
INSERT INTO `SysMed`.`PatientMedicalInfo` (`id_patient`, `disease_date`, `disease_type`, `disease_other_info`)
	VALUES (2, "2016-12-29 00:00:00", "Choroba8", "Choroba8 info...");
    
INSERT INTO `SysMed`.`PatientExamDate` (`id_patient`, `id_doctor`, `exam_date`, `other_examdate_info`)
	VALUES (1, 3, "2017-01-29 14:00:00", "info.... info...");
INSERT INTO `SysMed`.`PatientExamDate` (`id_patient`, `id_doctor`, `exam_date`, `other_examdate_info`)
	VALUES (2, 1, "2017-01-28 11:30:00", "info2.... info2...");
INSERT INTO `SysMed`.`PatientExamDate` (`id_patient`, `id_doctor`, `exam_date`, `other_examdate_info`)
	VALUES (3, 2, "2017-01-29 09:15:00", "info3.... info3...");
INSERT INTO `SysMed`.`PatientExamDate` (`id_patient`, `id_doctor`, `exam_date`, `other_examdate_info`)
	VALUES (3, 3, "2017-01-30 13:20:00", "info4.... info4...");
    
INSERT INTO `SysMed`.`PatientExamResult` (`id_patient`, `id_doctor`, `exam_date`, `diagnosis`, `permit_type`, `permit_form`, `permit_to`)
	VALUES (1, 3, "2016-12-30 16:00:00", "diagnoza1", 0, "2016-12-30 00:00:00", "2017-01-10 00:00:00");
INSERT INTO `SysMed`.`PatientExamResult` (`id_patient`, `id_doctor`, `exam_date`, `diagnosis`, `permit_type`, `permit_form`, `permit_to`)
	VALUES (3, 2, "2017-01-10 11:50:00", "diagnoza2", 1, "2017-01-10 00:00:00", "2017-01-17 00:00:00");
INSERT INTO `SysMed`.`PatientExamResult` (`id_patient`, `id_doctor`, `exam_date`, `diagnosis`, `permit_type`, `permit_form`, `permit_to`)
	VALUES (2, 2, "2017-01-04 15:20:00", "diagnoza3", 0, "2017-01-04 00:00:00", "2017-01-21 00:00:00");
INSERT INTO `SysMed`.`PatientExamResult` (`id_patient`, `id_doctor`, `exam_date`, `diagnosis`, `permit_type`, `permit_form`, `permit_to`)
	VALUES (1, 1, "2017-01-03 12:00:00", "diagnoza4", 1, "2017-01-03 00:00:00", "2017-01-12 00:00:00");
    
INSERT INTO `SysMed`.`PatientExamResultSymptoms` (`id_exam`, `symptom`, `symptom_description`)
	VALUES (1, "sympotm1", "opis sympotmu1");
INSERT INTO `SysMed`.`PatientExamResultSymptoms` (`id_exam`, `symptom`, `symptom_description`)
	VALUES (2, "sympotm2", "opis sympotmu2");
INSERT INTO `SysMed`.`PatientExamResultSymptoms` (`id_exam`, `symptom`, `symptom_description`)
	VALUES (2, "sympotm3", "opis sympotmu3");
INSERT INTO `SysMed`.`PatientExamResultSymptoms` (`id_exam`, `symptom`, `symptom_description`)
	VALUES (3, "sympotm4", "opis sympotmu4");
INSERT INTO `SysMed`.`PatientExamResultSymptoms` (`id_exam`, `symptom`, `symptom_description`)
	VALUES (3, "sympotm5", "opis sympotmu5");
INSERT INTO `SysMed`.`PatientExamResultSymptoms` (`id_exam`, `symptom`, `symptom_description`)
	VALUES (3, "sympotm6", "opis sympotmu6");
INSERT INTO `SysMed`.`PatientExamResultSymptoms` (`id_exam`, `symptom`, `symptom_description`)
	VALUES (4, "sympotm7", "opis sympotmu7");
    
INSERT INTO `SysMed`.`PatientPrescription` (`id_patient`, `id_doctor`, `prescription_date`, `prescription_other_info`)
	VALUES (1, 3, "2016-12-30 16:00:00", "info1...");
INSERT INTO `SysMed`.`PatientPrescription` (`id_patient`, `id_doctor`, `prescription_date`, `prescription_other_info`)
	VALUES (3, 2, "2017-01-10 11:50:00", "info2...");
INSERT INTO `SysMed`.`PatientPrescription` (`id_patient`, `id_doctor`, `prescription_date`, `prescription_other_info`)
	VALUES (2, 2, "2017-01-04 15:20:00", "info3...");
INSERT INTO `SysMed`.`PatientPrescription` (`id_patient`, `id_doctor`, `prescription_date`, `prescription_other_info`)
	VALUES (2, 2, "2017-01-04 15:20:00", "info4...");

INSERT INTO `SysMed`.`PatientPrescriptionElement` (`id_prescription`, `prescription_element`, `prescription_element_dose`, `prescription_element_info`)
	VALUES (1, "lek1", "dawka...", "info...");
INSERT INTO `SysMed`.`PatientPrescriptionElement` (`id_prescription`, `prescription_element`, `prescription_element_dose`, `prescription_element_info`)
	VALUES (1, "lek2", "dawka...", "info...");
INSERT INTO `SysMed`.`PatientPrescriptionElement` (`id_prescription`, `prescription_element`, `prescription_element_dose`, `prescription_element_info`)
	VALUES (2, "lek3", "dawka...", "info...");
INSERT INTO `SysMed`.`PatientPrescriptionElement` (`id_prescription`, `prescription_element`, `prescription_element_dose`, `prescription_element_info`)
	VALUES (3, "lek4", "dawka...", "info...");
INSERT INTO `SysMed`.`PatientPrescriptionElement`(`id_prescription`, `prescription_element`, `prescription_element_dose`, `prescription_element_info`)
	VALUES (3, "lek5", "dawka...", "info...");
INSERT INTO `SysMed`.`PatientPrescriptionElement` (`id_prescription`, `prescription_element`, `prescription_element_dose`, `prescription_element_info`)
	VALUES (4, "lek6", "dawka...", "info...");
    

INSERT INTO `SysMed`.`Login` (`id_staff`, `id_doctor`, `login`, `pass`)
	VALUES (1, null, "s.01", "s1pass");
INSERT INTO `SysMed`.`Login` (`id_staff`, `id_doctor`, `login`, `pass`)
	VALUES (2, null, "s.02", "s2pass");
INSERT INTO `SysMed`.`Login` (`id_staff`, `id_doctor`, `login`, `pass`)
	VALUES (null, 1, "d.01", "d1pass");
INSERT INTO `SysMed`.`Login` (`id_staff`, `id_doctor`, `login`, `pass`)
	VALUES (null, 2, "d.02", "d2pass");
INSERT INTO `SysMed`.`Login` (`id_staff`, `id_doctor`, `login`, `pass`)
	VALUES (null, 3, "d.02", "d3pass");
    
    
INSERT INTO `SysMed`.`DoctorTitle` (`title_name`)
	VALUES ("lek.med");
INSERT INTO `SysMed`.`DoctorTitle` (`title_name`)
	VALUES ("dr");
INSERT INTO `SysMed`.`DoctorTitle` (`title_name`)
	VALUES ("prof.");
    
INSERT INTO `SysMed`.`StaffPosition` (`position_name`)
	VALUES ("RECEPTION");
INSERT INTO `SysMed`.`StaffPosition` (`position_name`)
	VALUES ("NURCE");
    

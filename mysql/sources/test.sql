-- select cast(now() as date) as `CurrentDate`, cast(now() as time) as `CurrentTime`;
-- SELECT `id` FROM `SysMed`.`Patients` ORDER BY `id` DESC LIMIT 1;
-- SAVEPOINT `2017-01-16_23:44:37`;
-- 
-- INSERT INTO `SysMed`.`PatientExamDate` (`id_patient`, `id_doctor`, `exam_date`, `other_examdate_info`)
-- 	VALUES (1, 3, (select cast("2017-01-29" as datetime) + cast("14:00:00" as datetime)) , "info!.... info!...");

select cast( (cast("2017-01-29" as datetime) + cast("14:00:00" as time)) as datetime);

ALTER TABLE SysMed.PersonAddress DROP FOREIGN KEY PersonAddress_ibfk_1;
ALTER TABLE SysMed.PersonAddress DROP FOREIGN KEY PersonAddress_ibfk_2;
ALTER TABLE SysMed.PersonAddress DROP FOREIGN KEY PersonAddress_ibfk_3;
ALTER TABLE SysMed.PatientPrescriptionElement DROP FOREIGN KEY PatientPrescriptionElement_ibfk_1;
ALTER TABLE SysMed.PatientMedicalInfo DROP FOREIGN KEY PatientMedicalInfo_ibfk_1;
ALTER TABLE SysMed.PatientExamResultSymptoms DROP FOREIGN KEY PatientExamResultSymptoms_ibfk_1;
ALTER TABLE SysMed.PatientExamDate DROP FOREIGN KEY PatientExamDate_ibfk_1;
ALTER TABLE SysMed.PatientExamDate DROP FOREIGN KEY PatientExamDate_ibfk_2;
ALTER TABLE SysMed.Login DROP FOREIGN KEY Login_ibfk_1;
ALTER TABLE SysMed.Login DROP FOREIGN KEY Login_ibfk_2;
ALTER TABLE SysMed.PatientPrescription DROP FOREIGN KEY PatientPrescription_ibfk_1;
ALTER TABLE SysMed.PatientPrescription DROP FOREIGN KEY PatientPrescription_ibfk_2;
ALTER TABLE SysMed.PatientExamResult DROP FOREIGN KEY PatientExamResult_ibfk_1;
ALTER TABLE SysMed.PatientExamResult DROP FOREIGN KEY PatientExamResult_ibfk_2;
DROP TABLE SysMed.PersonAddress;
DROP TABLE SysMed.PatientPrescriptionElement;
DROP TABLE SysMed.PatientMedicalInfo;
DROP TABLE SysMed.PatientExamResultSymptoms;
DROP TABLE SysMed.PatientExamDate;
DROP TABLE SysMed.Login;
DROP TABLE SysMed.PatientPrescription;
DROP TABLE SysMed.PatientExamResult;
DROP TABLE SysMed.Staff;
DROP TABLE SysMed.Patients;
DROP TABLE SysMed.Doctors;
DROP TABLE SysMed.StaffPosition;
DROP TABLE SysMed.DoctorTitle;

TRUNCATE TABLE SysMed.PersonAddress;
TRUNCATE TABLE SysMed.PatientPrescriptionElement;
TRUNCATE TABLE SysMed.PatientPrescription;
TRUNCATE TABLE SysMed.PatientExamResultSymptoms;
TRUNCATE TABLE SysMed.PatientExamResult;
TRUNCATE TABLE SysMed.PatientExamDate;
TRUNCATE TABLE SysMed.Login;
TRUNCATE TABLE SysMed.Doctors;
TRUNCATE TABLE SysMed.DoctorTitle;
TRUNCATE TABLE SysMed.PatientMedicalInfo;
TRUNCATE TABLE SysMed.Patients;
TRUNCATE TABLE SysMed.Staff;
TRUNCATE TABLE SysMed.StaffPosition;

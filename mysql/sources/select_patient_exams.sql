SELECT 
`id_patient_exam` as `ID`, `id_patient` as `PatientID`, `id_doctor` as `DoctorID`, cast(`exam_date` as date) as `ExamDate`, cast(`exam_date` as time) as `ExamTime`, `other_examdate_info` as `Other`
FROM `SysMed`.`PatientExamDate`
WHERE `SysMed`.`PatientExamDate`.`id_patient` = 3 ORDER BY `SysMed`.`PatientExamDate`.`exam_date` ASC;
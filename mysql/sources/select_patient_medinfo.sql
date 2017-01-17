SELECT 
`id_medinfo` as `ID`, `disease_date` as `Disease Date`, `disease_type` as `Disease Type`, `disease_other_info` as `Other`
FROM `SysMed`.`PatientMedicalInfo`
WHERE `SysMed`.`PatientMedicalInfo`.`id_patient` = 1 ORDER BY `SysMed`.`PatientMedicalInfo`.`disease_date` DESC;
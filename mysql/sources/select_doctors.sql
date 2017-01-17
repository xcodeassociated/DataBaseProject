SELECT * FROM `SysMed`.`Doctors`;

SELECT 
`id` as `ID`, `name` as `Name`, `lastname` as `Lastname`, `pesel` as `PESEL`,
`city` as `City`, `street` as `Street`, `house_nr` as `House Number`, `flat_nr` as `Flat Number`, `postal_code` as `Postal Code`,
	(SELECT `SysMed`.`DoctorTitle`.`title_name` FROM 
		`SysMed`.`DoctorTitle` WHERE `SysMed`.`DoctorTitle`.`id_title` = IF (`SysMed`.`Doctors`.`title` = 0, 1, `SysMed`.`Doctors`.`title`) 
    LIMIT 1) as `TitleName`
FROM `SysMed`.`Doctors`
	LEFT OUTER JOIN `SysMed`.`PersonAddress`
	ON `SysMed`.`Doctors`.`id` = `SysMed`.`PersonAddress`.`id_doctor`;
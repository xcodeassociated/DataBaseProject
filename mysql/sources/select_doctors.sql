-- SELECT * FROM `SysMed`.`Doctors`;

SELECT 
`id` as `ID`, `name` as `Name`, `lastname` as `Lastname`, `pesel` as `PESEL`, 
`city` as `City`, `street` as `Street`, `house_nr` as `House Number`, `flat_nr` as `Flat Number`, `postal_code` as `Postal Code`
FROM `SysMed`.`Doctors`
	LEFT OUTER JOIN `SysMed`.`PersonAddress`
	ON `SysMed`.`Doctors`.`id` = `SysMed`.`PersonAddress`.`id_doctor`;
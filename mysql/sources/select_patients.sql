-- SELECT * FROM `SysMed`.`Patients`;

SELECT 
`id` as `ID`, `name` as `Name`, `lastname` as `Lastname`, `pesel` as `PESEL`, 
`city` as `City`, `street` as `Street`, IF(`house_nr` = null, "", `house_nr`)  as `House Number`, `flat_nr` as `Flat Number`, `postal_code` as `Postal Code`
FROM `SysMed`.`Patients`
	LEFT OUTER JOIN `SysMed`.`PersonAddress`
	ON `SysMed`.`Patients`.`id` = `SysMed`.`PersonAddress`.`id_patient`;


SELECT
  `id` as `ID`,
  `name` as `Name`,
  `lastname` as `Lastname`,
  `pesel` as `PESEL`,
  `city` as `City`,
  `street` as `Street`,
  IF(`house_nr` = null, "", `house_nr`)  as `House Number`,
  `flat_nr` as `Flat Number`,
  `postal_code` as `Postal Code`
FROM `SysMed`.`Patients`
	LEFT OUTER JOIN `SysMed`.`PersonAddress`
	ON `SysMed`.`Patients`.`id` = `SysMed`.`PersonAddress`.`id_patient`
  ORDER BY `name` DESC;
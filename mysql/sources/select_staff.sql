-- SELECT * FROM `SysMed`.`Staff`;

SELECT 
`id` as `ID`, `name` as `Name`, `lastname` as `Lastname`, `pesel` as `PESEL`, `position` as `Position`,
`city` as `City`, `street` as `Street`, `house_nr` as `House Number`, `flat_nr` as `Flat Number`, `postal_code` as `Postal Code`,
(SELECT `SysMed`.`StaffPosition`.`position_name` FROM 
		`SysMed`.`StaffPosition` WHERE `SysMed`.`StaffPosition`.`id_position` = IF (`SysMed`.`Staff`.`position` = 0, 1, `SysMed`.`Staff`.`position`) 
    LIMIT 1) as `Position`
FROM `SysMed`.`Staff`
	LEFT OUTER JOIN `SysMed`.`PersonAddress`
	ON `SysMed`.`Staff`.`id` = `SysMed`.`PersonAddress`.`id_staff`;
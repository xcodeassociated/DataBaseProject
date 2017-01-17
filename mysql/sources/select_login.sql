SELECT 
`SysMed`.`Staff`.`id` as `ID`, `name` as `Name`, `lastname` as `Lastname`, `pesel` as `PESEL`
FROM `SysMed`.`Staff`
	INNER JOIN `SysMed`.`Login`
	ON `SysMed`.`Staff`.`id` = `SysMed`.`Login`.`id_staff`
    WHERE `SysMed`.`Login`.`login` = 's.01' AND `SysMed`.`Login`.`pass` = 's1pass' LIMIT 1;
    
SELECT 
`SysMed`.`Doctors`.`id` as `ID`, `name` as `Name`, `lastname` as `Lastname`, `pesel` as `PESEL`
FROM `SysMed`.`Doctors`
	INNER JOIN `SysMed`.`Login`
	ON `SysMed`.`Doctors`.`id` = `SysMed`.`Login`.`id_doctor`
    WHERE `SysMed`.`Login`.`login` = 'd.01' AND `SysMed`.`Login`.`pass` = 'd1pass' LIMIT 1;
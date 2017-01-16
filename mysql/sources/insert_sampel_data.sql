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
    


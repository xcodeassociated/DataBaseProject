
CREATE TABLE `SysMed`.`Patients` (
  `id` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(100) NOT NULL,
  `lastname` VARCHAR(100) NOT NULL,
  `pesel` VARCHAR(20) NULL,
  PRIMARY KEY (`id`),
  UNIQUE INDEX `id_UNIQUE` (`id` ASC));

ALTER TABLE `SysMed`.`Patients` DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci;

CREATE TABLE `SysMed`.`Doctors` (
  `id` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(100) NOT NULL,
  `lastname` VARCHAR(100) NOT NULL,
  `pesel` VARCHAR(20) NOT NULL,
  `title` INT UNSIGNED NOT NULL,
  PRIMARY KEY (`id`));

ALTER TABLE `SysMed`.`Doctors` DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci;

CREATE TABLE `SysMed`.`Staff` (
  `id` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(100) NOT NULL,
  `lastname` VARCHAR(100) NOT NULL,
  `pesel` VARCHAR(20) NOT NULL,
  `position` INT UNSIGNED NOT NULL,
  PRIMARY KEY (`id`));

ALTER TABLE `SysMed`.`Staff` DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci;

CREATE TABLE `SysMed`.`PersonAddress` (
  `id_address` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `id_patient` INT UNSIGNED NULL,
  `id_doctor` INT UNSIGNED NULL,
  `id_staff` INT UNSIGNED NULL,
  `city` VARCHAR(45) NOT NULL,
  `street` VARCHAR(45) NOT NULL,
  `house_nr` INT UNSIGNED NOT NULL,
  `flat_nr` INT UNSIGNED NULL,
  `postal_code` VARCHAR(12) NOT NULL,
  PRIMARY KEY (`id_address`),
  UNIQUE INDEX `id_address_UNIQUE` (`id_address` ASC),
  FOREIGN KEY (`id_patient`) REFERENCES `SysMed`.`Patients`(`id`) ON DELETE CASCADE,
  FOREIGN KEY (`id_doctor`) REFERENCES `SysMed`.`Doctors`(`id`) ON DELETE CASCADE,
  FOREIGN KEY (`id_staff`) REFERENCES `SysMed`.`Staff`(`id`) ON DELETE CASCADE
);

ALTER TABLE `SysMed`.`PersonAddress` DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci;

CREATE TABLE `SysMed`.`PatientMedicalInfo` (
  `id_medinfo` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `id_patient` INT UNSIGNED NOT NULL,
  `disease_date` DATETIME NOT NULL,
  `disease_type` VARCHAR(120) NOT NULL,
  `disease_other_info` TEXT NULL,
  PRIMARY KEY (`id_medinfo`),
  UNIQUE INDEX `id_medinfo_UNIQUE` (`id_medinfo` ASC),
  FOREIGN KEY (`id_patient`) REFERENCES `SysMed`.`Patients`(`id`) ON DELETE CASCADE
);

ALTER TABLE `SysMed`.`PatientMedicalInfo` DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci;

CREATE TABLE `SysMed`.`PatientExamDate` (
  `id_patient_exam` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `id_patient` INT UNSIGNED NOT NULL,
  `id_doctor` INT UNSIGNED NOT NULL,
  `exam_date` DATETIME NOT NULL,
  `other_examdate_info` TEXT NULL,
  PRIMARY KEY (`id_patient_exam`),
  FOREIGN KEY (`id_patient`) REFERENCES `SysMed`.`Patients`(`id`) ON DELETE CASCADE,
  FOREIGN KEY (`id_doctor`) REFERENCES `SysMed`.`Doctors`(`id`) ON DELETE CASCADE
);

ALTER TABLE `SysMed`.`PatientExamDate` DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci;




CREATE TABLE `SysMed`.`PatientExamResult` (
  `id_exam_result` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `id_patient` INT UNSIGNED NOT NULL,
  `id_doctor` INT UNSIGNED NOT NULL,
  `exam_date` DATETIME NOT NULL,
  `diagnosis` VARCHAR(200) NOT NULL,
  `permit_type` INT UNSIGNED NULL,
  `permit_form` DATETIME NULL,
  `permit_to` DATETIME NULL,
  PRIMARY KEY (`id_exam_result`),
  FOREIGN KEY (`id_patient`) REFERENCES `SysMed`.`Patients`(`id`) ON DELETE CASCADE,
  FOREIGN KEY (`id_doctor`) REFERENCES `SysMed`.`Doctors`(`id`) ON DELETE CASCADE
);

ALTER TABLE `SysMed`.`PatientExamResult` DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci;

CREATE TABLE `SysMed`.`PatientExamResultSymptoms` (
  `id_exam_symptom` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `id_exam` INT UNSIGNED NOT NULL,
  `symptom` VARCHAR(200) NOT NULL,
  `symptom_description` TEXT NULL,
  PRIMARY KEY (`id_exam_symptom`),
  FOREIGN KEY (`id_exam`) REFERENCES `SysMed`.`PatientExamResult`(`id_exam_result`) ON DELETE CASCADE
);

ALTER TABLE `SysMed`.`PatientExamResultSymptoms` DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci;

CREATE TABLE `SysMed`.`PatientPrescription` (
  `id_prescription` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `id_patient` INT UNSIGNED NOT NULL,
  `id_doctor` INT UNSIGNED NOT NULL,
  `prescription_date` DATETIME NOT NULL,
  `prescription_other_info` TEXT NULL,
  PRIMARY KEY (`id_prescription`),
  FOREIGN KEY (`id_patient`) REFERENCES `SysMed`.`Patients`(`id`) ON DELETE CASCADE,
  FOREIGN KEY (`id_doctor`) REFERENCES `SysMed`.`Doctors`(`id`) ON DELETE CASCADE
);

ALTER TABLE `SysMed`.`PatientPrescription` DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci;

CREATE TABLE `SysMed`.`PatientPrescriptionElement` (
  `id_prescription_element` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `id_prescription` INT UNSIGNED NOT NULL,
  `prescription_element` VARCHAR(200) NOT NULL,
  `prescription_element_dose` VARCHAR(200) NULL,
  `prescription_element_info` TEXT NULL,
  PRIMARY KEY (`id_prescription_element`),
  FOREIGN KEY (`id_prescription`) REFERENCES `SysMed`.`PatientPrescription`(`id_prescription`) ON DELETE CASCADE
);

ALTER TABLE `SysMed`.`PatientPrescriptionElement` DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci;



CREATE TABLE `SysMed`.`Login` (
  `id` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `id_staff` INT UNSIGNED NULL,
  `id_doctor` INT UNSIGNED NULL,
  `login` VARCHAR(200) NOT NULL,
  `pass` VARCHAR(200) NOT NULL,
  PRIMARY KEY (`id`),
  FOREIGN KEY (`id_staff`) REFERENCES `SysMed`.`Staff`(`id`) ON DELETE CASCADE,
  FOREIGN KEY (`id_doctor`) REFERENCES `SysMed`.`Doctors`(`id`) ON DELETE CASCADE
);

ALTER TABLE `SysMed`.`Login` DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci;


CREATE TABLE `SysMed`.`DoctorTitle` (
  `id_title` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `title_name` VARCHAR(10) NOT NULL,
  PRIMARY KEY (`id_title`)
);

ALTER TABLE `SysMed`.`DoctorTitle` DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci;

CREATE TABLE `SysMed`.`StaffPosition` (
  `id_position` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `position_name` VARCHAR(10) NOT NULL,
  PRIMARY KEY (`id_position`)
);

ALTER TABLE `SysMed`.`StaffPosition` DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci;



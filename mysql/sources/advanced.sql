
DROP FUNCTION IF EXISTS getNewInsertedPatientsID;
CREATE FUNCTION getNewInsertedPatientsID()
RETURNS INT
BEGIN
  DECLARE NUM INT DEFAULT 0;
  SELECT MAX(`id`) INTO NUM FROM `SysMed`.`Patients`;
  RETURN NUM;
END;;

SELECT getNewInsertedPatientsID() as 'LastInsertedPatientsID';



DROP FUNCTION IF EXISTS find_patient;
DELIMITER ;;
CREATE FUNCTION find_patient(query VARCHAR(100), field VARCHAR(20)) RETURNS INT
BEGIN
    DECLARE local_variable_name INT;
    SELECT count(`name`) INTO local_variable_name FROM `SysMed`.`Patients` WHERE (
      case
        when field = 'name' then Patients.name LIKE concat('%', query, '%') OR Patients.lastname LIKE concat('%', query, '%') #ELSE
        when field = 'pesel' then Patients.pesel LIKE concat('%', query, '%')
      end
    );

  DROP TEMPORARY TABLE IF EXISTS find_patient_result;
  CREATE TEMPORARY TABLE find_patient_result (select Patients.id as `ID`,
                                Patients.name as `Name`,
                                Patients.lastname as `Lastname`,
                                Patients.pesel as `PESEL`,
                                PersonAddress.city as `City`,
                                PersonAddress.street as `Street`,
                                PersonAddress.house_nr as `House Number`,
                                PersonAddress.flat_nr as `Flat Number`,
                                PersonAddress.postal_code as `Postal Code`
                                              from Patients
   LEFT OUTER JOIN PersonAddress ON Patients.id  = PersonAddress.id_patient
   WHERE (
    case
      WHEN field = 'name' then Patients.name like concat('%', query, '%') or Patients.lastname like concat('%', query, '%') #ELSE
      WHEN field = '!name' then Patients.name like concat('%', query, '%')
      WHEN field = 'lastname' then Patients.lastname like concat('%', query, '%')
      WHEN field = 'pesel' then Patients.pesel like concat('%', query, '%')
    end
   )
  ) ;
  RETURN local_variable_name;
END;;
DELIMITER ;

set @query = 'y';
set @query2 = '6';
set @f = 'pesel';
set @f2 = 'pesel';


select find_patient(@query, @f) as count_;
select * from find_patient_result;

select find_patient(@query2, @f2) as count_;
select * from find_patient_result;



select cast(now() as date) as `CurrentDate`, cast(now() as time) as `CurrentTime`;

START TRANSACTION WITH CONSISTENT SNAPSHOT;
SAVEPOINT 2017_01_18_23_30_47;
COMMIT ;


DROP PROCEDURE IF EXISTS intGetID;
DELIMITER $$
CREATE PROCEDURE intGetID(IN Param1 VARCHAR(255), IN Param2 VARCHAR(255), IN Param3 VARCHAR(255), OUT ParamOUT INT)
BEGIN
  select @c1;
  select @c2;
  select @c3;
  select @out;
  select @query;
  SET @c1 = Param1;
  SET @c2 = Param2;
  SET @c3 = Param3;
  SET @query = concat("SELECT id INTO @out FROM " , @c2 ," WHERE name = @c1");
  PREPARE stmt FROM @query;
  EXECUTE stmt; # USING @out;
  DEALLOCATE PREPARE stmt;
  SET ParamOUT = @out;
END$$
DELIMITER ;

#select @Param0, @Param1, @Param2, @Param3, @ParamOUT;
SET @Param1 = 'Anna', @Param2 = 'Patients', @Param3 ='name', @ParamOUT = 0;
CALL intGetID(@Param1, @Param2, @Param3, @ParamOUT);
SELECT @ParamOUT as output;





DROP PROCEDURE IF EXISTS intGetXlikeY;
DELIMITER $$
CREATE PROCEDURE intGetXlikeY(IN Param0 VARCHAR(255), IN Param1 VARCHAR(255), IN Param2 VARCHAR(255), IN Param3 VARCHAR(255), OUT ParamOUT INT)
BEGIN
  select @c0;
  select @c1;
  select @c2;
  select @c3;
  select @out;
  select @query;
  SET @c0 = Param0;
  SET @c1 = Param1;
  SET @c2 = Param2;
  SET @c3 = Param3;
  SET @query = concat("SELECT ",@c0," INTO @out FROM " , @c2 ," WHERE name = @c1"); #concat("SELECT ", @c0, " INTO @out FROM " , @c2 ," WHERE @c3 = @c1");
  PREPARE stmt FROM @query;
  EXECUTE stmt;# USING @c1;
  DEALLOCATE PREPARE stmt;
  SET ParamOUT = @out;
END$$
DELIMITER ;

#select @Param0, @Param1, @Param2, @Param3, @ParamOUT;
SET @Param0 = 'id', @Param1 = 'nowy', @Param2 = 'Patients', @Param3 ='name', @ParamOUT = 0;
CALL intGetXlikeY(@Param0, @Param1, @Param2, @Param3, @ParamOUT);
SELECT @ParamOUT;




DROP TRIGGER IF EXISTS patientExamDate_LOG_trigger_ins;
CREATE TRIGGER patientExamDate_LOG_trigger_ins BEFORE INSERT ON `SysMed`.`PatientExamDate`
FOR EACH ROW INSERT INTO `SysMed`.`Logs`(`actions`)
VALUES(concat('ADDED Patient Exam: (', new.id_patient_exam, ')', NEW.id_patient, ' -> ', NEW.id_doctor));

DROP TRIGGER IF EXISTS patientExamDate_LOG_trigger_del;
CREATE TRIGGER patientExamDate_LOG_trigger_del BEFORE DELETE ON `SysMed`.`PatientExamDate`
FOR EACH ROW INSERT INTO `SysMed`.`Logs`(`actions`)
VALUES(concat('DELETED Patient Exam: (', old.id_patient_exam, ') ' ,old.id_patient, ' -> ', old.id_doctor));

DROP TRIGGER IF EXISTS patientExamDate_LOG_trigger_upd;
CREATE TRIGGER patientExamDate_LOG_trigger_upd BEFORE UPDATE ON `SysMed`.`PatientExamDate`
FOR EACH ROW INSERT INTO `SysMed`.`Logs`(`actions`)
VALUES(concat('UPDATED Patient Exam: (', old.id_patient_exam, ') ' ,old.id_patient, ' -> ', old.id_doctor, ' => ', new.id_patient, ' -> ', new.id_doctor ));
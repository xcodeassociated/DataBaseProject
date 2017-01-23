use SysMed;

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
CREATE FUNCTION find_patient(query VARCHAR(100), field VARCHAR(20), _order VARCHAR(20), p INT)
  RETURNS INT
BEGIN
    DECLARE local_variable_name INT;
    SELECT count(`name`) INTO local_variable_name FROM `SysMed`.`Patients` WHERE (
      case
        when field = 'name' then Patients.name LIKE concat('%', query, '%') OR Patients.lastname LIKE concat('%', query, '%') #ELSE
        when field = 'pesel' then Patients.pesel LIKE concat('%', query, '%')
      end
    );
  set @_ord = if (_order = null, 'lastname', _order);
  DROP TEMPORARY TABLE IF EXISTS find_patient_result;
  case
    when p = 0 then
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
       ) order by (
        case
          when @_ord = 'name' then name
          when @_ord = 'lastname' then lastname
          when @_ord = 'pesel' then pesel
          when @_ord = 'id' then id
        end
      ) ASC
      ) ;
    when p = 1 then
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
         ) order by (
          case
            when @_ord = 'name' then name
            when @_ord = 'lastname' then lastname
            when @_ord = 'pesel' then pesel
            when @_ord = 'id' then id
          end
        ) DESC
        ) ;
    end case;
  RETURN local_variable_name;
END;;
DELIMITER ;

set @query = 'a';
set @query2 = '6';
set @order = 'name';
set @order2 = 'lastname';
set @p = 0;
set @p2 = 1;
set @f = 'name';
set @f2 = 'pesel';


select find_patient(@query, @f, @order, @p) as count_;
select * from find_patient_result;

select find_patient(@query2, @f2, @order, @p2) as count_;
select * from find_patient_result;







DROP PROCEDURE IF EXISTS find_patient_2;
DELIMITER ;;
CREATE PROCEDURE find_patient_2(in query VARCHAR(100), in field VARCHAR(20), in query2 VARCHAR(100), in field2 VARCHAR(20), in _order VARCHAR(20), in p INT)
BEGIN
  set @_ord = if (_order = null, 'lastname', _order);
  DROP TEMPORARY TABLE IF EXISTS find_patient_result_2;
  case
    when p = 0 then

      drop temporary table if exists find_patient_result_2;
      CREATE TEMPORARY TABLE find_patient_result_2 (select Patients.id as `ID`,
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
       ) order by (
        case
          when @_ord = 'name' then name
          when @_ord = 'lastname' then lastname
          when @_ord = 'pesel' then pesel
          when @_ord = 'id' then id
        end
      ) ASC
      ) ;

      drop temporary table if exists find_patient_result_2_1;
      CREATE TEMPORARY TABLE find_patient_result_2_1 (select Patients.id as `ID`,
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
            WHEN field2 = 'name' then Patients.name like concat('%', query2, '%') or Patients.lastname like concat('%', query2, '%') #ELSE
            WHEN field2 = '!name' then Patients.name like concat('%', query2, '%')
            WHEN field2 = 'lastname' then Patients.lastname like concat('%', query2, '%')
            WHEN field2 = 'pesel' then Patients.pesel like concat('%', query2, '%')
          end
         ) order by (
          case
            when @_ord = 'name' then name
            when @_ord = 'lastname' then lastname
            when @_ord = 'pesel' then pesel
            when @_ord = 'id' then id
          end
        ) ASC
        ) ;

        drop TEMPORARY TABLE if exists final_2;
        CREATE TEMPORARY TABLE final_2 (
          `ID` INT UNSIGNED NOT NULL,
          `Name` VARCHAR(100) NOT NULL,
          `Lastname` VARCHAR(100) NOT NULL,
          `PESEL` VARCHAR(20) NULL,
          `City` VARCHAR(45) NOT NULL,
          `Street` VARCHAR(45) NOT NULL,
          `House Number` INT UNSIGNED NOT NULL,
          `Flat Number` INT UNSIGNED NULL,
          `Postal Code` VARCHAR(12) NOT NULL,
          PRIMARY KEY (`ID`),
        	UNIQUE KEY `ID` (ID)
        );
        INSERT IGNORE INTO final_2 SELECT * FROM find_patient_result_2;
        INSERT IGNORE INTO final_2 SELECT * FROM find_patient_result_2_1;

        drop TEMPORARY TABLE if exists final_22;
        CREATE TEMPORARY TABLE final_22 AS ( select * from final_2 order by (
            case
              when @_ord = 'name' then Name
              when @_ord = 'lastname' then Lastname
              when @_ord = 'pesel' then PESEL
              when @_ord = 'id' then ID
            end
        ) ASC );

        drop TEMPORARY TABLE if exists final_2_and;
        CREATE TEMPORARY TABLE final_2_and AS (
          SELECT * FROM find_patient_result_2
          WHERE ID IN (select ID from find_patient_result_2_1 where (
            case
              WHEN field2 = 'name' then Name like concat('%', query2, '%') or Lastname like concat('%', query2, '%') #ELSE
              WHEN field2 = '!name' then Name like concat('%', query2, '%')
              WHEN field2 = 'lastname' then Lastname like concat('%', query2, '%')
              WHEN field2 = 'pesel' then PESEL like concat('%', query2, '%')
            end
          ) order by (
            case
              when @_ord = 'name' then Name
              when @_ord = 'lastname' then Lastname
              when @_ord = 'pesel' then PESEL
              when @_ord = 'id' then ID
            end
          ) ASC)
        );

    when p = 1 then

        drop temporary table if exists find_patient_result_2;
        CREATE TEMPORARY TABLE find_patient_result_2 (select Patients.id as `ID`,
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
         ) order by (
          case
            when @_ord = 'name' then name
            when @_ord = 'lastname' then lastname
            when @_ord = 'pesel' then pesel
            when @_ord = 'id' then id
          end
        ) DESC
        ) ;

        drop temporary table if exists find_patient_result_2_1;
        CREATE TEMPORARY TABLE find_patient_result_2_1 (select Patients.id as `ID`,
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
            WHEN field2 = 'name' then Patients.name like concat('%', query2, '%') or Patients.lastname like concat('%', query2, '%') #ELSE
            WHEN field2 = '!name' then Patients.name like concat('%', query2, '%')
            WHEN field2 = 'lastname' then Patients.lastname like concat('%', query2, '%')
            WHEN field2 = 'pesel' then Patients.pesel like concat('%', query2, '%')
          end
         ) order by (
          case
            when @_ord = 'name' then name
            when @_ord = 'lastname' then lastname
            when @_ord = 'pesel' then pesel
            when @_ord = 'id' then id
          end
        ) DESC
        ) ;

        drop TEMPORARY TABLE if exists final_2;
        CREATE TEMPORARY TABLE final_2 (
          `ID` INT UNSIGNED NOT NULL,
          `Name` VARCHAR(100) NOT NULL,
          `Lastname` VARCHAR(100) NOT NULL,
          `PESEL` VARCHAR(20) NULL,
          `City` VARCHAR(45) NOT NULL,
          `Street` VARCHAR(45) NOT NULL,
          `House Number` INT UNSIGNED NOT NULL,
          `Flat Number` INT UNSIGNED NULL,
          `Postal Code` VARCHAR(12) NOT NULL,
          PRIMARY KEY (`ID`),
        	UNIQUE KEY `ID` (ID)
        );
        INSERT IGNORE INTO final_2 SELECT * FROM find_patient_result_2;
        INSERT IGNORE INTO final_2 SELECT * FROM find_patient_result_2_1;

        drop TEMPORARY TABLE if exists final_22;
        CREATE TEMPORARY TABLE final_22 AS ( select * from final_2 order by (
            case
              when @_ord = 'name' then Name
              when @_ord = 'lastname' then Lastname
              when @_ord = 'pesel' then PESEL
              when @_ord = 'id' then ID
            end
        ) DESC );

        drop TEMPORARY TABLE if exists final_2_and;
        CREATE TEMPORARY TABLE final_2_and AS (
          SELECT * FROM find_patient_result_2
          WHERE ID IN (select ID from find_patient_result_2_1 where (
            case
              WHEN field2 = 'name' then Name like concat('%', query2, '%') or Lastname like concat('%', query2, '%') #ELSE
              WHEN field2 = '!name' then Name like concat('%', query2, '%')
              WHEN field2 = 'lastname' then Lastname like concat('%', query2, '%')
              WHEN field2 = 'pesel' then PESEL like concat('%', query2, '%')
            end
          ) order by (
              case
                when @_ord = 'name' then Name
                when @_ord = 'lastname' then Lastname
                when @_ord = 'pesel' then PESEL
                when @_ord = 'id' then ID
              end
          ) DESC)
        );
    end case;
  select count(*) into @final_2_count from final_22;
  select count(*) into @final_2_and_count from final_2_and;
END;;
DELIMITER ;

set @query = 'j';
set @query2 = '';
set @order = '!name';
set @order2 = 'pesel';
set @p = 0;
set @p2 = 1;
set @f = '!name';
set @f2 = '';


call find_patient_2(@query, @f, @query2, @f2, @order2, @p2);

select * from final_22;
SELECT * from final_2_and;

select @final_2_count;
SELECT @final_2_and_count;



DROP PROCEDURE IF EXISTS find_exam;
DROP PROCEDURE IF EXISTS find_exam;
DELIMITER $$
CREATE PROCEDURE find_exam(in query VARCHAR(100), in field VARCHAR(20), in query2 VARCHAR(100), in field2 VARCHAR(20), in _order VARCHAR(20), in p INT)
BEGIN
  set @_ord = if (_order = null, 'exam_date', _order);
  DROP TEMPORARY TABLE IF EXISTS texam;
  CREATE TEMPORARY TABLE texam AS (
    select
               id_patient_exam,
               id_patient as pid,
               id_doctor as did,
               exam_date,
               other_examdate_info,
               name as pname,
               lastname as plastname,
               pesel as ppesel
    from PatientExamDate
      LEFT JOIN Patients on id = PatientExamDate.id_patient
  );
  DROP TEMPORARY TABLE IF EXISTS texam3;
  CREATE TEMPORARY TABLE texam3 AS (
        select id_patient_exam,
               pid,
               did,
               exam_date,
               other_examdate_info,
               pname, plastname, ppesel,
               Doctors.name as dname, Doctors.lastname as dlastname, Doctors.title as dtitle
        from texam
        LEFT JOIN Doctors on Doctors.id = texam.did
        WHERE (
          case
            when field = 'pname' then texam.pname like concat('%', query, '%') or texam.plastname like concat('%', query, '%')
            when field = '!pname' then texam.pname like concat('%', query, '%')
            when field = 'plastname' then texam.plastname like concat('%', query, '%')
            when field = 'pesel' then texam.ppesel like concat('%', query, '%')
          end
        )
  );

  DROP TEMPORARY TABLE IF EXISTS texam4;
  CREATE TEMPORARY TABLE texam4 AS (
        select id_patient_exam,
               pid,
               did,
               exam_date,
               other_examdate_info,
               pname, plastname, ppesel,
               Doctors.name as dname, Doctors.lastname as dlastname, Doctors.title as dtitle
        from texam
        LEFT JOIN Doctors on Doctors.id = texam.did
        WHERE (
          case
            when field2 = 'dname' then Doctors.name like concat('%', query2, '%') or Doctors.lastname like concat('%', query2, '%')
            when field2 = '!dname' then Doctors.name like concat('%', query2, '%')
            when field2 = 'dlastname' then Doctors.lastname like concat('%', query2, '%')
          end
        )
  );

  case

    when p = 0 then

       drop TEMPORARY TABLE if exists texam5;
        CREATE TEMPORARY TABLE texam5 (
          `id_patient_exam` INT UNSIGNED NOT NULL,
          `pid` INT NOT NULL,
          `did` INT NOT NULL,
          `exam_date` DATETIME NOT NULL,
          `other_examdate_info` TEXT NULL,
          PRIMARY KEY (`id_patient_exam`),
        	UNIQUE KEY `id_patient_exam` (id_patient_exam)
        );
        INSERT IGNORE INTO texam5 SELECT id_patient_exam, pid, did, exam_date, other_examdate_info  FROM texam3;
        INSERT IGNORE INTO texam5 SELECT id_patient_exam, pid, did, exam_date, other_examdate_info FROM texam4;

        drop TEMPORARY TABLE if exists texam6;
        CREATE TEMPORARY TABLE texam6 AS ( select * from texam5 order by (
            case
              when @_ord = 'pid' then pid
              when @_ord = 'did' then did
              when @_ord = 'exam_date' then exam_date
            end
        ) ASC );

        drop TEMPORARY TABLE if exists texam6_and;
        CREATE TEMPORARY TABLE texam6_and AS (
          SELECT id_patient_exam, pid, did, exam_date, other_examdate_info FROM texam3
          WHERE id_patient_exam IN (select id_patient_exam from texam4 where (
               case
                  when field2 = 'dname' then dname like concat('%', query2, '%') or dlastname like concat('%', query2, '%')
                  when field2 = '!dname' then dname like concat('%', query2, '%')
                  when field2 = 'dlastname' then dlastname like concat('%', query2, '%')
                end
          ) order by (
              case
                when @_ord = 'pid' then pid
                when @_ord = 'did' then did
                when @_ord = 'exam_date' then exam_date
              end
          ) ASC )
        );
        drop TEMPORARY TABLE if exists texam7_and;
        CREATE TEMPORARY TABLE texam7_and AS ( select * from texam6_and
        order by (
                  case
                    when @_ord = 'pid' then pid
                    when @_ord = 'did' then did
                    when @_ord = 'exam_date' then exam_date
                  end
              ) ASC
        );

    when p = 1 then

        drop TEMPORARY TABLE if exists texam5;
        CREATE TEMPORARY TABLE texam5 (
          `id_patient_exam` INT UNSIGNED NOT NULL,
          `pid` INT NOT NULL,
          `did` INT NOT NULL,
          `exam_date` DATETIME NOT NULL,
          `other_examdate_info` TEXT NULL,
          PRIMARY KEY (`id_patient_exam`),
        	UNIQUE KEY `id_patient_exam` (id_patient_exam)
        );
        INSERT IGNORE INTO texam5 SELECT id_patient_exam, pid, did, exam_date, other_examdate_info  FROM texam3;
        INSERT IGNORE INTO texam5 SELECT id_patient_exam, pid, did, exam_date, other_examdate_info FROM texam4;

        drop TEMPORARY TABLE if exists texam6;
        CREATE TEMPORARY TABLE texam6 AS ( select * from texam5 order by (
            case
              when @_ord = 'pid' then pid
              when @_ord = 'did' then did
              when @_ord = 'exam_date' then exam_date
            end
        ) DESC );

        drop TEMPORARY TABLE if exists texam6_and;
        CREATE TEMPORARY TABLE texam6_and AS (
          SELECT id_patient_exam, pid, did, exam_date, other_examdate_info FROM texam3
          WHERE id_patient_exam IN (select id_patient_exam from texam4 where (
               case
                  when field2 = 'dname' then dname like concat('%', query2, '%') or dlastname like concat('%', query2, '%')
                  when field2 = '!dname' then dname like concat('%', query2, '%')
                  when field2 = 'dlastname' then dlastname like concat('%', query2, '%')
                end
          ) )
        );
        drop TEMPORARY TABLE if exists texam7_and;
        CREATE TEMPORARY TABLE texam7_and AS ( select * from texam6_and
        order by (
                  case
                    when @_ord = 'pid' then pid
                    when @_ord = 'did' then did
                    when @_ord = 'exam_date' then exam_date
                  end
              ) DESC
        );

  END CASE;

select count(*) into @find_exam_count from texam6;
select count(*) into @find_exam_and_count from texam6_and;
END$$
DELIMITER ;


set @order = 'pid';
set @order2 = 'exam_date';
set @p = 0;
set @p2 = 1;

set @query = '6'; -- A
set @f = 'pesel'; -- A
set @query2 = 'f'; -- B
set @f2 = 'dname'; -- B

call find_exam(@query, @f, @query2, @f2, @order, @p);

select `id_patient_exam` as `ID`,
  `pid` as `PatientID`,
  `did` as `DoctorID`,
  cast(`exam_date` as date) as `ExamDate`,
  cast(`exam_date` as time) as `ExamTime`,
  `other_examdate_info` as `Other`
from texam7_and;

select `id_patient_exam` as `ID`,
  `pid` as `PatientID`,
  `did` as `DoctorID`,
  cast(`exam_date` as date) as `ExamDate`,
  cast(`exam_date` as time) as `ExamTime`,
  `other_examdate_info` as `Other`
from texam6;

select @find_exam_count;
select @find_exam_and_count;


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
  ORDER BY name DESC;


SELECT
  `id_patient_exam` as `ID`,
  `id_patient` as `PatientID`,
  `id_doctor` as `DoctorID`,
  cast(`exam_date` as date) as `ExamDate`,
  cast(`exam_date` as time) as `ExamTime`,
  `other_examdate_info` as `Other`
FROM `SysMed`.`PatientExamDate`
ORDER BY `exam_date` ASC;


select cast(now() as date) as `CurrentDate`, cast(now() as time) as `CurrentTime`;





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
  SET @query = concat("SELECT id INTO @out FROM " , @c2 ," WHERE @c3 = @c1");
  PREPARE stmt FROM @query;
  EXECUTE stmt; # USING @out;
  DEALLOCATE PREPARE stmt;
  SET ParamOUT = @out;
END$$
DELIMITER ;

select @Param0, @Param1, @Param2, @Param3, @ParamOUT;
SET @Param1 = 'Anna', @Param2 = 'Patients', @Param3 ='name', @ParamOUT = 0;
CALL intGetID(@Param1, @Param2, @Param3, @ParamOUT);
SELECT @ParamOUT as output;



DROP PROCEDURE IF EXISTS intGetXequalsY;
DELIMITER $$
CREATE PROCEDURE intGetXequalsY(IN Param0 VARCHAR(255), IN Param1 VARCHAR(255), IN Param2 VARCHAR(255), IN Param3 VARCHAR(255))
BEGIN
  SET @c0 = Param0;
  SET @c1 = Param1;
  SET @c2 = Param2;
  SET @c3 = Param3;
  DROP VIEW IF EXISTS intGetXequalsY;
  SET @query = concat("CREATE VIEW intGetXequalsY as SELECT ", @c0, " FROM " , @c2 ," WHERE ", @c3, " = '", @c1, "'");
  PREPARE stmt FROM @query;
  EXECUTE stmt;# USING @c1;
  DEALLOCATE PREPARE stmt;
END$$
DELIMITER ;

#select @Param0, @Param1, @Param2, @Param3, @ParamOUT;
SET @Param0 = 'id', @Param1 = 'Marta', @Param2 = 'Patients', @Param3 ='name';
CALL intGetXequalsY(@Param0, @Param1, @Param2, @Param3);
SELECT * from intGetXequalsY;



DROP PROCEDURE IF EXISTS intGetXlikeY;
DELIMITER $$
CREATE PROCEDURE intGetXlikeY(IN Param0 VARCHAR(255), IN Param1 VARCHAR(255), IN Param2 VARCHAR(255), IN Param3 VARCHAR(255))
BEGIN
  SET @c0 = Param0;
  SET @c1 = Param1;
  SET @c2 = Param2;
  SET @c3 = Param3;
  DROP VIEW IF EXISTS intGetXlikeYresult;
  SET @query = concat("CREATE VIEW intGetXlikeYresult as SELECT ", @c0, " FROM " , @c2 ," WHERE ", @c3, " like('%", @c1, "%')");
  PREPARE stmt FROM @query;
  EXECUTE stmt;# USING @c1;
  DEALLOCATE PREPARE stmt;
END$$
DELIMITER ;

#select @Param0, @Param1, @Param2, @Param3, @ParamOUT;
SET @Param0 = 'id', @Param1 = 'J', @Param2 = 'Patients', @Param3 ='name';
CALL intGetXlikeY(@Param0, @Param1, @Param2, @Param3);
SELECT * from intGetXlikeYresult;




DROP TABLE IF EXISTS `SysMed`.`Logs`;
CREATE TABLE `SysMed`.`Logs` (
  `id` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `date` DATETIME NOT NULL DEFAULT NOW(),
  `actions` VARCHAR(255) NOT NULL,
  PRIMARY KEY (`id`)
);
ALTER TABLE `SysMed`.`Logs` DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci;


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



DROP TRIGGER IF EXISTS patients_LOG_trigger_ins;
CREATE TRIGGER patients_LOG_trigger_ins BEFORE INSERT ON `SysMed`.`Patients`
FOR EACH ROW INSERT INTO `SysMed`.`Logs`(`actions`)
VALUES(concat('ADDED Patient: (', new.id, ') : ', NEW.name, ', ', NEW.lastname, ', ', new.pesel));

DROP TRIGGER IF EXISTS patients_LOG_trigger_del;
CREATE TRIGGER patients_LOG_trigger_del BEFORE DELETE ON `SysMed`.`Patients`
FOR EACH ROW INSERT INTO `SysMed`.`Logs`(`actions`)
VALUES(concat('DELETED Patient: (', old.id, ') : ', old.name, ', ', old.lastname, ', ', old.pesel));

DROP TRIGGER IF EXISTS patients_LOG_trigger_upd;
CREATE TRIGGER patients_LOG_trigger_upd BEFORE UPDATE ON `SysMed`.`Patients`
FOR EACH ROW INSERT INTO `SysMed`.`Logs`(`actions`)
VALUES(concat('DELETED Patient: (', old.id, ') : ', old.name, ', ', old.lastname, ', ', old.pesel, ' -> ', new.name, ', ', new.lastname, ', ', new.pesel));



DROP TRIGGER IF EXISTS personaddr_LOG_trigger_ins;
CREATE TRIGGER personaddr_LOG_trigger_ins BEFORE INSERT ON `SysMed`.`PersonAddress`
FOR EACH ROW INSERT INTO `SysMed`.`Logs`(`actions`)
VALUES(concat('ADDED Person addres for: ', new.id_patient, ' ', new.id_doctor, ' ', new.id_staff));

DROP TRIGGER IF EXISTS personaddr_LOG_trigger_del;
CREATE TRIGGER personaddr_LOG_trigger_del BEFORE DELETE ON `SysMed`.`PersonAddress`
FOR EACH ROW INSERT INTO `SysMed`.`Logs`(`actions`)
VALUES (concat('UPDATED Person addres for :', old.id_patient, ' ', old.id_doctor, ' ', old.id_staff));

DROP TRIGGER IF EXISTS personaddr_LOG_trigger_upd;
CREATE TRIGGER personaddr_LOG_trigger_upd BEFORE UPDATE ON `SysMed`.`PersonAddress`
FOR EACH ROW INSERT INTO `SysMed`.`Logs`(`actions`)
VALUES (concat('UPDATED Person addres for :', old.id_patient, ' ', old.id_doctor, ' ', old.id_staff));

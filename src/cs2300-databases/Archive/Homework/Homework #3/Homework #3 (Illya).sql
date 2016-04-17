/*
    Homework #3

    Due Date: April 11, 2016
    Author(s): Illya Starikov, Claire Trebing, Jason Young.
    Copyright © 2016. All rights reserved.
*/

/*
Questions For Dan Lin
- Social security limited to a number between 0 AND 9
- Date to be stored as a date
- PRIMARY KEYs NOT NULL by default, SET them anyway?
- References created post creation of tables
*/

/*-----------------------------------------------------------------------
 *  PROBLEM #1
 *-----------------------------------------------------------------------*/
CREATE TABLE EMPLOYEE (
    Fname varchar(15) NOT NULL,
    Minit char(1),
    Lname varchar(15) NOT NULL,
    Ssn numeric(9, 0),
    Bdate date NOT NULL,
    Address varchar(50) NOT NULL,
    Sex char(1) CHECK(Sex = 'M' OR Sex = 'F'),
    Salary decimal(12, 2),
    Super_ssn numeric(9, 0),
    Dno integer,
    PRIMARY KEY(Ssn)
);

CREATE TABLE DEPARTMENT (
    Dname VARCHAR(25) NOT NULL,
    Dnumber integer CHECK(Dnumber >= 0),
    Mgr_ssn numeric(9, 0),
    Mgr_start_date date,
    PRIMARY KEY(Dnumber)
);

CREATE TABLE DEPT_LOCATIONS (
    Dnumber integer,
    Dlocation varchar(25),
    PRIMARY KEY(DNumber, Dlocation)
);

CREATE TABLE PROJECT (
    Pname varchar(15) NOT NULL,
    Pnumber integer,
    Plocation varchar(25) NOT NULL,
    Dnum integer NOT NULL,
    PRIMARY KEY(Pnumber)
);

CREATE TABLE WORKS_ON (
    Essn numeric(9, 0),
    Pno integer,
    Hours float DEFAULT(0) CHECK (Hours >= 0),
    PRIMARY KEY (Essn, Pno)
);

CREATE TABLE DEPENDENT (
    Essn numeric(9, 0),
    Dependent_name varchar(15),
    Sex varchar(1) CHECK(Sex = 'M' or Sex = 'F'),
    Bdate date NOT NULL,
    Relationship varchar(15) NOT NULL,
    PRIMARY KEY (Essn, Dependent_name)
);

ALTER TABLE EMPLOYEE ADD CONSTRAINT Ssn FOREIGN KEY (Super_ssn) REFERENCES EMPLOYEE;
ALTER TABLE EMPLOYEE ADD CONSTRAINT Dnumber FOREIGN KEY (Dno) REFERENCES DEPARTMENT;
ALTER TABLE DEPARTMENT ADD CONSTRAINT Ssn FOREIGN KEY (Mgr_ssn) REFERENCES EMPLOYEE;
ALTER TABLE DEPT_LOCATIONS ADD CONSTRAINT Dnumber FOREIGN KEY (Dnumber) REFERENCES DEPARTMENT;
ALTER TABLE PROJECT ADD CONSTRAINT Dnumber FOREIGN KEY (Dnum) REFERENCES DEPARTMENT;
ALTER TABLE WORKS_ON ADD CONSTRAINT Ssn FOREIGN KEY (Essn) REFERENCES EMPLOYEE;
ALTER TABLE WORKS_ON ADD CONSTRAINT PNumber FOREIGN KEY (Pno) REFERENCES PROJECT;
ALTER TABLE DEPENDENT ADD CONSTRAINT Ssn FOREIGN KEY (Essn) REFERENCES EMPLOYEE;


/*-----------------------------------------------------------------------
 *  PROBLEM #2
 *-----------------------------------------------------------------------*/
INSERT INTO EMPLOYEE (Fname, Minit, Lname, Ssn, Bdate, Address, Sex, Salary) VALUES
    ('Franklin', 'T', 'Wong', 333445555, '1955-12-08', '638 Voss, Houston, TX', 'M', 40000),
    ('John', 'B', 'Smith', 123456789, '1965-01-09', '731 Fondren, Houston, TX', 'M', 30000),
    ('Alicia', 'J', 'Zelaya', 999887777, '1968-01-19', '3321 Castle, Spring, TX', 'F', 25000),
    ('Jennifer', 'S', 'Wallace', 987654321, '1941-06-20', '291 Berry, Bellaire, TX', 'F', 43000),
    ('Ramesh', 'K', 'Narayan', 666884444, '1962-09-15', '975 Fire Oak, Humble,TX', 'M', 38000),
    ('Joyce', 'A', 'English', 453453453, '1972-07-31', '5631 Rice, Houston, TX', 'F', 25000),
    ('Ahmad', 'V', 'Jabbar', 987987987, '1969-03-29', '980 Dallas, Houston, TX', 'M', 25000),
    ('James', 'E', 'Borg', 888665555, '1937-11-10', '450 Stone, Houston, TX', 'M', 55000);

UPDATE EMPLOYEE SET Super_ssn = 333445555 WHERE Ssn = 123456789;
UPDATE EMPLOYEE SET Super_ssn = 888665555 WHERE Ssn = 333445555;
UPDATE EMPLOYEE SET Super_ssn = 987654321 WHERE Ssn = 999887777;
UPDATE EMPLOYEE SET Super_ssn = 888665555 WHERE Ssn = 987654321;
UPDATE EMPLOYEE SET Super_ssn = 333445555 WHERE Ssn = 666884444;
UPDATE EMPLOYEE SET Super_ssn = 333445555 WHERE Ssn = 453453453;
UPDATE EMPLOYEE SET Super_ssn = 987654321 WHERE Ssn = 987987987;
UPDATE EMPLOYEE SET Super_ssn = NULL      WHERE Ssn = 888665555;

INSERT INTO DEPARTMENT (Dname, Dnumber, Mgr_ssn, Mgr_start_date) VALUES
    ('Research', 5, 333445555, '1988-05-22'),
    ('Administration', 4, 987654321, '1995-01-01'),
    ('Headquarters', 1, 888665555, '1981-06-19');

UPDATE EMPLOYEE SET Dno = 5 WHERE Ssn = 123456789;
UPDATE EMPLOYEE SET Dno = 5 WHERE Ssn = 333445555;
UPDATE EMPLOYEE SET Dno = 4 WHERE Ssn = 999887777;
UPDATE EMPLOYEE SET Dno = 4 WHERE Ssn = 987654321;
UPDATE EMPLOYEE SET Dno = 5 WHERE Ssn = 666884444;
UPDATE EMPLOYEE SET Dno = 5 WHERE Ssn = 453453453;
UPDATE EMPLOYEE SET Dno = 4 WHERE Ssn = 987987987;
UPDATE EMPLOYEE SET Dno = 1 WHERE Ssn = 888665555;

INSERT INTO DEPT_LOCATIONS (Dnumber, Dlocation) VALUES
    (1, 'Houston'),
    (4, 'Stafford'),
    (5, 'Bellaire'),
    (5, 'Sugarland'),
    (5, 'Houston');

INSERT INTO PROJECT (Pname, Pnumber, Plocation, Dnum) VALUES
    ('ProductX', 1, 'Bellaire', 5),
    ('ProductY', 2, 'Sugarland', 5),
    ('ProductZ', 3, 'Houston', 5),
    ('Computerization', 10, 'Stafford', 4),
    ('Reorganization', 20, 'Houston', 1),
    ('Newbenefits', 30, 'Stafford', 4);

INSERT INTO WORKS_ON (Essn, Pno, Hours) VALUES
    (123456789, 1, 32.5),
    (123456789, 2, 7.5),
    (666884444, 3, 40.0),
    (453453453, 1, 20.0),
    (453453453, 2, 20.0),
    (333445555, 2, 10.0),
    (333445555, 3, 10.0),
    (333445555, 10, 10.0),
    (333445555, 20, 10.0),
    (999887777, 30, 30.0),
    (999887777, 10, 10.0),
    (987987987, 10, 35.0),
    (987987987, 30, 5.0),
    (987654321, 30, 20.0),
    (987654321, 20, 15.0),
    (888665555, 20, NULL);

INSERT INTO DEPENDENT (Essn, Dependent_name, Sex, Bdate, Relationship) VALUES
    (333445555, 'Alice', 'F', '1986-04-05', 'Daughter'),
    (333445555, 'Theodore', 'M', '1983-10-25', 'Son'),
    (333445555, 'Joy', 'F', '1958-05-03', 'Spouse'),
    (987654321, 'Abner', 'M', '1942-02-28', 'Spouse'),
    (123456789, 'Michael', 'M', '1988-01-04', 'Son'),
    (123456789, 'Alice', 'F', '1988-12-30', 'Daughter'),
    (123456789, 'Elizabeth', 'F', '1967-05-05', 'Spouse');


/*-----------------------------------------------------------------------
 *  PROBLEM #3
 *-----------------------------------------------------------------------*/
SELECT *
FROM EMPLOYEE;

SELECT *
FROM DEPARTMENT;

SELECT *
FROM DEPT_LOCATIONS;

SELECT *
FROM PROJECT;

SELECT *
FROM WORKS_ON;

SELECT *
FROM DEPENDENT;

/*-----------------------------------------------------------------------
 *  PROBLEM #3
 *-----------------------------------------------------------------------*/
SELECT Fname, Minit, Lname
FROM PROJECT, WORKS_ON, EMPLOYEE
WHERE Dno = 5 AND Hours > 10 AND Pname = 'ProductX'
    AND WORKS_ON.Essn = EMPLOYEE.Ssn
    AND WORKS_ON.Pno = PROJECT.Pnumber;

SELECT Fname, Minit, Lname
FROM DEPENDENT, EMPLOYEE
WHERE Dependent_name = Fname
    AND EMPLOYEE.Ssn = DEPENDENT.Essn;

SELECT Fname, Minit, Lname
FROM EMPLOYEE
WHERE EMPLOYEE.Super_ssn = (
    SELECT SSN
    FROM EMPLOYEE
    WHERE EMPLOYEE.Fname = 'Franklin' AND EMPLOYEE.Lname = 'Wong');

SELECT sum(Hours), Pname
FROM WORKS_ON, PROJECT
WHERE WORKS_ON.Pno = PROJECT.Pnumber
group by Pname;

SELECT Fname, Minit, Lname
FROM EMPLOYEE, WORKS_ON
WHERE NOT EXISTS(SELECT PNumber FROM PROJECT WHERE PNumber NOT IN (SELECT Pno FROM WORKS_ON WHERE WORKS_ON.Pno = PROJECT.Pnumber))
    AND WORKS_ON.Essn = EMPLOYEE.Ssn;

SELECT Fname, Minit, Lname
FROM EMPLOYEE LEFT JOIN WORKS_ON ON EMPLOYEE.Ssn = WORKS_ON.Essn
WHERE WORKS_ON.Essn IS NULL;

SELECT Dname, avg(Salary)
FROM EMPLOYEE, DEPARTMENT
WHERE EMPLOYEE.Dno = DEPARTMENT.Dnumber
group by Dnumber;

SELECT avg(Salary)
FROM EMPLOYEE
WHERE EMPLOYEE.Sex = 'F';

SELECT Fname, Minit, Lname, Address
FROM EMPLOYEE, PROJECT, DEPT_LOCATIONS
WHERE Dlocation = 'Houston' AND Plocation = 'Houston'
    AND DEPT_LOCATIONS.Dnumber = EMPLOYEE.Dno
    AND PROJECT.Dnum = EMPLOYEE.Dno;

SELECT Lname
FROM EMPLOYEE LEFT JOIN DEPENDENT ON EMPLOYEE.Ssn = DEPENDENT.Essn
WHERE DEPENDENT.essn IS NULL;


/*-----------------------------------------------------------------------
 *  PROBLEM #5
 *-----------------------------------------------------------------------*/
DROP TABLE DEPT_LOCATIONS CASCADE;
DROP TABLE PROJECT CASCADE;
DROP TABLE WORKS_ON CASCADE;
DROP TABLE DEPENDENT CASCADE;
DROP TABLE EMPLOYEE CASCADE;
DROP TABLE DEPARTMENT CASCADE;
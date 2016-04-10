SELECT  Fname, Minit, Lname
FROM    EMPLOYEE, WORKS_ON, PROJECT
WHERE   Dno = 5 AND Hours >= 10 AND Pname = 'ProductX' and Pnumber = Pno

SELECT  Fname, Minit, Lname
FROM    EMPLOYEE, DEPENDENT
WHERE   Fname = Dependent_name

SELECT  E.Fname, E.Minit, E.Lname
FROM    EMPLOYEE AS E
WHERE

SELECT  Pname, SUM(Hours)
FROM    PROJECT P, WORKS_ON W
WHERE   P.Pnumber = W.pno GROUP BY P.Pname;

SELECT  Fname, Minit, Lname
FROM    EMPLOYEE, WORKS_ON, PROJECT
WHERE   NOT EXISTS ((SELECT Pnumber FROM PROJECT) MINUS (SELECT Pno FROM WORKS_ON WHERE Ssn = Essn));

SELECT  Fname, Minit, Lname
FROM    EMPLOYEE
WHERE   NOT EXISTS (SELECT Pno FROM WORKS_ON WHERE Ssn = Essn);

SELECT  Dname, AVG(Salary)
FROM    EMPLOYEE, DEPARTMENT
WHERE   Dno = Dnumber GROUP BY Dname;

SELECT  AVG(Salary)
FROM    EMPLOYEE
WHERE   Sex = 'F';

SELECT  Fname, Minit, Lname, Address
FROM    EMPLOYEE E, WORKS_ON W
WHERE   E.Ssn = W.Essn AND W.Pno IN (SELECT Pnumber FROM PROJECT WHERE Plocation = 'Houston')
    MINUS SELECT Fname, Minit, Lname, Address FROM EMPLOEE E WHERE Dno NOT IN (SELECT
    Dnumber FROM DEPT_LOCATIONS WHERE Dlocation = 'Houston');

SELECT  Lname
FROM    EMPLOYEE E, DEPARTMENT D
WHERE   E.Ssn = D.Mgr_ssn AND NOT EXISTS (SELECT * FROM DEPARTMENT WEHRE Mgr_ssn = Essn); ​
CREATE OR REPLACE FUNCTION new_user(
    id numeric(9, 0),
    username varchar(30),
    email varchar(50),
    heightFeet numeric(1, 0),
    heightInches numeric(2, 0),
    birthdate date,
    goal int,
    password varchar(50),
    joinDate date,
    gender char,
    firstName varchar(50),
    mInitial char,
    lastName varchar(50)
)
returns setof record as $$
BEGIN
    INSERT INTO USERS(UiD, Username, Email, HeightFeet, HeightInches, Birthdate, Goal, Password, JoinDate, Gender, FName, Minit, LName) VALUES
        (id, username, email, heightFeet, heightInches, birthdate, goal, password, joinDate, gender, firstName, mInitial, lastName);
END;
$$ language plpgsql;
-- This allows users to find other users based on first and last name
CREATE OR REPLACE FUNCTION query_user(firstName varchar(50), lastName varchar(50))
RETURNS record AS $foundUser$
declare
    foundUser record;
BEGIN
   SELECT * into foundUser FROM USERS WHERE firstName = USERS.FName and lastName = USERS.Lname;
   RETURN foundUser;
END;
$foundUser$ LANGUAGE plpgsql;
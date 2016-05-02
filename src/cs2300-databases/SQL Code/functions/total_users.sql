CREATE OR REPLACE FUNCTION total_users()
RETURNS integer AS $total$
declare
    total integer;
BEGIN
   SELECT count(*) into total FROM USERS;
   RETURN total;
END;
$total$ LANGUAGE plpgsql;
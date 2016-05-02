-- DEBUG PURPOSES
-- drop FUNCTION user_leaderboards();

CREATE OR REPLACE FUNCTION user_leaderboards()
RETURNS TABLE(FName varchar(50), LName varchar(50), count bigint) as $$
BEGIN
    RETURN QUERY
    select Users.FName, Users.Lname, count(WORKOUTS.UiD)
    from WORKOUTS, USERS
    where Users.UiD = WORKOUTS.UiD
    group by WORKOUTS.UiD, Users.FName, Users.Lname
    order by count(WORKOUTS.UiD) DESC
    LIMIT 10;
END;
$$ LANGUAGE plpgsql;

-- select user_leaderboards();
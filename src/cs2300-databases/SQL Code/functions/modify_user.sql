-- -- DEBUG PURPOSES
-- drop FUNCTION modify_user(
--     userID numeric(9, 0),
--     newUsername varchar(50),
--     newHeightFeet numeric(1, 0),
--     newHeightInches numeric(2, 0),
--     newGoal int,
--     newPassword varchar(50),
--     newGender char
-- );

CREATE OR REPLACE FUNCTION modify_user(
    userID numeric(9, 0),
    newUsername varchar(50),
    newHeightFeet numeric(1, 0),
    newHeightInches numeric(2, 0),
    newGoal int,
    newPassword varchar(50),
    newGender char
)
returns setof record as $$
BEGIN
    IF (newUsername != '0') THEN
        UPDATE USERS SET Username = newUsername WHERE userID = UiD;
    END IF;

    IF (newHeightFeet != 0) THEN
        UPDATE USERS SET HeightFeet = newHeightFeet WHERE userID = UiD;
    END IF;

    IF (newHeightInches != 0) THEN
        UPDATE USERS SET HeightInches = newHeightInches WHERE userID = UiD;
    END IF;

    IF (newGoal != 0) THEN
        UPDATE USERS SET Goal = newGoal WHERE userID = UiD;
    END IF;

    IF (newPassword != '0') THEN
        UPDATE USERS SET Password = newPassword WHERE userID = UiD;
    END IF;

    IF (newGender != '0') THEN
        UPDATE USERS SET Gender = newGender WHERE userID = UiD;
    END IF;
END;

$$ language plpgsql;
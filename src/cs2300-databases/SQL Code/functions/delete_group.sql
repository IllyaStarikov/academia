CREATE OR REPLACE FUNCTION delete_group(groupID numeric(9, 0))
returns setof record as $$
BEGIN
    DELETE FROM GROUPS WHERE GROUPS.GiD = groupID;
END;
$$ language plpgsql;

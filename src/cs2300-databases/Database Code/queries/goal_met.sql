-- USERS WHO HAVE MET THEIR GOAL AT LEAST ONCE
select USERS.Fname, USERS.Lname
from USERS, WEIGHT
where USERS.UiD = WEIGHT.UiD
group by USERS.Fname, USERS.Lname, WEIGHT.weight, USERS.goal
having WEIGHT.weight < USERS.goal;
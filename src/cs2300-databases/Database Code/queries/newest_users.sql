-- The 50 Newest Users
select Users.Fname, Users.Lname, Users.JoinDate
from USERS
group by Users.JoinDate, Users.Fname, Users.Lname
order by JoinDate DESC
LIMIT 50;
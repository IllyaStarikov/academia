-- GROUP SIZE
select Title, count(MEMBERS.UiD)
from GROUPS, MEMBERS
group by GROUPS.Title
order by count(MEMBERS.UiD) DESC;
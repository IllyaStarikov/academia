/*
# Notes For Jason.

- Titles are of fixed length, 20
- Messages are unlimited length
*/

create table POST (
    PiD integer not null,
    FiD integer not null,
    Message text not null,
    DateStamp date not null,
    Title varchar(20) not null,
    primary key(Pid, Fid)
);

create table FORUM (
    FiD integer not null,
    Title varchar(20) not null,
    DateCreated date,
    PublicOrPrivate boolean,
    GiD integer not null,
    primary key(FiD)
);

create table GROUPS (
    GiD integer,
    Moderator integer,
    Title varchar(20),
    StartDate date,
    primary key(GiD)
);

create table WORKOUT (
    WiD integer,
    Duration time,
    Title varchar(20),
    IntesityLevel numeric(0, 10),
    CaloriesBurned integer,
    UiD integer,
    primary key(WiD)
);

create table WORKOUT (
    WiD integer,
    Duration time,
    Title varchar(20),
    IntesityLevel numeric(0, 10),
    CaloriesBurned integer,
    UiD integer,

    primary key(WiD)
);



drop table POST cascade;
drop table FORUM cascade;
drop table FROUPS cascade;
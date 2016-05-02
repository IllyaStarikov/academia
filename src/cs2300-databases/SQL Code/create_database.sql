/*
# Notes For Jason.

- Titles are of fixed length, 20
- Messages are unlimited length
*/

create table USERS (
    UiD numeric(9, 0),
    Username varchar(50) NOT NULL,
    Email varchar(50) NOT NULL,
    HeightFeet numeric(1, 0),
    HeightInches numeric(2, 0),
    Birthdate date NOT NULL,
    Goal int,
    Password varchar(50) NOT NULL,
    JoinDate date NOT NULL,
    Gender char,
    FName varchar(50),
    Minit char,
    LName varchar(50),
    PRIMARY KEY(UiD)
);

create table POST (
    PiD numeric(9, 0) not null,
    FiD numeric(9, 0) not null,
    Message text not null,
    DateStamp date not null,
    Title varchar(20) not null,
    primary key(PiD, FiD)
);

create table GROUPS (
    GiD numeric(9, 0),
    Moderator  numeric(9, 0),
    Title varchar(100) NOT NULL,
    StartDate date NOT NULL,
    PRIMARY KEY(GiD)
);

create table MEMBERS (
    UiD numeric(9, 0),
    GiD numeric(9, 0),
    PRIMARY KEY(UiD, GID)
);


create table CHEST (
    UiD numeric(9, 0),
    Time_stamp time NOT NULL,
    Date_stamp date NOT NULL,
    Chest int,
    PRIMARY KEY(Time_stamp, UiD)
);

create table ARM (
    UiD numeric(9, 0),
    Time_stamp time NOT NULL,
    Date_stamp date NOT NULL,
    Arm integer,
    PRIMARY KEY(Time_stamp, UiD)
);

create table WEIGHT (
    UiD numeric(9, 0),
    Time_stamp time NOT NULL,
    Date_stamp date NOT NULL,
    Weight int,
    PRIMARY KEY(Time_stamp, UiD)
);

create table WORKOUTS (
    WiD numeric(9, 0),
    Duration time NOT NULL,
    Title varchar(25) NOT NULL,
    Intensity numeric(2, 0) CHECK(Intensity <= 10 OR Intensity >= 1),
    CaloriesBurned int CHECK(CaloriesBurned > 0),
    UiD numeric(9, 0),
    PRIMARY KEY(WiD)
);


create table CARDIO (
    WiD numeric(9, 0) REFERENCES WORKOUTS,
    AverageHeartRate int,
    AverageSpeed int,
    DistanceCovered int,
    PRIMARY KEY(WiD)
);

create table STRENGTH (
    WiD numeric(9, 0) REFERENCES WORKOUTS,
    TargetZone varchar(50),
    PRIMARY KEY (WiD)
);

create table FORUM (
    FiD numeric(9, 0),
    GiD numeric(9, 0),
    Title varchar(30) NOT NULL,
    DateCreated date NOT NULL,
    PublicorPrivate bit NOT NULL,
    PRIMARY KEY(FiD)
);

ALTER TABLE GROUPS ADD CONSTRAINT fk_grou_user FOREIGN KEY (Moderator) REFERENCES USERS(UiD);
ALTER TABLE MEMBERS ADD CONSTRAINT fk_mem_user FOREIGN KEY (UiD) REFERENCES USERS(UiD);
ALTER TABLE CHEST ADD CONSTRAINT fk_chest_user FOREIGN KEY (UiD) REFERENCES USERS(UiD);
ALTER TABLE WEIGHT ADD CONSTRAINT fk_weight_user FOREIGN KEY (UiD) REFERENCES USERS(UiD);
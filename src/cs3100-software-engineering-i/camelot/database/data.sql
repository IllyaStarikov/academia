-- test data for the database

INSERT INTO "USER" VALUES ('zach', 'pass');
INSERT INTO "CHANNEL" VALUES ('Software Group', 'zach');
INSERT INTO "CHANNEL" VALUES ('Server Team');
INSERT INTO "CHANNEL" VALUES ('Client Team');
INSERT INTO "CHANNELS_JOINED" VALUES ('zach', 'Software Group');
INSERT INTO "IS_CONNECTED_TO" VALUES ('zach', 'Software Group', DEFAULT, 'testing the messages in the database', '2017-03-14 14:11:30')

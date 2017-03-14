## Camelot Database
This database is created with the usage of Python with Psycopg2 which acts as a connector between Python and postgreSQL. You will first need to install the following things:

- ////// Possibly look into setting up Vagrant file so that users only have to worry about installing Vagrant & VirtualBox OR look into setting up virtual environments for python3 ////////

Personally, I'm running MacOS with Posrgres and Postico to the handle the database. Postgres helps host a local server for viewing the database while Postico is used for visualizing the tables of the database.

## After Installation
Assuming all things have been installed correctly, go to the database folder and run the following commands:
- python3 create_database.py
- python3 insert_data.py

////// Add in a way for user's to input their database info when running python scripts /////

NOTE: depending on how you have python 3 installed, you might be using the command "python" instead of "python3"

The database should now be initialized on your server in the database specified.

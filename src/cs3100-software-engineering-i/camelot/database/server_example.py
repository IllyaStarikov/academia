from database import Camelot_Database

if __name__ == '__main__':
    mydb = Camelot_Database()

    # All of these choices have been added for the purpose of checking and making
    # sure the database was updating correctly.

    choice = input('Would you like to add tables to the database? (y = yes, n = no)')

    if (choice == 'y' or choice == 'yes'):
        mydb.create_tables('tables.sql')

    choice = input('Would you like to add data to the database? (y = yes, n = no)')

    if (choice == 'y' or choice == 'yes'):
        mydb.insert_data('data.sql')

    choice = input('Would you like to empty the tables in the database? (y = yes, n = no)')

    if (choice == 'y' or choice == 'yes'):
        mydb.empty_tables()

import psycopg2
from sys import exit

class Camelot_Database():

    def __init__(self):
        pass

    # Makes connection to database
    def make_connection(self):
        try:
            conn = psycopg2.connect("dbname='camelot' host='localhost'")
        except:
            exit("I am unable to connect to the database")

        return conn

    # Creates tables in database
    def create_tables(self, filename):
        conn = self.make_connection()
        cur = conn.cursor()
        cur.execute(open(filename, 'r').read())
        self.commit_and_close_connection(conn)
        print("Tables have been inserted into the database.")

    # Readies initial data for database
    def insert_data(self, filename):
        conn = self.make_connection()
        cur = conn.cursor()
        cur.execute(open(filename, 'r').read())
        self.commit_and_close_connection(conn)
        print("Data has been added to the database.")

    # Empties all of the current database tables (created by create_tables)
    def empty_tables(self, ):
        conn = self.make_connection()
        cur = conn.cursor()
        cur.execute("""Truncate "USER", "CHANNEL", "CHANNELS_JOINED", "IS_CONNECTED_TO" CASCADE""")
        self.commit_and_close_connection(conn)

    # Adds data to the database & closes the connection to the database
    def commit_and_close_connection(self, conn):
        conn.commit()
        conn.close()

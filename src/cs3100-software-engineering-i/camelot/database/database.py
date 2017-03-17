import psycopg2
from sys import exit
import json

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

    # Adds a user to the database
    def create_account(self, username, password):
        conn = self.make_connection()
        cur = conn.cursor()

        try:
            cur.execute('''INSERT INTO "USER" VALUES ('{}', '{}')'''.format(username, password))
            self.commit_and_close_connection(conn)
        except:

            self.commit_and_close_connection(conn)
            # NOTE: The client will need to do checks to make sure the username
            #       & password are of the correct length, otherwise they will
            #       recieve an error that the says 'username is already taken'
            #       when the username & password have incorrect lengths.
            return json.dumps({
                "error": "That username is already taken."
            })

    # Checks that the username & password are a match in the database
    def check_username_password(self, username, password):
        conn = self.make_connection()
        cur = conn.cursor()

        cur.execute('''
        SELECT userid, password
        FROM "USER"
        WHERE userid='{}' AND password='{}'
        '''.format(username, password))

        rows = cur.fetchall()
        if not rows:
            self.commit_and_close_connection(conn)
            return json.dumps({
                "error": "The username and/or password do not exist in the database."
            }, indent=4)

        # Return back to the user the channels in the database
        cur.execute('''
        SELECT channelid
        FROM "CHANNEL"
        ''')

        rows = cur.fetchall()
        if not rows:
            self.commit_and_close_connection(conn)
            return json.dumps({
                "error": "No channels exist in the database."
            }, indent=4)

        json_to_be_sent = {"channels": []}
        for channel in rows:
            json_to_be_sent['channels'].append(channel[0])

        self.commit_and_close_connection(conn)
        return json.dumps(json_to_be_sent, indent=4)

    # Gets the current channels in the database
    def get_channels(self):
        conn = self.make_connection()
        cur = conn.cursor()

        cur.execute('''
        SELECT channelid
        FROM "CHANNEL"
        ''')

        rows = cur.fetchall()
        if not rows:
            self.commit_and_close_connection(conn)
            return json.dumps({
                "error": "No channels exist in the database."
            }, indent=4)

        channels = {"channels": []}
        for channel in rows:
            channels['channels'].append(channel[0])

        self.commit_and_close_connection(conn)
        return channels

    # Adds to "CHANNELS_JOINED" table in the database; adds the
    # channels that the user wants to join.
    def add_channels_to_user_info(self, username, channels):
        conn = self.make_connection()
        cur = conn.cursor()
        for channel in channels:
            cur.execute('''INSERT INTO "CHANNELS_JOINED" VALUES ('{}', '{}')'''.format(username, channel))
        self.commit_and_close_connection(conn)

    # Creates tables in database
    def create_tables(self, filename):
        conn = self.make_connection()
        cur = conn.cursor()
        cur.execute(open(filename, 'r').read())
        self.commit_and_close_connection(conn)

    # Readies initial data for database
    def insert_data(self, filename):
        conn = self.make_connection()
        cur = conn.cursor()
        cur.execute(open(filename, 'r').read())
        self.commit_and_close_connection(conn)

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

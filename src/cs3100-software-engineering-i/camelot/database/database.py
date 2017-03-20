import psycopg2
from sys import exit
import json

## Camelot_Database
#
#  This class provides an interface with the Camelot Database
class Camelot_Database():

    def __init__(self):
        pass

    ## make_connection
    #
    #  Makes a connection to database
    #  @return The connection object
    def make_connection(self):
        try:
            conn = psycopg2.connect("dbname='camelot' host='localhost'")
        except:
            exit("I am unable to connect to the database")

        return conn

    ## create_user
    #
    #  Adds a user to the database
    #  @param self The object pointer
    #  @param username The name (string) of the user to add
    #  @param password The password (string) to be associated with this user
    #  @return None on success, a JSON object with failure reason otherwise
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

    ## check_username_password
    #
    #  Checks that the username & password are a match in the database
    #  @param self The object pointer
    #  @param username The name (string) of the user to check
    #  @param password The password (string) to be associated with this user
    #  @return A JSON object containing a list of channels on success, or an error code otherwise
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

        # TODO IH 3-19: This should probably be in its own function
        # Actually, isn't this just a copy-paste of the get_channels function?
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

    ## get_channels
    #
    #  Gets the current channels in the database
    #  @param self The object pointer
    #  @return A JSON object containing a list of channels on success, or an error code otherwise
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

    ## add_channels_to_user_info
    #
    #  Adds to "CHANNELS_JOINED" table in the database; adds the
    #  channels that the user wants to join.
    #  @param self The object pointer
    #  @param username The user to add to the channels
    #  @param channels The list of channels to add the user to
    def add_channels_to_user_info(self, username, channels):
        conn = self.make_connection()
        cur = conn.cursor()
        for channel in channels:
            cur.execute('''INSERT INTO "CHANNELS_JOINED" VALUES ('{}', '{}')'''.format(username, channel))
        self.commit_and_close_connection(conn)

    ## create_tables
    #
    #  Creates tables in database
    #  @param self The object pointer
    #  @param filename The SQL file to pull table generation from
    def create_tables(self, filename):
        # TODO IH 3-19: We should consider combining the following 2 functions into one.
        # Maybe something like `execute_sql_script`?
        conn = self.make_connection()
        cur = conn.cursor()
        cur.execute(open(filename, 'r').read())
        self.commit_and_close_connection(conn)

    ## insert_data
    #
    #  Readies initial data for database
    #  @param self The object pointer
    #  @param filename The SQL file to pull table insertion data from
    def insert_data(self, filename):
        conn = self.make_connection()
        cur = conn.cursor()
        cur.execute(open(filename, 'r').read())
        self.commit_and_close_connection(conn)

    ## empty_tables
    #
    #  Empties all of the current database tables (created by create_tables)
    #  @param self The object pointer
    def empty_tables(self, ):
        conn = self.make_connection()
        cur = conn.cursor()
        cur.execute("""Truncate "USER", "CHANNEL", "CHANNELS_JOINED", "IS_CONNECTED_TO" CASCADE""")
        self.commit_and_close_connection(conn)

    ## commit_and_close_connection
    #
    #  Adds data to the database & closes the connection to the database
    #  @param self The object pointer
    #  @param conn The connection to the database to be modified
    def commit_and_close_connection(self, conn):
        conn.commit()
        conn.close()

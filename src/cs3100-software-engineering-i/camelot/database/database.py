import psycopg2
from sys import exit
import json

############ GENERAL NOTES ##############
# 'json.dumps' encodes the data into json
# 'json.loads' decodes the json data
#########################################

## Camelot_Database
#
#  This class provides an interface with the Camelot Database
class Camelot_Database():

    def __init__(self):
        self.insert_data('tables.sql')

    ## Makes a connection to database
    #
    #  @return The connection object
    def make_connection(self):
        try:
            conn = psycopg2.connect("dbname='camelot' host='localhost'")
        except:
            exit("Unable to connect to the database")

        return conn

    ## Adds a user to the database
    #
    #  @param self The object pointer
    #  @param username The name (string) of the user to add
    #  @param password The password (string) to be associated with this user
    #  @return None on success, a JSON object with failure reason otherwise
    def create_account(self, username, password):
        conn = self.make_connection()
        cur = conn.cursor()
        error = None

        # Makes sure the username isn't already taken
        cur.execute('''
        SELECT userid
        FROM "USER"
        WHERE userid='{}'
        '''.format(username))

        if cur.rowcount:
            error = json.dumps({
                "error": "That username is already taken."
            }, indent=4)
        else:
            error = self.validate_username_password(username, password)

        if error:
            return error

        # If no errors occured, create the account
        cur.execute('''INSERT INTO "USER" VALUES ('{}', '{}')'''.format(username, password))
        self.commit_and_close_connection(conn)

    ## Validates the username & password are of the correct length
    #
    #  @param self The object pointer
    #  @param username The name (string) of the user to add
    #  @param password The password (string) to be associated with this user
    #  @return None on success, a JSON object with failure reason otherwise
    def validate_username_password(self, username, password):
        conn = self.make_connection()
        cur = conn.cursor()
        error = None

        # Checks the lengths of the username & password
        if len(username) > 20 or len(username) < 1:
            error = "The username isn't of the correct length (0 < len(username) <= 20)."
        elif len(password) > 20 or len(username) < 1:
            error = "The password isn't of the correct length (0 < len(password) <= 20)."

        # If any error occured
        if error:
            self.commit_and_close_connection(conn)
            return json.dumps({
                "error": error
            }, indent=4)

        self.commit_and_close_connection(conn)

    ## Checks that the username & password are a match in the database
    #
    #  @param self The object pointer
    #  @param username The name (string) of the user to check
    #  @param password The password (string) to be associated with this user
    #  @return A JSON object containing an error message or None if the username/password is in the database
    def check_username_password_in_database(self, username, password):
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
                "error": "The username/password combination do not exist in the database."
            }, indent=4)

        self.commit_and_close_connection(conn)

    ## Gets the current channels in the database
    #
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
        return json.dumps(channels, indent=4)

    ## Adds to "CHANNELS_JOINED" table in the database; adds the
    #  channels that the user wants to join.
    #
    #  @param self The object pointer
    #  @param username The user to add to the channels
    #  @param channels The list of channels to add the user to
    def add_channels_to_user_info(self, username, channels):
        conn = self.make_connection()
        cur = conn.cursor()

        for channel in channels:
            # TODO ZW 3-20: Need to add an error handler for if the user has already joined
            # a channel, and is trying to join it again.
            cur.execute('''INSERT INTO "CHANNELS_JOINED" VALUES ('{}', '{}')'''.format(username, channel))

        self.commit_and_close_connection(conn)

    ## Creates a channel in the database
    #
    #  @param self The object pointer
    #  @param channel_name The name of the channel to be created
    #  @param admin The username of the creator of the channel
    #  @return A JSON object containing an error if there is one, none if successful
    def create_channel(self, channel_name, admin):
        conn = self.make_connection()
        cur = conn.cursor()

        if len(channel_name) > 40 or len(channel_name) < 1:
            self.commit_and_close_connection(conn)
            return json.dumps({
                "error": "The name of the channel isn't of the correct length (0 < len(channel_name) <= 40)."
            }, indent=4)

        # Used for checking if the admin value has been set
        if admin:
            cur.execute('''INSERT INTO "CHANNEL" VALUES ('{}', '{}')'''.format(channel_name, admin))
        else:
            cur.execute('''INSERT INTO "CHANNEL" VALUES ('{}', NULL)'''.format(channel_name))
        self.commit_and_close_connection(conn)


    ## Removes a channel from the database
    #
    #  @param self The object pointer
    #  @param channel_name The channel to be removed
    #  @param user The user calling the function
    #  @return On success returns None, else returns a json object containing the error
    def delete_channel(self, channel_name, user):
        conn = self.make_connection()
        cur = conn.cursor()

        # Checks if the channel exists in the database
        error = self.check_channel_in_database(channel_name)
        if error:
            return error

        # Checks if the user trying to delete the channel, is the admin of the channel
        cur.execute('''
        SELECT channelid
        FROM "CHANNEL"
        WHERE channelid='{}' AND admin='{}'
        '''.format(channel_name, user))

        if cur.rowcount != 1:
            self.commit_and_close_connection(conn)
            return json.dumps({
                "error": "The user trying to delete the channel isn't the admin of the channel."
            }, indent=4)

        # If no errors occur, delete the channel
        cur.execute('''
        DELETE FROM "CHANNEL"
        WHERE channelid='{}'
        '''.format(channel_name))

        self.commit_and_close_connection(conn)

    ## Removes a user from the database
    #
    #  @param self The object pointer
    #  @param username The username to be deleted
    #  @param password The password to be associated with the username
    #  @return On success returns None, else returns a JSON object containing the error
    def delete_account(self, username, password):
        conn = self.make_connection()
        cur = conn.cursor()

        # Check for username and password are in database
        error = self.check_username_password_in_database(username, password)

        if error:
            return error

        # If no errors occur, delete the account
        cur.execute('''
        DELETE FROM "USER"
        WHERE userid='{}'
        '''.format(username))

        self.commit_and_close_connection(conn)

    ## Gets all over the users in a specified channel
    #
    #  @param self The object pointer
    #  @param channel_name The channel specified for getting the users of
    #  @return On success returns None, else returns a JSON object containing the error
    def get_users_in_channel(self, channel_name):
        conn = self.make_connection()
        cur = conn.cursor()

        # Checks if the channel exists in the database
        error = self.check_channel_in_database(channel_name)
        if error:
            return error

        # Grabs the users for the specified channel
        cur.execute('''
        SELECT userid
        FROM "CHANNELS_JOINED"
        WHERE channelid='{}'
        '''.format(channel_name))
        rows = cur.fetchall()

        # Creates base json data to be returned
        result = {
            "users_in_channel": {
                "channel": channel_name,
                "users": []
            }
        }

        # Adds users to the dictionary
        for user in rows:
            result['users_in_channel']['users'].append(user[0])

        self.commit_and_close_connection(conn)
        return json.dumps(result, indent=4)

    ## Makes the user leave the specified channel
    #
    #  @param self The object pointer
    #  @param channel_name The channel specified that the user wants to leave_channel
    #  @param user The user who is wanting to leave a channel
    def leave_channel(self, channel_name, user):
        conn = self.make_connection()
        cur = conn.cursor()

        cur.execute('''
        DELETE FROM "CHANNELS_JOINED"
        WHERE channelid='{}' AND userid='{}'
        '''.format(channel_name, user))

        self.commit_and_close_connection(conn)

    ## Allows the user to change their password
    #
    #  @param self The object pointer
    #  @param username A string used to identify the user attempting to change their username
    #  @param current_password The current password of the user
    #  @param new_password The new password that the user is wanting to replace their old password with
    def change_password(self, username, current_password, new_password):
        conn = self.make_connection()
        cur = conn.cursor()
        error = None

        # Checks if the username/password combination exist in the database
        error = self.check_username_password_in_database(username, current_password)
        if error:
            self.commit_and_close_connection(conn)
            return error

        # Checks that new password is valid (also checks username by default)
        error = self.validate_username_password(username, new_password)
        if error:
            self.commit_and_close_connection(conn)
            return error

        # If no errors occured, updates the user's password
        cur.execute('''
        UPDATE "USER"
        SET password='{}'
        WHERE userid='{}'
        '''.format(new_password, username))

        self.commit_and_close_connection(conn)

    ## Checks if the channel exists in the database
    #
    #  @param self The object pointer
    #  @param channel_name The channel specified to check if it exists in the database
    def check_channel_in_database(self, channel_name):
        conn = self.make_connection()
        cur = conn.cursor()

        # Checks if the channel exists in the database
        cur.execute('''
        SELECT channelid
        FROM "CHANNEL"
        WHERE channelid='{}'
        '''.format(channel_name))

        if cur.rowcount != 1:
            self.commit_and_close_connection(conn)
            return json.dumps({
                "error": "The specified channel was not found."
            }, indent=4)

        self.commit_and_close_connection(conn)

    ## Readies initial data for database
    #
    #  @param self The object pointer
    #  @param filename The SQL file to pull table insertion data from
    def insert_data(self, filename):
        conn = self.make_connection()
        cur = conn.cursor()
        cur.execute(open(filename, 'r').read())
        self.commit_and_close_connection(conn)

    ## Empties all of the current database tables (created by create_tables)
    #
    #  @param self The object pointer
    def empty_tables(self):
        conn = self.make_connection()
        cur = conn.cursor()
        cur.execute("""Truncate "USER", "CHANNEL", "CHANNELS_JOINED" CASCADE""")
        self.commit_and_close_connection(conn)

    ## Adds data to the database & closes the connection to the database
    #
    #  @param self The object pointer
    #  @param conn The connection to the database to be modified
    def commit_and_close_connection(self, conn):
        conn.commit()
        conn.close()

import json

############ GENERAL NOTES ##############
# 'json.dumps' encodes the data into json
# 'json.loads' decodes the json data
#########################################

class Camelot_Server():

    def change_password(self, mydb, client_request):
        try:
            username = client_request['change_password']['username']
            current_password = client_request['change_password']['current_password']
            new_password = client_request['change_password']['new_password']
        except KeyError:
            return json.dumps({
                "error": "The JSON file sent didn't contain valid information."
            }, indent=4)

        return mydb.change_password(username, current_password, new_password)

    def leave_channel(self, mydb, client_request):
        channel_name = client_request['leave_channel']

        # Eventaully, when the server is working, you'll grab the user making the request
        # and set it to the admin. A check will also need to be done to make sure that
        # a session has a user
        #user = session.user
        user = "username" #Temporary

        return mydb.leave_channel(channel_name, user)

    def get_users_in_channel(self, mydb, client_request):
        channel_name = client_request['get_users_in_channel']
        return mydb.get_users_in_channel(channel_name)

    def delete_account(self, mydb, client_request):
        # Check that no one is logged in under the given username
        # Checks what channels the user is an admin of because those channels
        # will be deleted; these channels need to be known so that users can
        # be notified of channels that are deleted.

        try:
            username = client_request['delete_account']['username']
            password = client_request['delete_account']['password']
        except KeyError:
            return json.dumps({
                "error": "The JSON file sent didn't contain valid information."
            }, indent=4)

        return mydb.delete_account(username, password)

    def delete_channel(self, mydb, client_request):
        channel_name = client_request['delete_channel']

        # Eventaully, when the server is working, you'll grab the user making the request
        # and set it to the admin. A check will also need to be done to make sure that
        # a session has a user
        #user = session.user
        user = "username" #Temporary

        return mydb.delete_channel(channel_name, user)

    def create_channel(self, mydb, client_request):
        channel_name = client_request['create_channel']

        # Eventaully, when the server is working, you'll grab the user making the request
        # and set it to the admin. A check will also need to be done to make sure that
        # a session has a user
        #admin = session.user
        #admin = "username" #Temporary
        admin = None

        return mydb.create_channel(channel_name, admin)

    # NOTE: Some variable will also need to be passed to identify which
    #       user is trying to join a channel. I'm guessing this variable
    #       will be created when the client logs into the server.
    def join_channel(self, mydb, client_request):

        # For now, I'll assume with a local variable the client's username
        # Eventaully, this will come from session.user
        username = 'username'

        # Makes sure there are channels for the user to join
        current_channels_available = json.loads(mydb.get_channels())
        if 'error' in current_channels_available.keys():
            return json.dumps(current_channels_available, indent=4)

        channels_user_wants_to_join = [channel for channel in client_request['join_channel']]

        # Make sure the user isn't trying to join invalid channels
        for channel in channels_user_wants_to_join:
            if channel not in current_channels_available['channels']:
                return json.dumps({
                    "error": "The user is trying to join a channel that doesn't exist."
                }, indent=4)

        # Connects the user to the specified channels and stores the information in the database
        mydb.add_channels_to_user_info(username, channels_user_wants_to_join)

    def login(self, mydb, client_request):
        # Makes sure the user is sending valid information
        try:
            client_username = client_request['login']['username']
            client_password = client_request['login']['password']
        except KeyError:
            return json.dumps({
                "error": "The JSON file sent didn't contain valid information."
            }, indent=4)

        result = mydb.check_username_password_in_database(client_username, client_password)
        if result:
            return result
        else:
            return mydb.get_channels()

    def create_account(self, mydb, client_request):
        try:
            client_username = client_request['create_account']['username']
            client_password = client_request['create_account']['password']
        except KeyError:
            return json.dumps({
                "error": "The JSON file sent didn't contain valid information."
            }, indent=4)

        return mydb.create_account(client_username, client_password)

    def new_message(self, mydb, client_request):
        # Going to need to add a way to send the new message to the correct users

        return json.dumps(client_request, indent=4)

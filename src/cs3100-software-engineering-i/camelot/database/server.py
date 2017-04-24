import json

############ GENERAL NOTES ##############
# 'json.dumps' encodes the data into json
# 'json.loads' decodes the json data
#########################################

class Camelot_Server():

    def __init__(self):
        self.user = None

    def login_required(func):
        def call(self, mydb, client_request):
            if self.user:
                return func(self, mydb, client_request)
            else:
                return json.dumps({
                    "error": "A user must be signed in to access this function."
                }, indent=4)
        return call

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

    @login_required
    def leave_channel(self, mydb, client_request):
        channel_name = client_request['leave_channel']
        return mydb.leave_channel(channel_name, self.user)

    @login_required
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

    @login_required
    def delete_channel(self, mydb, client_request):
        channel_name = client_request['delete_channel']
        return mydb.delete_channel(channel_name, self.user)

    @login_required
    def create_channel(self, mydb, client_request):
        channel_name = client_request['create_channel']
        return mydb.create_channel(channel_name, self.user)

    @login_required
    def join_channel(self, mydb, client_request):
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

        if channels_user_wants_to_join:
            # Connects the user to the specified channels and stores the information in the database
            return mydb.add_channels_to_user_info(self.user, channels_user_wants_to_join)
        else:
            return json.dumps({
                "error": "No channels were given for the user to join."
            }, indent=4)

    # On success, return a list of channels available to the user to join
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
            self.user = client_username
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

    @login_required
    def logout(self, mydb, client_request):
        # Don't need to check the value of the key in the dictionary, if the
        # key "logout" existed, then that's all that is needed.

        temp = self.user
        self.user = None
        return json.dumps({
            "success": "{} has successfully logged out.".format(temp)
        }, indent=4)


    @login_required
    def new_message(self, mydb, client_request):
        # Make sure the user sending the message, is sending it to channel that they are in themself
        try:
            channel_name = client_request['new_message']['channel_receiving_message']
            client_username = self.user
            timestamp = client_request['new_message']['timestamp']
            message = client_request['new_message']['message']
        except KeyError:
            return json.dumps({
                "error": "The JSON file sent didn't contain valid information."
            }, indent=4)

        error = mydb.new_message(client_username, channel_name)
        if error:
            return error

        return json.dumps({
            "new_message": {
                "channel_receiving_message": channel_name,
                "user": client_username,
                "timestamp": timestamp,
                "message": message
            }
        }, indent=4)

    # Gets the channels that the specified user is a part of
    @login_required
    def get_channels_for_user(self, mydb, client_request):
        return mydb.get_channels_for_user(self.user)

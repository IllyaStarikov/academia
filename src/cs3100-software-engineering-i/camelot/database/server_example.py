from database import Camelot_Database
import json


############ GENERAL NOTES ##############
# 'json.dumps' encodes the data into json
# 'json.loads' decodes the json data
#########################################

global SERVER_PASSWORD
SERVER_PASSWORD = 'iheartgosnell'

def test_client_create_account():
    return json.dumps({
        "create_account": {
            "username": "username",
            "password": "password",
            "server_password": "iheartgosnell"
        }
    }, indent=4)

def test_client_login():
    return json.dumps({
        "login": {
            "username": "username",
            "password": "password",
            "server_password": "iheartgosnell"
        }
    }, indent=4)

def test_client_join_channels():
    return json.dumps({
        "join_channel": [
            "Client Team",
            "Server Team"
        ]
    }, indent=4)

def test_client_new_message():
    return json.dumps({
        "new_message": {
            "channel_receiving_message": "Client Team",
            "user": "username",
            "timestamp": "2017-03-14 14:11:30",
            "message": "the actual message that the user posted"
        }
    }, indent=4)

# NOTE: Some variable will also need to be passed to identify which
#       user is trying to join a channel. I'm guessing this variable
#       will be created when the client logs into the server.
def join_channel(mydb, client_request):

    # For now, I'll assume with a local variable the client's username
    username = 'username'

    # Makes sure there are channels for the user to join
    current_channels_available = mydb.get_channels()
    if 'error' in current_channels_available.keys():
        return current_channels_available

    channels_user_wants_to_join = [channel for channel in client_request['join_channel']]

    # Make sure the user isn't trying to join invalid channels
    for channel in channels_user_wants_to_join:
        if channel not in current_channels_available['channels']:
            return json.dumps({
                "error": "The user is trying to join a channel that doesn't exist."
            }, indent=4)

    # Connects the user to the specified channels and stores the information in the database
    result = mydb.add_channels_to_user_info(username, channels_user_wants_to_join)

def login(mydb, client_request):
    global SERVER_PASSWORD

    # Makes sure the user is sending valid information
    if client_request['login']['username'] and client_request['login']['password'] and client_request['login']['server_password']:
        client_username = client_request['login']['username']
        client_password = client_request['login']['password']
        server_password = client_request['login']['server_password']

        if server_password == SERVER_PASSWORD:
            result = mydb.check_username_password(client_username, client_password)

            if result:
                return result
        else:
            return json.dumps({
                "error": "Your server password is wrong."
            }, indent=4)
    else:
        return json.dumps({
            "error": "The JSON file sent didn't contain valid information."
        })

def create_account(mydb, client_request):
    global SERVER_PASSWORD

    if client_request['create_account']['username'] and client_request['create_account']['password'] and client_request['create_account']['server_password']:
        client_username = client_request['create_account']['username']
        client_password = client_request['create_account']['password']
        server_password = client_request['create_account']['server_password']

        if server_password == SERVER_PASSWORD:
            result = mydb.create_account(client_username, client_password)

            if result:
                return result
        else:
            return json.dumps({
                "error": "Your server password is wrong."
            }, indent=4)
    else:
        return json.dumps({
            "error": "The JSON file sent didn't contain valid information."
        })

def send_to_client(response):
    print("This is what will get sent to the client:\n")
    print(response)
    print('')

if __name__ == '__main__':
    mydb = Camelot_Database()
    mydb.create_tables('tables.sql')
    #mydb.insert_data('data.sql')

    #client_request = json.loads(test_client_create_account())
    #client_request = json.loads(test_client_login())
    #client_request = json.loads(test_client_join_channels())
    #client_request = json.loads(test_client_new_message())

    for operation in client_request.keys():
        if operation == 'create_account':
            response = create_account(mydb, client_request)
        elif operation == 'login':
            response = login(mydb, client_request)
        elif operation == 'join_channel':
            response = join_channel(mydb, client_request)
        elif operation == 'new_message':
            response = json.dumps(client_request, indent=4)
        else:
            response = json.dumps({
                "error": "The JSON file sent didn't contain valid information."
            }, indent=4)

    if response:
        send_to_client(response)

    '''
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
    '''

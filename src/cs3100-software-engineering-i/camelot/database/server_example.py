from database import Camelot_Database
from server import Camelot_Server
import json


############ GENERAL NOTES ##############
# 'json.dumps' encodes the data into json
# 'json.loads' decodes the json data
#########################################

def test_bad_json():
    return json.dumps({
        "creating_channel": {
            "test":"asd"
        }
    })

def test_client_create_account():
    return json.dumps({
        "create_account": {
            "username": "zach",
            "password": "password",
        }
    }, indent=4)

def test_client_login():
    return json.dumps({
        "login": {
            "username": "username",
            "password": "password",
        }
    }, indent=4)

def test_client_join_channel():
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

def test_client_create_channel():
    return json.dumps({
        "create_channel": "some new channel name"
    }, indent=4)

def test_client_delete_channel():
    return json.dumps({
        "delete_channel": "some new channel name"
    }, indent=4)

def test_client_delete_account():
    return json.dumps({
        "delete_account": {
            "username": "zach",
            "password": "pass"
        }
    }, indent=4)

def test_client_get_users_in_channel():
    return json.dumps({
        "get_users_in_channel": "Client Team"
    }, indent=4)

def test_client_leave_channel():
    return json.dumps({
        "leave_channel": "Client Team"
    }, indent=4)

def test_client_change_password():
    return json.dumps({
        "change_password": {
            "username": "username",
            "current_password": "password",
            "new_password": "their new password"
        }
    }, indent=4)

def send_to_client(response):
    print("This is what will get sent to the client:\n")
    print(response)
    print('')

if __name__ == '__main__':
    server = Camelot_Server()
    mydb = Camelot_Database()
    #mydb.insert_data('data.sql')

    client_request = json.loads(test_bad_json())
    #client_request = json.loads(test_client_create_account())
    #client_request = json.loads(test_client_login())
    #client_request = json.loads(test_client_join_channel())
    #client_request = json.loads(test_client_new_message())
    #client_request = json.loads(test_client_create_channel())
    #client_request = json.loads(test_client_delete_channel())
    #client_request = json.loads(test_client_delete_account())
    #client_request = json.loads(test_client_get_users_in_channel())
    #client_request = json.loads(test_client_leave_channel())
    #client_request = json.loads(test_client_change_password())

    for operation in client_request.keys():
        try:
            response = getattr(server, operation)(mydb, client_request)
        except AttributeError:
            response = json.dumps({
                "error": "The JSON file sent didn't contain valid information."
            }, indent=4)


    # TODO ZW 3-20: Need to add a check that makes sure a client is only getting sent
    # messages if the user is a part of the specified channel.
    #response = json.dumps(client_request, indent=4)

    # TODO zw 4-1: Need to add a way to send a message to all users if a channel has
    # been deleted.


    if response:
        send_to_client(response)

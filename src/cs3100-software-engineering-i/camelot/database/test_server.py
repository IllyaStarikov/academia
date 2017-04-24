from database import Camelot_Database
from server import Camelot_Server
import json

################################### HOW TO USE THIS FILE #########################################
# Pytest: Used for running unit tests                                                            #
# INSTALL: pytest (for me I installed it via command-line using: "pip3 install pytest")          #
# RUN: Just type "pytest" in the command-line while in the same directory as this file           #
#                                                                                                #
# Pytest-cov: Used for seeing how much code coverage there is                                    #
# INSTALL: pytest-cov (for me I installed it via command-line using: "pip3 install pytest-cov")  #
# RUN: Just type "py.test --cov-report term-missing --cov=./" in the command-line while in       #
#      the same directory as this file                                                           #
##################################################################################################

############ GENERAL NOTES ################
# 'json.dumps' encodes the data into json #
# 'json.loads' decodes the json data      #
###########################################

def test_setup():
    server = Camelot_Server()
    mydb = Camelot_Database()
    mydb.empty_tables()

def test_create_account_invalid_json():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "create_account": {
            "username_invalid": "username",
            "password": "password",
        }
    }, indent=4))

    expected_response = json.dumps({
        "error": "The JSON file sent didn't contain valid information."
    }, indent=4)

    result = server.create_account(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_create_account_username_incorrect_length():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "create_account": {
            "username": "username-----------------------------------------------",
            "password": "password",
        }
    }, indent=4))

    expected_response = json.dumps({
        "error": "The username isn't of the correct length (0 < len(username) <= 20)."
    }, indent=4)

    result = server.create_account(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_create_account_password_incorrect_length():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "create_account": {
            "username": "username",
            "password": "password-----------------------------------------------",
        }
    }, indent=4))

    expected_response = json.dumps({
        "error": "The password isn't of the correct length (0 < len(password) <= 20)."
    }, indent=4)

    result = server.create_account(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_create_account_username_already_taken():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "create_account": {
            "username": "username",
            "password": "password",
        }
    }, indent=4))

    expected_response = json.dumps({
        "error": "That username is already taken."
    }, indent=4)

    server.create_account(mydb, client_request)
    result = server.create_account(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_create_account_success():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "create_account": {
            "username": "username",
            "password": "password",
        }
    }, indent=4))

    expected_response = json.dumps({
        "success": "Successfully created username's account."
    }, indent=4)

    result = server.create_account(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_create_account_success_with_default_channels_added_to_account():
    server = Camelot_Server()
    mydb = Camelot_Database()
    mydb.insert_data('data.sql')

    expected_response = json.dumps({
        "channels": ["Server Team", "Client Team", "Software Eng. Group"]
    }, indent=4)

    mydb.create_account("username", "password")
    result = mydb.get_channels_for_user("username")

    assert expected_response == result
    mydb.empty_tables()

def test_get_channels_for_user():
    server = Camelot_Server()
    mydb = Camelot_Database()
    mydb.insert_data('data.sql')

    client_request = json.dumps({
        "get_channels_for_user": "get_channels_for_user"
    }, indent=4)

    expected_response = json.dumps({
        "channels": ["Server Team", "Client Team", "Software Eng. Group"]
    }, indent=4)

    mydb.create_account("username", "password")
    server, mydb = login(server, mydb, 'username', 'password')
    result = server.get_channels_for_user(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_login_invalid_json():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "login": {
            "username_invalid": "username",
            "password": "password",
        }
    }, indent=4))

    expected_response = json.dumps({
        "error": "The JSON file sent didn't contain valid information."
    }, indent=4)

    result = server.login(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_login_user_password_combination_not_in_database():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "login": {
            "username": "username",
            "password": "password",
        }
    }, indent=4))

    expected_response = json.dumps({
        "error": "The username/password combination do not exist in the database."
    }, indent=4)

    result = server.login(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_login_no_channels_available():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "login": {
            "username": "username",
            "password": "password",
        }
    }, indent=4))

    expected_response = json.dumps({
        "error": "No channels exist in the database."
    }, indent=4)

    mydb.create_account("username", "password")
    result = server.login(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_login_success():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "login": {
            "username": "username",
            "password": "password",
        }
    }, indent=4))

    expected_response = json.dumps({
        "channels": ["ChannelTest"]
    }, indent=4)

    mydb.create_account("username", "password")
    mydb.create_channel("ChannelTest", "username")

    result = server.login(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_new_message_not_logged_in():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "new_message": {
            "channel_receiving_message": "Client Team",
            "user": "username",
            "timestamp": "2017-03-14 14:11:30",
            "message": "the actual message that the user posted"
        }
    }, indent=4))

    expected_response = json.dumps({
        "error": "A user must be signed in to access this function."
    }, indent=4)

    result = server.new_message(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_new_message_invalid_json():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "new_message": {
            "channel_receiving_": "Client Team",
            "user": "username",
            "timestamp": "2017-03-14 14:11:30",
            "message": "the actual message that the user posted"
        }
    }, indent=4))

    expected_response = json.dumps({
        "error": "The JSON file sent didn't contain valid information."
    }, indent=4)

    mydb.create_account('username', 'password')
    server, mydb = login(server, mydb, 'username', 'password')
    mydb.create_channel('Client Team', None)
    mydb.add_channels_to_user_info('username', ['Client Team'])

    result = server.new_message(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_new_message_user_cant_send_message_to_channel_theyre_not_in():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "new_message": {
            "channel_receiving_message": "Client Team",
            "user": "username",
            "timestamp": "2017-03-14 14:11:30",
            "message": "the actual message that the user posted"
        }
    }, indent=4))

    expected_response = json.dumps({
        "error": "The user is trying to send a message to a channel they haven't joined yet."
    }, indent=4)

    mydb.create_account('username', 'password')
    server, mydb = login(server, mydb, 'username', 'password')
    mydb.create_channel('Client Team', None)

    result = server.new_message(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_new_message_send_message_to_channel_that_doesnt_exist():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "new_message": {
            "channel_receiving_message": "dummy channel",
            "user": "username",
            "timestamp": "2017-03-14 14:11:30",
            "message": "the actual message that the user posted"
        }
    }, indent=4))

    expected_response = json.dumps({
        "error": "The specified channel was not found."
    }, indent=4)

    mydb.create_account('username', 'password')
    server, mydb = login(server, mydb, 'username', 'password')

    result = server.new_message(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_new_message_success():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "new_message": {
            "channel_receiving_message": "Client Team",
            "user": "username",
            "timestamp": "2017-03-14 14:11:30",
            "message": "the actual message that the user posted"
        }
    }, indent=4))

    expected_response = json.dumps({
        "new_message": {
            "channel_receiving_message": "Client Team",
            "user": "username",
            "timestamp": "2017-03-14 14:11:30",
            "message": "the actual message that the user posted"
        }
    }, indent=4)

    mydb.create_account('username', 'password')
    server, mydb = login(server, mydb, 'username', 'password')
    mydb.create_channel('Client Team', None)
    mydb.add_channels_to_user_info('username', ['Client Team'])

    result = server.new_message(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_join_channel_not_logged_in():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "join_channel": [
            "Client Team",
            "Server Team"
        ]
    }, indent=4))

    expected_response = json.dumps({
        "error": "A user must be signed in to access this function."
    }, indent=4)

    result = server.join_channel(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_join_channel_no_channels_available():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "join_channel": [
            "Client Team",
            "Server Team"
        ]
    }, indent=4))

    expected_response = json.dumps({
        "error": "No channels exist in the database."
    }, indent=4)

    mydb.create_account('username', 'password')
    server, mydb = login(server, mydb, 'username', 'password')

    result = server.join_channel(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_join_channel_that_doesnt_exist():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "join_channel": [
            "Client Team",
            "Server Team"
        ]
    }, indent=4))

    expected_response = json.dumps({
        "error": "The user is trying to join a channel that doesn't exist."
    }, indent=4)

    mydb.create_account('username', 'password')
    server, mydb = login(server, mydb, 'username', 'password')
    mydb.create_channel("TestChannel", "username")

    result = server.join_channel(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_join_channel_trying_to_join_channel_that_you_are_already_a_part_of():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "join_channel": [
            "Client Team",
            "Server Team"
        ]
    }, indent=4))

    expected_response = json.dumps({
        "error": "The user has already joined one or more of the channels they were trying to join again."
    })

    mydb.create_account("username", "password")
    server, mydb = login(server, mydb, "username", "password")
    mydb.create_channel("Client Team", "username")
    mydb.create_channel("Server Team", "username")
    server.join_channel(mydb, client_request)
    result = server.join_channel(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_join_channel_user_tries_to_send_json_containing_zero_channels_to_join():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "join_channel": []
    }, indent=4))

    expected_response = json.dumps({
        "error": "No channels were given for the user to join."
    }, indent=4)

    mydb.create_account("username", "password")
    server, mydb = login(server, mydb, "username", "password")
    mydb.create_channel("Client Team", "username")
    mydb.create_channel("Server Team", "username")
    result = server.join_channel(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_join_channel_success():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "join_channel": [
            "Client Team",
            "Server Team"
        ]
    }, indent=4))

    expected_response = json.dumps({
        "channels_joined": ["Client Team", "Server Team"],
        "user": "username"
    }, indent=4)

    mydb.create_account("username", "password")
    server, mydb = login(server, mydb, "username", "password")
    mydb.create_channel("Client Team", "username")
    mydb.create_channel("Server Team", "username")
    result = server.join_channel(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_create_channel_not_logged_in():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "create_channel": "Test Channel Name with incorrect length-----------"
    }, indent=4))

    expected_response = json.dumps({
        "error": "A user must be signed in to access this function."
    }, indent=4)

    result = server.create_channel(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_create_channel_channel_name_incorrect_length():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "create_channel": "Test Channel Name with incorrect length-----------"
    }, indent=4))

    expected_response = json.dumps({
        "error": "The name of the channel isn't of the correct length (0 < len(channel_name) <= 40)."
    }, indent=4)

    mydb.create_account("username", "password")
    server, mydb = login(server, mydb, 'username', 'password')

    result = server.create_channel(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_create_channel_that_already_exists():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "create_channel": "Test Channel Name"
    }, indent=4))

    expected_response = json.dumps({
        "error": "The specified channel already exists in the database."
    }, indent=4)

    mydb.create_account("username", "password")
    server, mydb = login(server, mydb, 'username', 'password')

    server.create_channel(mydb, client_request)
    result = server.create_channel(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_create_channel_success():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "create_channel": "Test Channel Name"
    }, indent=4))

    expected_response = json.dumps({
        "channel_created": {
            "channel": "Test Channel Name",
            "message": "A new channel has been created: 'Test Channel Name'."
        }
    }, indent=4)

    mydb.create_account("username", "password")
    server, mydb = login(server, mydb, 'username', 'password')

    result = server.create_channel(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_delete_channel_not_logged_in():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "delete_channel": "Non-existent channel"
    }, indent=4))

    expected_response = json.dumps({
        "error": "A user must be signed in to access this function."
    }, indent=4)

    result = server.delete_channel(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_delete_channel_channel_not_found():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "delete_channel": "Non-existent channel"
    }, indent=4))

    expected_response = json.dumps({
        "error": "The specified channel was not found."
    }, indent=4)

    mydb.create_account("username", "password")
    server, mydb = login(server, mydb, 'username', 'password')
    mydb.create_channel("TestChannel", "username")

    result = server.delete_channel(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_delete_channel_user_not_authorized_to_delete_channel():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "delete_channel": "TestChannel"
    }, indent=4))

    expected_response = json.dumps({
        "error": "The user trying to delete the channel isn't the admin of the channel."
    }, indent=4)

    mydb.create_account("username", "password")
    server, mydb = login(server, mydb, 'username', 'password')
    mydb.create_account("admin user", "password")
    mydb.create_channel("TestChannel", "admin user")

    result = server.delete_channel(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_delete_channel_success():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "delete_channel": "TestChannel"
    }, indent=4))

    expected_response = json.dumps({
        "channel_deleted": {
            "channel": "TestChannel",
            "message": "The channel `TestChannel` has been deleted."
        }
    }, indent=4)

    mydb.create_account("username", "password")
    server, mydb = login(server, mydb, 'username', 'password')
    mydb.create_channel("TestChannel", "username")

    result = server.delete_channel(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_delete_account_invalid_json():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "delete_account": {
            "username_invalid": "username",
            "password": "password"
        }
    }, indent=4))

    expected_response = json.dumps({
        "error": "The JSON file sent didn't contain valid information."
    }, indent=4)

    result = server.delete_account(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_delete_account_account_does_not_exist():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "delete_account": {
            "username": "username",
            "password": "password"
        }
    }, indent=4))

    expected_response = json.dumps({
        "error": "The username/password combination do not exist in the database."
    }, indent=4)

    result = server.delete_account(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_delete_account_success():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "delete_account": {
            "username": "username",
            "password": "password"
        }
    }, indent=4))

    expected_response = json.dumps({
        "account_deleted": {
            "username": "username",
            "channels_being_deleted": ["TestChannel"]
        }
    }, indent=4)

    mydb.create_account("username", "password")
    mydb.create_channel("TestChannel", "username")
    result = server.delete_account(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_get_users_in_channel_not_logged_in():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "get_users_in_channel": "Client Team"
    }, indent=4))

    expected_response = json.dumps({
        "error": "A user must be signed in to access this function."
    }, indent=4)

    result = server.get_users_in_channel(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_get_users_in_channel_channel_does_not_exist():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "get_users_in_channel": "Client Team"
    }, indent=4))

    expected_response = json.dumps({
        "error": "The specified channel was not found."
    }, indent=4)

    mydb.create_account("username", "password")
    server, mydb = login(server, mydb, 'username', 'password')

    result = server.get_users_in_channel(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_get_users_in_channel_success():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "get_users_in_channel": "Client Team"
    }, indent=4))

    expected_response = json.dumps({
        "users_in_channel": {
            "channel": "Client Team",
            "users": [
                "username",
                "user2"
            ]
        }
    }, indent=4)

    mydb.create_account("username", "password")
    server, mydb = login(server, mydb, 'username', 'password')
    mydb.create_account("user2", "password")
    mydb.create_channel("Client Team", None)
    mydb.add_channels_to_user_info("username", ["Client Team"])
    mydb.add_channels_to_user_info("user2", ["Client Team"])

    result = server.get_users_in_channel(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_leave_channel_not_logged_in():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "leave_channel": "Client Team"
    }, indent=4))

    expected_response = json.dumps({
        "error": "A user must be signed in to access this function."
    }, indent=4)

    result = server.leave_channel(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_leave_channel_channel_does_not_exist():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "leave_channel": "Client Team"
    }, indent=4))

    expected_response = json.dumps({
        "error": "The specified channel was not found."
    }, indent=4)

    mydb.create_account("username", "password")
    server, mydb = login(server, mydb, 'username', 'password')

    result = server.leave_channel(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_leave_channel_success():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "leave_channel": "Client Team"
    }, indent=4))

    expected_response = json.dumps({
        "leave_channel":{
            "channel": "Client Team",
            "user": "username",
            "message": "username has left the channel."
         }
    }, indent=4)

    mydb.create_account("username", "password")
    server, mydb = login(server, mydb, 'username', 'password')
    mydb.create_channel("Client Team", None)
    mydb.add_channels_to_user_info("username", ["Client Team"])

    result = server.leave_channel(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_change_password_invalid_json():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "change_password": {
            "username_invalid": "username",
            "current_password": "password",
            "new_password": "their new password"
        }
    }, indent=4))

    expected_response = json.dumps({
        "error": "The JSON file sent didn't contain valid information."
    }, indent=4)

    result = server.change_password(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_change_password_account_does_not_exist():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "change_password": {
            "username": "username",
            "current_password": "password",
            "new_password": "their new password"
        }
    }, indent=4))

    expected_response = json.dumps({
        "error": "The username/password combination do not exist in the database."
    }, indent=4)

    result = server.change_password(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_change_password_invalid_new_password():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "change_password": {
            "username": "username",
            "current_password": "password",
            "new_password": "their new password--------------------------"
        }
    }, indent=4))

    expected_response = json.dumps({
        "error": "The password isn't of the correct length (0 < len(password) <= 20)."
    }, indent=4)

    mydb.create_account("username", "password")

    result = server.change_password(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_change_password_success():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "change_password": {
            "username": "username",
            "current_password": "password",
            "new_password": "their new password"
        }
    }, indent=4))

    expected_response = json.dumps({
        "success": "Successfully changed username's password."
    }, indent=4)

    mydb.create_account("username", "password")

    result = server.change_password(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_logout_not_logged_in():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "logout": "logout"
    }, indent=4))

    expected_response = json.dumps({
        "error": "A user must be signed in to access this function."
    }, indent=4)

    result = server.logout(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def test_logout_success():
    server = Camelot_Server()
    mydb = Camelot_Database()

    client_request = json.loads(json.dumps({
        "logout": "logout"
    }, indent=4))

    expected_response = json.dumps({
        "success": "username has successfully logged out."
    }, indent=4)

    mydb.create_account("username", "password")
    server, mydb = login(server, mydb, 'username', 'password')

    result = server.logout(mydb, client_request)

    assert expected_response == result
    mydb.empty_tables()

def login(server, mydb, username, password):
    client_request = json.loads(json.dumps({
        "login": {
            "username": username,
            "password": password,
        }
    }, indent=4))

    # The login function needs to be called through the Camelot_Server class
    # so that the 'self.user' variable can be set.
    server.login(mydb, client_request)

    return (server, mydb)

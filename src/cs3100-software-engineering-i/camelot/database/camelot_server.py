import socket
import threading
import json
from server import Camelot_Server
from database import Camelot_Database
from time import sleep

# NOTE: Sleep is used after making sending calls so that clients have time to process
#       each send; this helps prevent multiple JSON objects from getting inadvertently
#       sent at once. If more than one JSON object is in a package sent to the client,
#       it will cause errors when unpacking the JSON information (or at least in python
#       it will).


my_clients = {}
my_threads = []
client_lock = threading.Lock()

class ClientThread(threading.Thread):
    def __init__(self, conn, addr):
        threading.Thread.__init__(self)
        self.conn = conn
        self.addr = addr
        self.server = Camelot_Server()
        self.mydb = Camelot_Database()
        self.unauthorized_function_calls = ['__init__', 'login_required']

    def run(self):
        # Global keyword needed if your wanting to change the variable in a method
        global my_clients
        connected = True

        # Get this client's thread
        cur_thread = threading.current_thread()
        thread_name = cur_thread.name

        while connected:
            # Checks for new packages from the client
            error, client_request = self.validate_request_data(thread_name)

            # If a new package was recieved from the client (and no errors occured with the package)
            if not error:
                # Grab the threads that have a user logged in
                valid_threads = [thread for thread in my_threads if thread.server.user]

                # Attempt to carry out the clients request
                for operation in client_request.keys():
                    try:
                        if operation in self.unauthorized_function_calls:
                            raise AttributeError
                        with client_lock:
                            response = getattr(self.server, operation)(self.mydb, client_request)
                    except AttributeError:
                        response = json.dumps({
                            "error": "The JSON file sent didn't contain valid information."
                        }, indent=4)

                if operation == 'new_message':
                    # Unload the JSON into a dictionary for usage
                    check = json.loads(response)
                    new_message = False

                    try:
                        if check['new_message']:
                            new_message = True
                    except KeyError:
                        with client_lock:
                            self.conn.sendall(bytes(str(response), 'ascii'))
                            sleep(0.5)

                    if new_message:
                        users_to_notify = self.mydb.get_users_in_channel(check['new_message']['channel_receiving_message'])
                        users_to_notify = json.loads(users_to_notify)

                        try:
                            if users_to_notify['error']:
                                users_to_notify = json.dumps(users_to_notify, indent=4)

                                with client_lock:
                                    self.conn.sendall(bytes(str(users_to_notify), 'ascii'))
                                    sleep(0.5)

                        except KeyError:
                            users_to_message = [user for user in users_to_notify['users_in_channel']['users']]

                            for client_thread in valid_threads:
                                if client_thread.server.user in users_to_message:
                                    with client_lock:
                                        client_thread.conn.sendall(bytes(str(response), 'ascii'))
                                        sleep(0.5)

                elif operation == 'delete_channel':
                    # Unload the JSON into a dictionary for usage
                    check = json.loads(response)
                    delete_channel = False

                    try:
                        if check['channel_deleted']:
                            delete_channel = True
                    except KeyError:
                        with client_lock:
                            self.conn.sendall(bytes(str(response), 'ascii'))
                            sleep(0.5)

                    if delete_channel:
                        for client_thread in valid_threads:
                            with client_lock:
                                client_thread.conn.sendall(bytes(str(response), 'ascii'))
                                sleep(0.5)

                elif operation == 'create_channel':
                    # Unload the JSON into a dictionary for usage
                    check = json.loads(response)
                    create_channel = False

                    try:
                        if check['channel_created']:
                            create_channel = True
                    except KeyError:
                        with client_lock:
                            self.conn.sendall(bytes(str(response), 'ascii'))
                            sleep(0.5)

                    if create_channel:
                        # Notify all users of the new channel created
                        for client_thread in valid_threads:
                            with client_lock:
                                client_thread.conn.sendall(bytes(str(response), 'ascii'))
                                sleep(0.5)

                elif operation == 'join_channel':
                    # Unload the JSON into a dictionary for usage
                    check = json.loads(response)
                    join_channel = False

                    try:
                        if check['channels_joined']:
                            join_channel = True
                    except KeyError:
                        with client_lock:
                            self.conn.sendall(bytes(str(response), 'ascii'))
                            sleep(0.5)

                    if join_channel:
                        # Notify users who are in a specified channel of the new user who entered.
                        for client_thread in valid_threads:
                            for channel in check['channels_joined']:
                                if not client_thread.mydb.check_username_in_channel(client_thread.server.user, channel):
                                    with client_lock:
                                        client_thread.conn.sendall(bytes(str(json.dumps({
                                            "user_joined_channel": {
                                                "message": "{} has joined the channel.".format(check['user']),
                                                "user": check['user'],
                                                "channel": channel
                                            }
                                        }, indent=4)), 'ascii'))
                                        sleep(0.5)

                elif operation == 'delete_account':
                    # Unload the JSON into a dictionary for usage
                    check = json.loads(response)
                    delete_account = False

                    try:
                        if check['account_deleted']:
                            delete_account = True
                    except KeyError:
                        with client_lock:
                            self.conn.sendall(bytes(str(response), 'ascii'))
                            sleep(0.5)

                    if delete_account:
                        # Send the user who deleted the account a message
                        self.conn.sendall(bytes(str(json.dumps({
                            "success": "Your account has been deleted."
                        }, indent=4)), 'ascii'))

                        # Check if someone is logged in under account being deleted.
                        for client_thread in valid_threads:
                            if client_thread.server.user == check['account_deleted']['username']:
                                client_thread.server.user = None
                                with client_lock:
                                    client_thread.conn.sendall(bytes(str(json.dumps({
                                        "account_deleted": "You've been logged out due to your account being deleted."
                                    }, indent=4)), 'ascii'))
                                    sleep(0.5)

                        channels_being_deleted = check['account_deleted']['channels_being_deleted']

                        # Notify all users that a channel has been deleted
                        for channel in channels_being_deleted:
                            for client_thread in valid_threads:
                                with client_lock:
                                    client_thread.conn.sendall(bytes(str(json.dumps({
                                        "channel_deleted": {
                                            "channel": channel,
                                            "message": "The channel `{}` has been deleted.".format(channel)
                                        }
                                    }, indent=4)), 'ascii'))
                                    sleep(0.5)

                elif operation == 'leave_channel':
                    # Unload the JSON into a dictionary for usage
                    check = json.loads(response)
                    leave_channel = False

                    try:
                        if check['leave_channel']:
                            leave_channel = True
                    except KeyError:
                        with client_lock:
                            self.conn.sendall(bytes(str(response), 'ascii'))
                            sleep(0.5)

                    if leave_channel:
                        # Notify all users in the specified channel that the specified user has left said channel.
                        for client_thread in valid_threads:
                            if (not client_thread.mydb.check_username_in_channel(client_thread.server.user, check['leave_channel']['channel']) and
                            client_thread.server.user != check['leave_channel']['user']):
                                with client_lock:
                                    client_thread.conn.sendall(bytes(str(response), 'ascii'))
                                    sleep(0.5)

                        with client_lock:
                            self.conn.sendall(bytes(str(json.dumps({
                                "success": "You have successfully left the channel: `{}`".format(check['leave_channel']['channel'])
                            }, indent=4)), 'ascii'))
                            sleep(0.5)


                else:
                    with client_lock:
                        self.conn.sendall(bytes(str(response), 'ascii'))
                        sleep(0.5)

            #If an error occured
            else:
                client_lock.acquire()

                try:
                    self.conn.sendall(bytes(str(client_request), 'ascii'))
                    sleep(0.5)

                except BrokenPipeError:
                    print("{} disconnected.".format(thread_name))
                    my_clients.pop(self.addr)
                    client_lock.release()
                    return None

                client_lock.release()

    def validate_request_data(self, thread_name):
        error = False

        try:
            # Receive the data from that socket
            request = json.loads(self.conn.recv(4096).decode('ascii'))
            print("Received `{}` from `{}`".format(json.dumps(request), thread_name))

        except:
            error = True
            request = json.dumps({
                "error": "Something went wrong"
                }, indent=4)

        return (error, request)

if __name__ == '__main__':
    # Add some initial channels to the database
    mydb = Camelot_Database()
    mydb.insert_data('data.sql')

    host = '127.0.0.1'
    port = 12345

    soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # this is for easy starting/killing the app
    soc.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    soc.bind((host,port))
    soc.listen(10)

    try:
        # Accept new incoming clients
        while True:
            client_socket, addr = soc.accept()
            my_clients[addr] = client_socket
            print('Got a new connection from {}'.format(addr))
            new_client_thread = ClientThread(client_socket, addr)
            new_client_thread.daemon = True
            my_threads.append(new_client_thread)
            new_client_thread.start()

    except KeyboardInterrupt:
        print('Shutting down server...')
        client_lock.acquire()
        for client in my_clients.values():
            client_request = json.dumps({
                "connection": "Broke"
            }, indent=4)
            client.sendall(bytes(str(client_request), 'ascii'))
            sleep(0.5)
        client_lock.release()

    soc.close()

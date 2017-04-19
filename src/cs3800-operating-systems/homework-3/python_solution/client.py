import socket
import threading
from time import sleep
from sys import exit, argv

running = True
lock = threading.Lock()

class ClientRecvThread(threading.Thread):

    # Constructor that creates a thread and sets the socket for the client
    def __init__(self, soc):
        threading.Thread.__init__(self)
        self.soc = soc

    def run(self):
        global running

        while True:

            # Receives new message from server
            result_bytes = soc.recv(4096) # the number means how the response can be in bytes
            result_string = result_bytes.decode('ascii') # the return will be in bytes, so decode

            # If the client receives nothing from the server, close the client
            if not result_bytes:
                print("The client's connection to the server has been broke.")
                running = False
                return None

            # If the server is shutting down, close the client after 10 seconds
            if result_string == 'Shutting down server in 10 seconds..':
                print(result_string)
                sleep(10)
                running = False
                return None

            # Otherwise, print out the message received from the server
            else:
                print(result_string)


class ClientSendThread(threading.Thread):

    # Constructor that creates a thread and sets the socket for the client
    def __init__(self, soc):
        threading.Thread.__init__(self)
        self.soc = soc
        self.user = None

    def run(self):
        connected = True

        # Gets username
        username = input('Please enter a username: \n')
        self.user = username

        # Sends message to server that user has joined chat
        message = '{} has joined the chat.'.format(username)
        with lock:
            self.soc.sendall(bytes(message, 'ascii'))

        # Loops while the user is connected to the server
        while connected:

            # Gets new messages from user
            message = input('')
            if self.check_for_quit(message):
                return None

            # Sends message to server with user's new message
            message = username + ": " + message
            with lock:
                self.soc.sendall(bytes(message, 'ascii'))

    # Checks if the user wants to quit the client
    def check_for_quit(self, text):
        global running
        exit_calls = ['/exit', '/quit', '/part']

        # If the user entered a valid exit call, send a notice to the server,
        # and close the client's connection.
        if text in exit_calls:
            message = '{} has left the chat.'.format(self.user)
            with lock:
                self.soc.sendall(bytes(message, 'ascii'))

            running = False
            return True


if __name__ == '__main__':
    if len(argv) != 2:
        exit('Make sure your including one arguement which is the host name.')

    try:
        soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    except:
        exit('Failed to create socket.')

    try:
        soc.connect((argv[1], 12345))
    except:
        exit('Failed to connect to server socket.')

    try:
        send_thread = ClientSendThread(soc)
    except:
        exit('Failed to create send thread.')

    # Allows thread to close without waiting for the thread to finish
    send_thread.daemon = True

    try:
        send_thread.start()
    except:
        exit('Failed to start send thread.')

    try:
        recv_thread = ClientRecvThread(soc)
    except:
        exit('Failed to create recieve thread.')

    # Allows thread to close without waiting for the thread to finish
    recv_thread.daemon = True

    try:
        recv_thread.start()
    except:
        exit('Failed to start recieve thread.')

    # client runs indefinitely until running equals False
    while running:
        try:
            while running:
                pass
        except KeyboardInterrupt:
            print('Please enter /exit, /quit, or /part to quit the client.\n')

    print('Closing client')
    try:
        soc.close()
    except:
        exit('Failed to close connection to server socket.')

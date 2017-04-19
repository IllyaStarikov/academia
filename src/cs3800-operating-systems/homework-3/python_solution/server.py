import socket
import threading
from time import sleep
from sys import exit

my_clients = {}
client_limit = 10
lock = threading.Lock()

class ClientThread(threading.Thread):

    # Constructor that sets the connection and address for each client thread
    def __init__(self, conn, addr):
        threading.Thread.__init__(self)
        self.conn = conn
        self.addr = addr

    def run(self):
        # Global keyword needed if your wanting to change the variable in a method
        global my_clients

        while True:
            # Gets message from clent
            message = self.conn.recv(4096).decode('ascii')

            # If the message from the client returns empty, then the client has closed
            if not message:
                print("{} disconnected.".format(self.addr))
                my_clients.pop(self.addr)
                return None

            # Send a message to each of the clients (besides the calling client)
            for client_conn in my_clients.values():
                if client_conn != self.conn:
                    with lock:
                        client_conn.sendall(bytes(str(message), 'ascii'))


if __name__ == '__main__':
    host = socket.gethostname()
    port = 12345
    print('Hostname for client: {}'.format(host))

    try:
        soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    except socket.error:
        exit('Failed to create socket.')

    # this is for easy starting/killing the app
    soc.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    try:
        soc.bind((host,port))
    except socket.error:
        exit('Failed to bind socket.')

    try:
        soc.listen(client_limit)
    except socket.error:
        exit('Failed to listen on the socket.')

    try:
        # Continuously accept new incoming clients
        while True:
            # Accept client connectin
            client_socket, addr = soc.accept()

            # Check if the max number of clients has been reached
            if len(my_clients) < client_limit:

                # Add the new client's information to a dictionary that stores client connections
                my_clients[addr] = client_socket
                print('Got a new connection from {}'.format(addr))

                try:
                    new_client_thread = ClientThread(client_socket, addr)
                except:
                    exit('Failed to create thread.')

                new_client_thread.daemon = True

                try:
                    new_client_thread.start()
                except:
                    exit('Failed to start thread.')

            # If the max number of clients are connected, notify the new
            # client trying to connect, and close their connection
            else:
                message = 'The server has reached its client limit of {}'.format(client_limit)
                client_socket.sendall(bytes(message, 'ascii'))
                client_socket.close()

    # If the server recieves a keyboard interrupt, send clients a message that the server is
    # closing in 10 seconds.
    except KeyboardInterrupt:
        print('Shutting down server in 10 seconds..')
        for client in my_clients.values():
            response = "Shutting down server in 10 seconds.."
            with lock:
                client.sendall(bytes(response, 'ascii'))
        sleep(10)

    try:
        # Close the server socket
        soc.close()
    except:
        exit('Failed to close the server socket.')

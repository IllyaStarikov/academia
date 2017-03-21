#!/usr/bin/python3
import json
import select
import socket
import sys
import time


def client(ip, port):
    my_username = input("Enter a username: ")
    if len(my_username) > 12:
        my_username = my_username[:12]
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.settimeout(2)
    sock.connect((ip, port))
    sys.stdout.write(">>>")
    sys.stdout.flush()
    running = True
    while running:
        socket_list = [sys.stdin, sock]
        ready_to_read,ready_to_write,in_error = select.select(socket_list,[],[],0)

        for s in ready_to_read:
            if s == sock:
                response_json = str(sock.recv(1024), 'utf-8')
                if response_json:
                    try:
                        response = json.loads(response_json)['new_message']
                        peer_username = response['user']
                        timestamp = response['timestamp']
                        message = response['message']
                        peer_message = "{} {:>12}: {}".format(timestamp, peer_username, message)
                    except KeyError:
                        response = json.loads(response_json)['error']
                        peer_message = "Something went wrong: {}".format(response)
                    sys.stdout.write(peer_message)
                    sys.stdout.write(">>>")
                    sys.stdout.flush()
            else:
                message = s.readline()
                if message.strip('\n') == '/quit':
                    sock.shutdown(socket.SHUT_WR)
                    sock.close()
                    running = False
                    break
                else:
                    message_json = {
                            "new_message": {
                                "channel_receiving_message": "Channel 1",
                                "user": my_username,
                                "timestamp": time.strftime("%H:%M:%S", time.localtime()),
                                "message": message,
                                },
                            }
                    sock.sendall(bytes(json.dumps(message_json), 'utf-8'))
                    sys.stdout.write(">>>")
                    sys.stdout.flush()

if __name__ == "__main__":
    # client("camelotserver.ddns.net", 9009)
    client("localhost", 9009)

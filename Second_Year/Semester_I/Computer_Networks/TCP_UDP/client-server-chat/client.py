import socket
import struct
import threading
import time

SERVER_IP = '192.168.100.110'
SERVER_PORT = 1234
CHAT_PORT = 1235

peers = []
chat_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
chat_socket.bind(('0.0.0.0', CHAT_PORT))

def new_peer_notification(cs):
    while (True):
        peer_ip_length = cs.recv(4)
        peer_ip_length = struct.unpack("!I", peer_ip_length)[0]

        peer_ip = cs.recv(peer_ip_length)
        peer_ip = peer_ip.decode('utf-8')

        peers.append(peer_ip)
        time.sleep(0.2)

def chat_send(message):
    message_bytes = message.encode('utf-8')

    for peer_ip in peers:
        chat_socket.sendto(struct.pack("!I", len(message_bytes)), (peer_ip, CHAT_PORT))
        chat_socket.sendto(message_bytes, (peer_ip, CHAT_PORT))


def chat_update():
    global chat_socket

    while (True):
        message_length, source = chat_socket.recvfrom(4)
        message_length = struct.unpack("!I", message_length)[0]

        message, source = chat_socket.recvfrom(message_length)
        message = message.decode('utf-8')

        print(source[0], " : ", message)

        time.sleep(0.2)

if __name__ == "__main__":
    try:
        cs = socket.create_connection((SERVER_IP, SERVER_PORT))
    except socket.error as msg:
        print("Error connecting to server: ", msg.strerror)
        exit(-1)

    new_peer_notification_thread = threading.Thread(target=new_peer_notification, args=(cs,), daemon=True)

    chat_update_thread = threading.Thread(target=chat_update, daemon=True)
    chat_update_thread.start()

    print("Connecting to chat...")

    # get IPs of the other peers
    peers_length = cs.recv(4)
    peers_length = struct.unpack("!I", peers_length)[0]

    for p in range(peers_length):
        peer_ip_length = cs.recv(4)
        peer_ip_length = struct.unpack("!I", peer_ip_length)[0]

        peer_ip = cs.recv(peer_ip_length)
        peer_ip = peer_ip.decode('utf-8')

        peers.append(peer_ip)

    print("You are connected to chat!")

    new_peer_notification_thread.start()

    while (True):
        message = input("")
        chat_send(message)

# TODO remove client from peers when disconnecting
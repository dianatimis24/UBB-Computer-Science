import socket
import struct
import threading

IP = '0.0.0.0'
PORT = 1234

clients = []
clients_lock = threading.Lock()
threads = []

def manage_new_client(client_socket):
    global clients, clients_lock

    send_peers(client_socket) # send to new client the IPs of the active clients
    new_client_notification(client_socket) # notify the active clients there is a new client

    clients_lock.acquire()
    clients.append(client_socket)
    clients_lock.release()

def new_client_notification(client_socket):
    global clients, clients_lock

    client_ip = client_socket.getpeername()[0]

    # send to each active client the IP of the new client
    clients_lock.acquire()
    for cs in clients:
        cs.sendall(struct.pack("!I", len(client_ip)))
        cs.sendall(client_ip.encode('utf-8'))
    clients_lock.release()

def send_peers(client_socket):
    global clients, clients_lock

    client_socket.sendall(struct.pack("!I", len(clients))) # number of clients

    clients_lock.acquire()
    for c in clients:
        client_ip = c.getpeername()[0]
        client_socket.sendall(struct.pack("!I", len(client_ip))) # length of peer IP
        client_socket.sendall(client_ip.encode('utf-8')) # peer IP
    clients_lock.release()

if __name__ == "__main__":
    try:
        rs = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # TCP socket
        rs.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) # reuse port
        rs.bind((IP, PORT))
        rs.listen(5)
    except socket.error as msg:
        print("Error creating socket: ", msg.strerror)
        exit(-1)

    while (True):
        print("Waiting for clients...")
        client_socket, client_address = rs.accept()
        print("New client from ", client_address)

        client_thread = threading.Thread(target=manage_new_client, args=(client_socket,))
        threads.append(client_thread)
        client_thread.start()

# TODO remove peer from chat when disconected
import socket, threading
import struct

HOST = "0.0.0.0"
PORT = 1234

threads = []
clients_files = {}
files_lock = threading.Lock()

def manage_client(client_socket):
    add_client(client_socket)

    while (True):
        request_file(client_socket)


def add_client(client_socket):
    global clients_files, files_lock

    # receive files of client
    files = ""
    try:
        files = client_socket.recv(1024)
        files = files.decode('utf-8')
    except socket.error as message:
        print("Error receiving files: ", message.strerror)
        client_socket.close()
        exit(-2)


    files_lock.acquire()
    clients_files[client_socket] = files.split(';')[:-1]
    files_lock.release()
    # print(str(clients_files))

def request_file(client_socket):
    global clients_files, files_lock

    # receive name of the file to request
    file_name = ""
    try:
        file_name = client_socket.recv(1024)
        file_name = file_name.decode('utf-8')
    except socket.error as message:
        print("Error receiving data: ", message.strerror)
        client_socket.close()
        exit(-2)


    peer_ip = ""
    peer_port = 0

    # find client with the requested file
    files_lock.acquire()
    for peer in clients_files.keys():
        peer_files = clients_files[peer]
        for f in peer_files:
            if f == file_name:
                peer_ip = peer.getpeername()[0]
                peer_port = peer.getpeername()[1]
                break
    files_lock.release()

    print("File ", file_name, " found at peer IP ", peer_ip, ", port ", str(peer_port))

    # send peer address to client
    try:
        peer_ip_bytes = peer_ip.encode('utf-8')
        peer_ip_length = len(peer_ip_bytes)
        client_socket.sendall(struct.pack("!I", peer_ip_length))
        client_socket.sendall(peer_ip_bytes)
        client_socket.sendall(struct.pack("!I", peer_port))
    except socket.error as message:
        print("Error finding peer: ", message.strerror)
        client_socket.close()
        exit(-2)


if __name__ == "__main__":
    try:
        rs = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        rs.bind((HOST, PORT))
        rs.listen(5)
    except socket.error as message:
        print("Error creating server: ", message.strerror)
        exit(-1)

    while (True):
        try:
            print("Waiting for clients...")
            client_socket, client_address = rs.accept()
            print("Client connected from " + client_address[0] + ", " + str(client_address[1]))

            client_thread = threading.Thread(target=manage_client, args=(client_socket,))
            threads.append(client_thread)
            client_thread.start()
        except socket.error as message:
            print("Error: ", message.strerror)
            rs.close()
            exit(-2)
import socket, threading, os
import struct

HOST = '192.168.100.110' # 'localhost'
PORT = 1234
PEER_HOST = '0.0.0.0'
PEER_PORT = 1235

def peer_server(directory_name):
    # create socket for communicating with other clients
    try:
        ps = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        ps.bind((PEER_HOST, PEER_PORT))
        ps.listen(5)
    except socket.error as message:
        print("Error: ", message.strerror)
        exit(-1)

    while (True):
        # connect to client - receive name of file to send
        try:
            peer_socket, peer_address = ps.accept()
            # print("Peer connected from ", peer_socket.getpeername())

            file_name = peer_socket.recv(1024)
            file_name = file_name.decode('utf-8')
        except socket.error as message:
            print("Error: ", message.strerror)
            ps.close()
            exit(-2)

        # read contents of file
        f = open(os.path.join(directory_name, file_name), "r")
        content = f.read()
        f.close()

        # send file contents to the client
        try:
            peer_socket.sendall(content.encode('utf-8'))
        except socket.error as message:
            print("Error: ", message.strerror)
            peer_socket.close()
            exit(-2)

        peer_socket.close()


def get_file_peer(peer_ip, file_name, directory_path):
    try:
        ps = socket.create_connection((peer_ip, PEER_PORT)) # connect to peer
    except socket.error as message:
        print("Error: ", message.strerror)
        exit(-1)

    # send file name - receive the content of the file
    try:
        ps.sendall(file_name.encode('utf-8'))
        file_content = ps.recv(1024)
        file_content = file_content.decode('utf-8')
    except socket.error as message:
        print("Error: ", message.strerror)
        ps.close()
        exit(-2)

    # save content in a copy file on the client
    # print("File content: ", file_content)
    save_file(directory_path, file_name, file_content)
    ps.close()

def save_file(directory_path, file_name, file_content):
    file = open(os.path.join(directory_path, "copy_" + file_name), "w")
    file.write(file_content)
    file.close()

if __name__ == "__main__":
    try:
        s = socket.create_connection((HOST, PORT))
    except socket.error as message:
        print("Error connecting to server: ", message.strerror)
        exit(-1)

    directory_path = input("Directory path: ")

    # start 'server' thread of client to send the file to other clients
    peer_thread = threading.Thread(target=peer_server, args=(directory_path,))
    peer_thread.start()

    # find all files in the given directory path
    files = ""
    for f in os.listdir(directory_path):
        if os.path.isfile(os.path.join(directory_path, f)):
            files += f + ";"
    print("Files: " + files)

    # send to server all files
    try:
        s.sendall(files.encode('utf-8'))
    except socket.error as message:
        print("Error sending directory: ", message.strerror)
        s.close()
        exit(-2)

    while (True):
        # send to server file to request
        file_name = input("File name to request: ")

        try:
            s.sendall(file_name.encode('utf-8'))
        except socket.error as message:
            print("Error sending data: ", message.strerror)
            s.close()
            exit(-2)

        # receive from server peer address
        try:
            peer_ip_length = s.recv(4)
            peer_ip_length = struct.unpack("!I", peer_ip_length)[0]

            peer_ip = s.recv(peer_ip_length)
            peer_ip = peer_ip.decode('utf-8')

            peer_port = s.recv(4)
            peer_port = struct.unpack("!I", peer_port)[0]

            print("Peer IP " + peer_ip + ", port " + str(peer_port))
        except socket.error as message:
            print("Error receiving peer: ", message.strerror)
            s.close()
            exit(-2)

        # get from peer the file
        get_file_peer(peer_ip, file_name, directory_path)

    # peer_thread.join()
    # s.close()
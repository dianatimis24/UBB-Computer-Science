import socket, struct, threading, os, time

HOST = '0.0.0.0'
PORT = 1234

reset_event = threading.Event()
threads = []

def send_file(client_socket):
    global reset_event

    client_name = client_socket.getpeername()
    # client connected
    print("Client connected from: ", client_name)

    # receive data from client
    try:
        file_path = client_socket.recv(1024) # ~ string
        file_path = file_path.decode('ascii')
        print("File path: ", file_path)
    except socket.error as message:
        print("Error receiving data: ", message.strerror)
        client_socket.close()
        return

    # get length of a file
    file_length = -1
    try:
        if not os.path.isfile(file_path): raise OSError()
        file_length = os.path.getsize(file_path) # returns the size, in bytes, of path (OSError if path not found)
    except OSError as path_message:
        # file does not exist: send length -1 and no content
        print("File does not exist")
        client_socket.sendall(struct.pack("!i", file_length))
        # client_socket.send()
        time.sleep(0.5)
        client_socket.close()
        return

    # get content of a file
    file = open(file_path, "r")
    file_content = file.read()
    file.close()

    # send data to client
    try:
        client_socket.send(struct.pack("!I", file_length))
        client_socket.sendall(bytes(file_content, 'ascii'))
    except socket.error as message:
        print("Error sending data: ", message.strerror)
        client_socket.close()
        return

    # close socket connection with client
    time.sleep(0.5)
    client_socket.close()

def reset_server(): # TODO where to set the reset_event to join the threads?
    global reset_event, threads

    reset_event.wait()
    for t in threads:
        t.join()
    threads = []

    print("All threads finished")
    print("Server closed")

if __name__ == "__main__":
    try:
        rs = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # create TCP socket
        rs.bind((HOST, PORT))
        rs.listen(5) # queue of 5 clients
    except socket.error as message:
        print("Error: ", message.strerror)
        exit(-1)

    # reset_thread = threading.Thread(target=reset_server, daemon=True)
    # reset_thread.start()

    while True:
        print("Waiting for client to connect")
        client_socket, client_address = rs.accept()
        send_file(client_socket)

        # client_thread = threading.Thread(target=send_file, args=(client_socket,))
        # threads.append(client_thread)
        # client_thread.start()
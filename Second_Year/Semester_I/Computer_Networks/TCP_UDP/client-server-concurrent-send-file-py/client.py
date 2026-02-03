import socket, struct, sys

HOST = 'localhost'
PORT = 1234

if __name__ == "__main__":
    # connect the client to the server
    try:
        s = socket.create_connection((HOST, PORT))
    except socket.error as message:
        print("Error: ", message.strerror)
        exit(-1)

    file_path = input("File path: ")
    try:
        # send data to server
        s.sendall(bytes(file_path, 'ascii'))

        # receive data from server
        file_length = s.recv(4) # ~ int
        file_length = struct.unpack('!i', file_length)[0]  # = ntoh

        file_content = s.recv(file_length if file_length != -1 else 0)
        file_content = file_content.decode('ascii')
    except socket.error as message:
        print("Error: ", message.strerror)
        s.close()
        exit(-2)

    print("File length: ", file_length)
    print("File content: ", file_content)
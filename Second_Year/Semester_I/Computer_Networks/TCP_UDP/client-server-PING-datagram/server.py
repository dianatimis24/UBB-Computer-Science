import socket

SERVER_IP = '0.0.0.0'
SERVER_PORT = 1234

if __name__ == "__main__":
    try:
        rs = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        rs.bind((SERVER_IP, SERVER_PORT))
    except socket.error as msg:
        print("Error creating socket: ", msg.strerror)
        exit(-1)

    print("Server start...")

    while True:
        data, source = rs.recvfrom(1024)

        rs.sendto(data, source)
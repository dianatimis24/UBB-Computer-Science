import socket

# search <part number>
# get <part number>
# order <part number> <quantity>
# exit

SERVER_IP = '192.168.100.110'
SERVER_PORT = 1234

if __name__ == "__main__":
    try:
        cs = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        cs.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    except socket.error as msg:
        print("Error creating socket: ", msg.strerror)
        exit(-1)

    while True:
        command = input("> ")
        cs.sendto(command.encode(), (SERVER_IP, SERVER_PORT))

        message, source = cs.recvfrom(1024)
        print(message.decode())

        if command == "exit":
            break
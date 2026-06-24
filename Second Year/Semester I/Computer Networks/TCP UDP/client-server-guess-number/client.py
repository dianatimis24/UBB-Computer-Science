import socket, random
import struct
import time

SERVER_IP = '192.168.100.110'
SERVER_PORT = 1234

lower_bound = 0
upper_bound = 100

if __name__ == "__main__":
    try:
        cs = socket.create_connection((SERVER_IP, SERVER_PORT))
    except socket.error as msg:
        print("Error connecting to server: ", msg.strerror)
        exit(-1)

    while True:
        number = random.randrange(lower_bound, upper_bound)
        print("Number: ", number)
        cs.send(struct.pack("!I", number))

        response = cs.recv(1024)
        response = response.decode('utf-8')
        print(response)

        if response == "smaller":
            upper_bound = number - 1
        elif response == "larger":
            lower_bound = number + 1
        else:
            break

        time.sleep(1)

    cs.close()
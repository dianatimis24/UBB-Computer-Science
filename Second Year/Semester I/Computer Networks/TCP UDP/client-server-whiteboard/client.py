import socket, time, threading


IP = '192.168.100.110' # 'localhost'
TCP_IP = '0.0.0.0'
PORT = 1234
TCP_PORT = 1235

def send_command(s):
    # command = input("Command: ")
    # s.sendto(bytes(command, 'ascii'), (IP, PORT))
    while True:
        command = input("Command: ")
        s.sendto(bytes(command, 'ascii'), (IP, PORT))
        time.sleep(0.1)

def update_image():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((TCP_IP, TCP_PORT))
    s.listen(3)

    while True:
        transfer_socket, addr = s.accept()
        data = transfer_socket.recv(1024)
        print(data.decode('ascii'))
        time.sleep(0.5)

if __name__ == "__main__":
    # s = socket.create_connection((IP, PORT))
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    client_update = threading.Thread(target=update_image, daemon=True)
    client_update.start()

    send_command(s)

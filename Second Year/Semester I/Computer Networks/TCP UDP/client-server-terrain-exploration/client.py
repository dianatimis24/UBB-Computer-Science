import socket, time, threading, random
import string
import struct


SERVER_IP = '192.168.100.110'
SERVER_PORT = 1234
BROADCAST_IP = '0.0.0.0'
BROADCAST_PORT = 1235

N = 5
stop_event = threading.Event()
stop_event.clear()

broadcast_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
broadcast_socket.bind((BROADCAST_IP, BROADCAST_PORT))

def broadcast_receive():
    global BROADCAST_IP, BROADCAST_PORT, stop_event

    while True:
        map_length, source = broadcast_socket.recvfrom(4)
        map_length = struct.unpack("!I", map_length)[0]

        map_data, source = broadcast_socket.recvfrom(map_length)
        map_data = map_data.decode('utf-8')

        print("Map: ", map_data)

        if is_map_explored(map_data):
            stop_event.set()
            break

        time.sleep(0.5)

def is_map_explored(map_data: string):
    map_cells = map_data.split(',')

    for cell in map_cells:
        if cell.strip() == "'u'":
            return False

    return True

def stop_client(broadcast_thread):
    global stop_event, broadcast_socket

    stop_event.wait()

    broadcast_thread.join()
    broadcast_socket.close()

    print("Exploration finished!")

if __name__ == "__main__":
    try:
        cs = socket.create_connection((SERVER_IP, SERVER_PORT))
    except socket.error as msg:
        print("Error connecting to server: ", msg.strerror)
        exit(-1)

    broadcast_thread = threading.Thread(target=broadcast_receive, daemon=True)
    stop_thread = threading.Thread(target=stop_client, args=(broadcast_thread,), daemon=True)

    stop_thread.start()
    broadcast_thread.start()

    print("Connected to server")

    while True:
        if stop_event.is_set():
            break

        position = random.randrange(0, N)
        cs.sendall(struct.pack("!H", position))

        type = 'u'
        while type == 'u':
            type = random.choice(string.ascii_lowercase)
        cs.sendall(bytes(type, 'utf-8'))

        print("Position ", position, " type ", type)

        time.sleep(5)

    stop_thread.join()
    cs.close()
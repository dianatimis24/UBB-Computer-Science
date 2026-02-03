import socket, time, threading
import struct


SERVER_IP = '0.0.0.0'
SERVER_PORT = 1234
BROADCAST_IP = '192.168.100.110'
BROADCAST_PORT = 1235

N = 5
map = []
clients = []

threads = []
map_lock = threading.Lock()
clients_lock = threading.Lock()
send_event = threading.Event()
send_event.clear()
stop_event = threading.Event()
stop_event.clear()

broadcast_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

def generate_map():
    for i in range(N):
        map.append('u')

    print("Initial map: ", map)

def update_map(client_ip, position, type):
    global map, map_lock

    map_lock.acquire()
    if map[position] == 'u':
        map[position] = type
    map_lock.release()

    print("[", client_ip, "] Position ", position, " type ", type, " : ", map)

    send_event.set()

def manage_client(client_socket):
    global clients, clients_lock

    clients_lock.acquire()
    clients.append(client_socket)
    clients_lock.release()

    explore(client_socket)

def explore(client_socket):
    global stop_event
    while True:
        if stop_event.is_set():
            break

        try:
            position = client_socket.recv(2)
            position = struct.unpack("!H", position)[0]

            type = client_socket.recv(1)
            type = type.decode('utf-8')

            update_map(client_socket.getpeername()[0], position, type)
        except socket.error as s_msg:
            print("Error receiving data: ", s_msg.strerror)
            client_socket.close()
            exit(-2)
        # except struct.error as st_msg: # server received a position while the exploration is being finished --> struct raises error
        #     continue

        time.sleep(0.5)

def broadcast_send():
    global map, clients, BROADCAST_PORT, send_event, map_lock, clients_lock, stop_event

    while True:
        send_event.wait()

        map_lock.acquire()
        map_data = str(map)[1:-1]
        map_lock.release()

        clients_lock.acquire()
        for c in clients:
            c_ip = c.getpeername()[0]
            broadcast_socket.sendto(struct.pack("!I", len(map_data)), (c_ip, BROADCAST_PORT))
            broadcast_socket.sendto(map_data.encode('utf-8'), (c_ip, BROADCAST_PORT))
        clients_lock.release()

        if is_map_explored():
            stop_event.set()
            break

        send_event.clear()
        time.sleep(0.5)

def is_map_explored():
    global map, map_lock

    map_lock.acquire()
    for cell in map:
        if cell == 'u':
            map_lock.release()
            return False
    map_lock.release()

    return True

def stop_server():
    global threads, clients, broadcast_socket, stop_event

    stop_event.wait()

    for t in threads:
        t.join()

    for c in clients:
        c.close()

    print("Exploration finished!")

if __name__ == "__main__":
    try:
        rs = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        rs.bind((SERVER_IP, SERVER_PORT))
        rs.settimeout(5)
        rs.listen(2)
    except socket.error as msg:
        print("Error creating socket: ", msg.strerror)
        exit(-1)

    generate_map()

    stop_thread = threading.Thread(target=stop_server, daemon=True)
    stop_thread.start()

    broadcast_thread = threading.Thread(target=broadcast_send, daemon=True)
    threads.append(broadcast_thread)
    broadcast_thread.start()

    while True:
        if stop_event.is_set():
            break

        print("Waiting for clients...")
        try:
            client_socket, client_address = rs.accept()
            print("New client from ", client_address)

            client_thread = threading.Thread(target=manage_client, args=(client_socket,))
            threads.append(client_thread)
            client_thread.start()
        except TimeoutError as t_msg:
            time.sleep(0.5)
        except socket.error as s_msg:
            print("Error connecting to client: ", s_msg.strerror)
            rs.close()
            exit(-2)

    stop_thread.join()
    rs.close()
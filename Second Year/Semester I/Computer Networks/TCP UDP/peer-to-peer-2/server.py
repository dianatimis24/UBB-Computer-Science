import socket
import struct
import time
from threading import Thread, Lock

PORT = 7000
connected_clients = []
threads = []
clients_lock = Lock()


def send_update_to_all(addr, new = True):
    global connected_clients, clients_lock

    for _sock, (_ip1, _port1) in connected_clients:
        try:
            send_str = f"{"N" if new else "D"}|{addr[0]}:{addr[1]}"
            _sock.sendall(send_str.encode('ascii'))
        except socket.error as e:
            print(f"[TIMEOUT ERROR] {e}. Disconnecting {_ip1}:{_port1}")

def client_worker(client_socket: socket.socket, addr: tuple):
    global connected_clients, clients_lock
    print(connected_clients)

    try:
        # Get the port
        port = client_socket.recv(2)
        port = struct.unpack("!H", port)[0]

        print("[CLIENT] Got port", port)

    except socket.error as e:
        print("[RECV ERROR]")
        client_socket.close()
        return

    # Send the list of all connections
    list_str = '|'.join(f"{_ip}:{_port}" for _, (_ip, _port) in connected_clients)
    try:
        if list_str:
            client_socket.sendall(list_str.encode('ascii'))
        else:
            client_socket.sendall(b'\x69')
    except socket.timeout as e:
        print(f"[TIMEOUT ERROR] {e}")
        client_socket.close()
    except socket.error as e:
        print(f"[SEND ERROR] {e}")

    send_update_to_all((addr[0], port))

    # Add it to the connected clients list
    clients_lock.acquire()
    connected_clients.append((client_socket, (addr[0], port)))
    clients_lock.release()

    while True:
        try:
            # Get input from the client
            print("[CLIENT WORKER] Waiting for exit byte...")
            client_socket.recv(1)

            print("[CLIENT WORKER] Disconnecting...")
            client_socket.close()

            clients_lock.acquire()
            connected_clients = [x for x in connected_clients if x[0] != client_socket]
            clients_lock.release()

            send_update_to_all((addr[0], port), False)
            break
        except socket.timeout:
            pass
        except socket.error as e:
            print(f"[CLIENT WORKER] {e}")


def main():
    global threads, connected_clients

    try:
        tcp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        tcp_socket.bind(('0.0.0.0', PORT))
        tcp_socket.listen(500)

        tcp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    except socket.error as e:
        print(f"[SOCKET CREATION] {e}")
        exit(-1)

    while True:
        try:
            print("Listening for connections...")
            tcp_socket.settimeout(60)
            client_socket, addr = tcp_socket.accept()
            tcp_socket.settimeout(None)

            # Set a timeout of sending so we know if a connection went offline
            client_socket.setsockopt(socket.SOL_SOCKET, socket.SO_SNDTIMEO, 5000)

            print("Accepted", addr)

            client_t = Thread(target=client_worker, args=(client_socket, addr))
            threads.append(client_t)
            client_t.start()
        except:
            if len(connected_clients) == 0:
                break

    for t in threads:
        t.join()

main()

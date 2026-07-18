import socket
import struct
import sys
from csv import unix_dialect
from threading import Thread, Lock, RLock

DEFAULT_UDP_PORT = 4544
TCP_PORT = 7000

available_clients = []
is_running = True
running_lock = Lock()
clients_lock = Lock()

def tcp_listener(tcp_socket: socket.socket):
    global is_running, clients_lock

    while is_running:
        try:
            update_str = tcp_socket.recv(1024).decode('ascii')
            if not update_str: # skip empty strings
                continue
            print(update_str)
            status, ip = update_str.split("|")
            if status == "N":
                print(f"{ip} has connected to the server.")

                _ip, _port = ip.split(":")
                clients_lock.acquire()
                available_clients.append((_ip, int(_port)))
                clients_lock.release()
            elif status == "D":
                print(f"{ip} has disconnected from the server")

                _ip, _port = ip.split(":")
                clients_lock.acquire()
                available_clients.remove((_ip, int(_port)))
                clients_lock.release()

        except socket.timeout:
            pass
        except Exception as e:
            print(f"[TCP LISTENER] {e}")

def udp_listener(udp_socket: socket.socket):
    global is_running

    while is_running:
        try:
            msg, addr = udp_socket.recvfrom(1024)
            msg = msg.decode("ascii")

            print(f"[UDP LISTENER]: {addr[0]}:{addr[1]} sent: \'{msg}\'")
        except socket.timeout:
            pass
        except Exception as e:
            print(f"[UDP LISTENER] {e}")

def main():
    global available_clients
    global is_running, available_clients

    try:
        if len(sys.argv) == 2:
            udp_port = int(sys.argv[1])
        else:
            udp_port = DEFAULT_UDP_PORT
    except Exception as e:
        print(e)
        udp_port = DEFAULT_UDP_PORT

    try:
        print("Opening UDP socket...")
        udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        udp_socket.bind(('0.0.0.0', udp_port))
        udp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_RCVTIMEO, 5000)


        print("Connecting to server...")
        tcp_socket = socket.create_connection(("localhost", TCP_PORT))
        tcp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_RCVTIMEO, 5000)
        # Send the port
        print("Sending the port")
        tcp_socket.sendall(struct.pack("!H", udp_port))

        # Recive the list
        print("Reciving list")
        avail_clients_str = tcp_socket.recv(1024)
        if len(avail_clients_str) == 1:
            pass
        else:
            avail_clients_str = avail_clients_str.decode('ascii')
            print("Clients list:", avail_clients_str)
            for ip_str in avail_clients_str.split("|"):
                ip, port = ip_str.split(":")
                available_clients.append((ip, int(port)))
    except socket.error as e:
        print(f"[SERVER CREATION ERROR] {e}")
        exit(-1)

    # Create the 2 threads
    tcp_listener_t, udp_listener_t = Thread(target=tcp_listener, args=(tcp_socket,)), Thread(target=udp_listener, args=(udp_socket,))
    tcp_listener_t.start()
    udp_listener_t.start()

    while is_running:
        # Get the message from the keyboard
        msg = input("Input your message (QUIT to exit):")
        if msg == "QUIT":
            tcp_socket.send(b'\x01')
            is_running = False
            break

        # Send the message to everyone
        for _ip, _port in available_clients:
            try:
                print(f"[MAIN] Sending {msg} to {_ip}:{_port}")
                udp_socket.sendto(msg.encode('ascii'), (_ip, _port))
            except Exception as e:
                ...

    tcp_listener_t.join()
    udp_listener_t.join()

    tcp_socket.close()
    udp_socket.close()

main()
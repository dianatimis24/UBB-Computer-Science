import struct
import socket
import threading
from dataclasses import dataclass, field
from os import times_result
from threading import Thread, Lock
import time


class Server:
    RENDEVOUS_PORT = 4544
    HEARTBEAT_PORT = 1212
    SENDER_PORT = 4112

    @staticmethod
    def __welcome_message() -> str:
        return f"""WELCOME TO THE SERVER. COMMANDS:
    list - lists the available files
    download <file_name> - downloads the file (into ./downloads)
    exit - exits the server"""

    def __timer_thread(self):

        tries = 0
        MAX_TRIES = 3
        while self.running:
            if len(self.client_files_lut) == 0:
                tries += 1
            else:
                tries = 0

            if tries == MAX_TRIES:
                print(f"[TIMER] 0 clients connected for {MAX_TRIES} tries. Stopping server.")
                self.running = False
                break
            else:
                print(f"[TIMER] {len(self.client_files_lut)} clients connected.")

            time.sleep(20)


    def __heartbeat_thread(self):
        while self.running:
            print(self.client_files_lut, self.files_clients_lut)

            # Send a heartbeat to all connected clients
            clients_to_disconnect = []
            for client, ip in self.heartbeat_clients:
                try:
                    # Send a byte to the client
                    client.send(struct.pack("!B", 0x01))
                    # Wait for recive
                    client.recv(1)
                except socket.error:
                    print(f"[HEARTBEAT] Didn't recive answer from {ip}. Closing connection.")
                    clients_to_disconnect.append(ip)

            for client in clients_to_disconnect:
                self.__disconnect_client(client)

            time.sleep(5)

    def __disconnect_client(self, ip: str):
        # Delete the entry from the client_files_lut
        self.client_lock.acquire()

        if ip not in self.client_files_lut:
            self.client_lock.release()
            return

        # delete the ip from each file
        for file in self.client_files_lut[ip]:
            self.files_clients_lut[file] = [x for x in self.files_clients_lut[file] if x[0] != ip]

        # Remove from heartbeat
        self.heartbeat_clients = [x for x in self.heartbeat_clients if x[1] != ip]

        del self.client_files_lut[ip]

        self.client_lock.release()


    def __get_ip_for_file(self, file_name: str) -> tuple:
        if file_name not in self.files_clients_lut:
            raise FileNotFoundError()

        from random import randint

        # Select a random entry from the list
        return self.files_clients_lut[file_name][randint(0, len(self.files_clients_lut[file_name]) - 1)]


    def __client_thread(self, client_socket: socket.socket, ip: str):
        # Get the files
        self.client_lock.acquire()
        try:
            number_of_files = client_socket.recv(4)
            number_of_files = struct.unpack("!i", number_of_files)[0]

            self.client_files_lut[ip] = []

            # Get the file paths
            for _ in range(number_of_files):
                file_name = client_socket.recv(1024)
                file_name = file_name.decode('ascii')

                self.client_files_lut[ip].append(file_name)
                if file_name not in self.files_clients_lut:
                    self.files_clients_lut[file_name] = []

                # append the ip
                self.files_clients_lut[file_name].append((ip, self.SENDER_PORT))
        except socket.error as e:
            print(f"[CLIENT {client_socket.getsockname()}] Failed startup. Closing. {e}")
            client_socket.close()
            self.client_lock.release()
            return

        self.client_lock.release()

        # Send to the client the available commands
        client_socket.send(Server.__welcome_message().encode('ascii'))

        # The loop
        while self.running:
            # get the command
            try:
                command = client_socket.recv(1024).decode('ascii')

                command_args = command.split()

                if command_args[0] == "list":
                    # Send the list of files
                    list_of_files = " ,".join(file for file in self.files_clients_lut).encode('ascii')
                    client_socket.send(list_of_files)

                elif command_args[0] == "exit":
                    self.__disconnect_client(ip)
                    break
                elif command_args[0] == "download":
                    addr, port = self.__get_ip_for_file(command_args[1])

                    # Send the address and port
                    client_socket.send(addr.encode('ascii'))
                    client_socket.send(struct.pack("!H", port))


            except socket.error as e:
                ...
            except FileNotFoundError as e:
                ...

        self.__disconnect_client(ip)
        client_socket.close()

    def __init__(self):
        self.client_files_lut: dict[str, list] = {}
        self.files_clients_lut: dict[str, list] = {}

        self.heartbeat_clients = []
        self.threads = []

        self.running = True
        self.running_lock = Lock()
        self.client_lock = Lock()

        try:
            self.rendevous_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
            self.heartbeat_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)

            self.rendevous_sock.bind(('localhost', self.RENDEVOUS_PORT))
            self.heartbeat_sock.bind(('localhost', self.HEARTBEAT_PORT))

            # Set recive timeout
            self.rendevous_sock.setsockopt(socket.SOL_SOCKET, socket.SO_RCVTIMEO, 5)

            # Set recive and send timeout
            self.heartbeat_sock.setsockopt(socket.SOL_SOCKET, socket.SO_RCVTIMEO, 5)
            self.heartbeat_sock.setsockopt(socket.SOL_SOCKET, socket.SO_SNDTIMEO, 5)

            self.rendevous_sock.listen(500)
            self.heartbeat_sock.listen(500)

            # Start up the heartbeat thread
            self.heartbeat_thread = Thread(target=self.__heartbeat_thread)
            self.heartbeat_thread.start()

            self.timer_thread = Thread(target=self.__timer_thread)
            self.timer_thread.start()
        except (socket.error, threading.ThreadError) as e:
            print(f"[ERROR] {e}")
            exit(-1)

    def run(self):
        while self.running:
            # Set a timeout
            try:
                self.rendevous_sock.settimeout(5)
                client_socket, addr = self.rendevous_sock.accept()
                self.rendevous_sock.settimeout(None)

                # Connect to the heartbeat as well
                self.heartbeat_sock.settimeout(5)
                hb_socket, (ip, port) = self.heartbeat_sock.accept()
                self.heartbeat_sock.settimeout(None)

                self.heartbeat_clients.append((hb_socket, ip))

                # Start a new client thread
                cl_thread = Thread(target=self.__client_thread, args=(client_socket,addr[0]))
                self.threads.append(cl_thread)
                cl_thread.start()

            except socket.error as e:
                print(f"[RENDEVOUS] {e}")

        # Join everything
        self.heartbeat_thread.join()
        self.timer_thread.join()
        for t in self.threads:
            t.join()

Server().run()

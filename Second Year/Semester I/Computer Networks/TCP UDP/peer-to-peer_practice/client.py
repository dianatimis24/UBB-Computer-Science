import os
import struct
import socket
import threading

class Client:
    def __init__(self, host="localhost"):
        self.shared_dir = "./shared"
        self.remote_addr = (host, 4544)
        self.heartbeat_addr = (host, 1212)
        self.sender_port = 4112
        self.remote_control_socket = None
        self.heartbeat_socket = None

    def heartbeat_loop(self):
        while True:
            b = self.heartbeat_socket.recv(1)
            if not b:
                return
            self.heartbeat_socket.send(b)

    def sender_loop(self):
        server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server.bind(("0.0.0.0", self.sender_port))
        server.listen(50)

        while True:
            client, addr = server.accept()
            length = struct.unpack("!I", client.recv(4))[0]
            filename = client.recv(length).decode("ascii")
            path = os.path.join(self.shared_dir, filename)
            try:
                data = open(path, "rb").read()
                client.send(struct.pack("!I", len(data)))
                client.send(data)
            except:
                client.send(struct.pack("!I", 0))
            client.close()

    def start(self):
        files = [f for f in os.listdir(self.shared_dir)
                 if os.path.isfile(os.path.join(self.shared_dir, f))]

        self.remote_control_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.remote_control_socket.connect(self.remote_addr)

        self.heartbeat_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.heartbeat_socket.connect(self.heartbeat_addr)

        threading.Thread(target=self.heartbeat_loop, daemon=True).start()
        threading.Thread(target=self.sender_loop, daemon=True).start()

        self.remote_control_socket.send(struct.pack("!i", len(files)))
        for filename in files:
            self.remote_control_socket.send(filename.encode("ascii"))

        banner = self.remote_control_socket.recv(1024)
        print(banner.decode("ascii"))

    def cmd(self, command):
        parts = command.split()
        self.remote_control_socket.send(command.encode("ascii"))

        if parts[0] == "list":
            return self.remote_control_socket.recv(4096).decode("ascii")

        if parts[0] == "download":
            addr = self.remote_control_socket.recv(1024).decode("ascii")
            port = struct.unpack("!H", self.remote_control_socket.recv(2))[0]

            download_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            download_socket.connect((addr, port))

            download_socket.send(struct.pack("!I", len(parts[1])))
            download_socket.send(parts[1].encode("ascii"))

            length = struct.unpack("!I", download_socket.recv(4))[0]
            if length > 0:
                data = download_socket.recv(length)
                open(os.path.join("./downloads", parts[1]), "wb").write(data)

            download_socket.close()

if __name__ == "__main__":
    os.makedirs("./downloads", exist_ok=True)
    client = Client()
    client.start()
    while True:
        command = input().strip()
        if command == "exit":
            client.cmd("exit")
            break
        output = client.cmd(command)
        if output:
            print(output)

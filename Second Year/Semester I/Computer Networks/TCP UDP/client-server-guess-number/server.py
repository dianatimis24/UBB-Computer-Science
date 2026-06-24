import socket, random, threading
import struct
import time

SERVER_IP = '0.0.0.0'
SERVER_PORT = 1234

threads = []
clients = {}

number = random.randrange(0, 100)

guess_event = threading.Event()
guess_event.clear()
reset_event = threading.Event()
reset_event.clear()
# locks
clients_lock = threading.Lock()


def manage_client(client_socket):
    global clients, number, clients_lock

    clients_lock.acquire()
    clients[client_socket] = 0
    clients_lock.release()

    while True:
        try:
            answer = client_socket.recv(4)
            answer = struct.unpack("!I", answer)[0]
            print(client_socket.getpeername(), " : ", answer)

            clients_lock.acquire()
            clients[client_socket] += 1
            clients_lock.release()

            response = "smaller"
            if guess_event.is_set():
                response = f"You lost - after {clients[client_socket]} tries"
            elif answer < number:
                response = "larger"
            elif answer == number:
                response = f"You win - within {clients[client_socket]} tries"
                guess_event.set()
                reset_event.set()

            client_socket.send(response.encode('utf-8'))
        except struct.error:
            continue

        if guess_event.is_set():
            break

        time.sleep(0.2)


def restart():
    global clients, threads, number, reset_event, guess_event

    while True:
        reset_event.wait()
        print("Round finished. Next round loading...")

        guess_event.clear()

        for t in threads:
            t.join()
        threads = []

        for c in clients.keys():
            c.close()
        clients = {}

        number = random.randrange(0, 100)
        print("Number: ", number)

        reset_event.clear()


if __name__ == "__main__":
    try:
        rs = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        rs.bind((SERVER_IP, SERVER_PORT))
        rs.listen(5)
    except socket.error as msg:
        print("Error creating socket: ", msg.strerror)
        exit(-1)

    restart_thread = threading.Thread(target=restart)
    restart_thread.start()

    print("Number: ", number)

    while True:
        print("Waiting for clients...")
        client_socket, client_address = rs.accept()
        print(f"New client from {client_address}")

        client_thread = threading.Thread(target=manage_client, args=(client_socket,))
        threads.append(client_thread)
        client_thread.start()

# TODO doesn't work very well with more clients
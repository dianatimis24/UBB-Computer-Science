import socket, struct, random, time, threading

HOST = '0.0.0.0'
PORT = 1234
TIMEOUT = 10

server_random_float = 0.0
best_error = 5.0
winner_client = -1

threads = []
winner_lock = threading.Lock()
client_lock = threading.Lock()
stop_event = threading.Event()
stop_event.clear()

clients_barrier = threading.Barrier(1)

def check_guess(client_socket):
    global server_random_float, best_error, winner_client, winner_lock, client_lock
    global clients_barrier

    try:
        client_random_float = client_socket.recv(4)
        client_random_float = struct.unpack("!f", client_random_float)[0]
    except socket.error as message:
        print("Error receiving data: ", message.strerror)
        exit(-2)

    clients_barrier.wait()

    winner_lock.acquire()
    if abs(server_random_float - client_random_float) < best_error:
        best_error = abs(server_random_float - client_random_float)
        winner_client = threading.get_ident()
    winner_lock.release()

    clients_barrier.wait()

    client_answer = "You lost!"
    if (winner_client == threading.get_ident()):
        client_answer = "You have the best guess with an error of |<SRF>" + str(server_random_float) + " - <CRF>" + str(client_random_float) + "| = " + str(best_error)

    try:
        client_socket.sendall(bytes(client_answer, 'ascii'))
    except socket.error as message:
        print("Error sending data: ", message.strerror)
        exit(-2)

    stop_event.set()

def stop_server():
    global threads, stop_event

    stop_event.wait()
    for t in threads:
        t.join()

    threads = []
    stop_event.clear()

if __name__ == "__main__":
    try:
        rs = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # TCP socket
        rs.bind((HOST, PORT))
        rs.listen(5)
        rs.settimeout(1)
    except socket.error as message:
        print("Error creating socket: ", message.strerror)
        exit(-1)

    server_random_float = random.random() # random float between 0.0 and 1.0
    print(server_random_float)

    t = threading.Thread(target=stop_server, daemon=True)
    t.start()

    last_connection_time = time.time()
    nr_clients = 0

    while True:
        print("Waiting for clients...")
        try:
            client_socket, client_address = rs.accept()
            print("Client connected from: ", client_socket.getpeername())
            last_connection_time = time.time()

            t = threading.Thread(target=check_guess, args=(client_socket,))
            threads.append(t)
            nr_clients += 1
        except socket.timeout:
            pass

        if time.time() - last_connection_time > TIMEOUT:
            print("No new connection in the last" + str(TIMEOUT) + " seconds")
            break

    clients_barrier = threading.Barrier(nr_clients                       )
    for t in threads:
        t.start()
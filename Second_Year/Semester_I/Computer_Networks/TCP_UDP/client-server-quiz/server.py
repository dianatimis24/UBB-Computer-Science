import socket, struct, threading, time

SERVER_IP = '0.0.0.0'
SERVER_PORT = 1234
TIMER_PORT = 1235

threads = []
clients = {} # client_socket: {index: answer}
questions = "1+1;2+3;4/2"
n = 3

start_quiz = threading.Event()
start_quiz.clear()

time_up = threading.Event()
time_up.clear()

def manage_client(client_socket):
    global clients, questions, n, start_quiz, time_up
    clients[client_socket] = {}
    client_socket.settimeout(10)

    # wait for quiz to start
    start_quiz.wait()

    # send questions string to client
    client_socket.send(questions.encode())

    # receive answers until all answers sent or time is up
    while len(clients[client_socket]) < n and not time_up.is_set():
        try:
            data = client_socket.recv(1024)

            if time_up.is_set():
                raise socket.error()

            answer_data = (data.decode()).split(' ')
            index = answer_data[0]
            answer = answer_data[1]

            clients[client_socket][index] = answer
        except socket.error as msg:
            break

        time.sleep(0.2)

    # calculate score of client
    print(f"Send score to {client_socket.getpeername()}")
    score = int(100 / n * len(clients[client_socket]))
    client_socket.send(struct.pack("!I", score))

def start():
    print("Quiz round is starting.")
    start_quiz.set()

def timer():
    global clients, TIMER_PORT, time_up, start_quiz

    timer_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    while True:
        # wait for quiz to start
        start_quiz.wait()

        # start timer
        current_timer = 10
        while current_timer >= 0 and start_quiz.is_set():

            # send how much time is left to each client (better to use broadcast)
            for c in clients.keys():
                timer_socket.sendto(struct.pack("!I", current_timer), (c.getpeername()[0], TIMER_PORT))

            print(current_timer, end=", ")
            current_timer -= 1

            time.sleep(1)

        time_up.set()
        start_quiz.clear()
        if current_timer < 0:
            print("Time up.")

if __name__ == "__main__":
    try:
        server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) # reuse port
        server_socket.bind((SERVER_IP, SERVER_PORT))
        server_socket.settimeout(10)
        server_socket.listen(3)
    except socket.error as msg:
        print("Error creating socket: ", msg.strerror)
        exit(-1)

    timer_thread = threading.Thread(target=timer)
    timer_thread.start()

    while True:
        try:
            print("Waiting for clients...")
            client_socket, client_address = server_socket.accept()
            print(f"New client from {client_address}")

            client_thread = threading.Thread(target=manage_client, args=(client_socket,))
            threads.append(client_thread)
            client_thread.start()
        except socket.error as msg:
            # start quiz when no more clients connected in the last 10 seconds
            if clients != {}:
                start()

            # clean up
            for t in threads:
                t.join()

            for c in clients.keys():
                c.close()

            threads = []
            clients = {}

            start_quiz.clear()
            time_up.clear()

            print("Quiz round finished.")
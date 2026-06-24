import socket
import struct
import threading
import time

SERVER_IP = '0.0.0.0'
SERVER_PORT = 1234
TIMER_PORT = 1235

threads = []
clients = {}
questions = "1+1;2+3;4/2"
n = 3

start_quiz = threading.Event()
start_quiz.clear()

def manage_client(client_socket):
    global clients, questions, n, start_quiz
    clients[client_socket] = {}

    start_quiz.wait()

    client_socket.send(questions.encode())

    while len(clients[client_socket]) < n:
        data = client_socket.recv(1024)
        answer_data = (data.decode()).split(' ')
        index = answer_data[0]
        answer = answer_data[1]

        clients[client_socket][index] = answer

        time.sleep(0.2)

    score = 100
    client_socket.send(struct.pack("!I", score))

    client_socket.close()

def start():
    print("Quiz round is starting.")
    start_quiz.set()

if __name__ == "__main__":
    try:
        server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server_socket.bind((SERVER_IP, SERVER_PORT))
        server_socket.settimeout(10)
        server_socket.listen(3)
    except socket.error as msg:
        print("Error creating socket: ", msg.strerror)
        exit(-1)

    while True:
        try:
            print("Waiting for clients...")
            client_socket, client_address = server_socket.accept()
            print(f"New client from {client_address}")

            client_thread = threading.Thread(target=manage_client, args=(client_socket,))
            threads.append(client_thread)
            client_thread.start()
        except socket.error as msg:
            start()

            for t in threads:
                t.join()

            threads = []
            clients = {}

            start_quiz.clear()
            print("Quiz round finished.")
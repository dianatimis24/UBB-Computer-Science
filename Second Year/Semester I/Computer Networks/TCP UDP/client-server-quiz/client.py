import random
import socket
import struct
import threading
import time

SERVER_IP = '192.168.100.110'
CONNECTION_PORT = 1234
TIMER_PORT = 1235

time_up = threading.Event()
time_up.clear()

def timer():
    global time_up, TIMER_PORT

    timer_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    timer_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)  # reuse port
    timer_socket.bind(('0.0.0.0', TIMER_PORT))

    # receive left time from server
    current_time, source = timer_socket.recvfrom(4)
    current_time = struct.unpack("!I", current_time)[0]
    print("Time: ", end="")
    while current_time > 0 and not time_up.is_set():
        print(f"({current_time})", end=", ")

        current_time, source = timer_socket.recvfrom(4)
        current_time = struct.unpack("!I", current_time)[0]

    print(current_time)
    time_up.set()
    if current_time == 0:
        print("TIME UP!")

if __name__ == "__main__":
    try:
        connection_socket = socket.create_connection((SERVER_IP, CONNECTION_PORT))
    except socket.error as msg:
        print("Error connecting to server: ", msg.strerror)
        exit(-1)

    timer_thread = threading.Thread(target=timer)
    timer_thread.start()

    print("Connected to server. Waiting for quiz to start...")

    # receive questions string from server
    data = connection_socket.recv(1024)
    data = data.decode()

    questions = data.split(';')

    # simulate answering questions (in order)
    print("\nQUIZ START!")
    try:
        for q in questions:
            print(q)
            answer = str(questions.index(q)) + " "
            answer += str(random.randrange(0, 10))

            if not time_up.is_set():
                time.sleep(random.randrange(0, 10))

                print("Answer:", answer)
                connection_socket.send(answer.encode())
            else:
                break
    except socket.error as msg:
        time_up.set()

    time_up.set()
    print("\nQUIZ OVER!")

    # receive score from server
    print("Receiving score...")
    score = connection_socket.recv(4)
    score = struct.unpack("!I", score)[0]

    print("SCORE: ", score)
    print("Disconnected from server.")
    connection_socket.close()
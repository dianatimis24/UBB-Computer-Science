import socket
import struct

SERVER_IP = '192.168.100.110'
CONNECTION_PORT = 1234
TIMER_PORT = 1235


if __name__ == "__main__":
    try:
        connection_socket = socket.create_connection((SERVER_IP, CONNECTION_PORT))
    except socket.error as msg:
        print("Error connecting to server: ", msg.strerror)
        exit(-1)

    print("Connected to server. Waiting for quiz to start...")

    data = connection_socket.recv(1024)
    data = data.decode()

    questions = data.split(';')

    print("\nQUIZ START!")
    for q in questions:
        print(q)
        answer = str(questions.index(q)) + " "
        answer += input("Answer: ")

        connection_socket.send(answer.encode())

    score = connection_socket.recv(4)
    score = struct.unpack("!I", score)[0]

    print("\nQUIZ OVER!")
    print("SCORE: ", score)
    print("Disconnected from server.")
    connection_socket.close()
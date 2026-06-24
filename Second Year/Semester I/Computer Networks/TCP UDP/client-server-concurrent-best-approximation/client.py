import socket, struct, random
from multiprocessing import Process

HOST = 'localhost'
PORT = 1234
NRCLIENTS = 5

processes = []

def client(client_socket):
    # random.uniform(low_bound, up_bound)
    client_random_float = random.random() # float between 0.0 and 1.0
    print("Client " + str(client_socket.getsockname()[1]) + ": " + str(client_random_float))

    answer = "Something went wrong"
    try:
        client_socket.send(struct.pack("!f", client_random_float))

        answer = client_socket.recv(1024)
        answer = answer.decode('ascii')
    except socket.error as message:
        print("Error: ", message.strerror)

    print("Client " + str(client_socket.getsockname()[1]) + ": " + answer)
    client_socket.close()

if __name__ == "__main__":

    for i in range(NRCLIENTS):
        try:
            s = socket.create_connection((HOST, PORT))

            p = Process(target=client, args=(s,))
            processes.append(p)
            p.start()
        except socket.error as message:
            print("Error connecting to server: ", message.strerror)
            exit(-1)

    for p in processes:
        p.join()
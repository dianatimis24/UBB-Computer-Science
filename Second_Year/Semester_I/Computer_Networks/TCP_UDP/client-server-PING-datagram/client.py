import socket, time, random
import string

if __name__ == "__main__":
    ip = ""
    port = ""
    while ip == "":
        ip = input("Server IP: ")
    while port == "":
        port = input("Server Port: ")

    try:
        cs = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    except socket.error as msg:
        print("Error connecting to server: ", msg.strerror)
        exit(-1)

    while True:
        package_length = random.randrange(5, 50)
        package = ''.join(random.choices(string.ascii_letters + string.digits, k=package_length)) # generate random string
        print("\nPackage: ", package)

        time_send = time.time()
        cs.sendto(package.encode('utf-8'), (ip, int(port)))

        received_package, source = cs.recvfrom(1024)
        time_receive = time.time()

        received_package = received_package.decode('utf-8')
        if package == received_package:
            print("Package contents match")
        else:
            print("Package contents DO NOT match!")

        print(f"Round trip time: {time_receive - time_send}")

        time.sleep(2)

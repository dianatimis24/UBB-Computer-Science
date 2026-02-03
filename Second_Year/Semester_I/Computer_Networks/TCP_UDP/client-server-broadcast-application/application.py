import os
import socket
import threading
import time
from datetime import datetime

CLEAR_OS_COMMAND = 'cls'

BROADCAST_IP = '192.168.100.255'
BROADCAST_PORT = 7777

peers = {} # (ip, port): time, date
malformed_data = [] # (ip, port, data)

stop_event = threading.Event()
stop_event.clear()

def broadcast(cs):
    global BROADCAST_IP, BROADCAST_PORT, stop_event

    time_passed = 0
    while not stop_event.is_set():
        if time_passed % 3 == 0:
            cs.sendto(b'TIMEQUERY', (BROADCAST_IP, BROADCAST_PORT))
        if time_passed % 10 == 0:
            cs.sendto(b'DATEQUERY', (BROADCAST_IP, BROADCAST_PORT))

        time.sleep(1)
        time_passed += 1

def update():
    global peers, malformed_data, stop_event, CLEAR_OS_COMMAND

    while not stop_event.is_set():
        os.system(CLEAR_OS_COMMAND)
        for p in peers.keys():
            p_time, p_date = peers[p]
            print(f"{p[0]}:{p[1]}\t\t{p_time}   {p_date}")

        print("Malformed data")
        for m in malformed_data:
            print(f"{m[0]}:{m[1]}\t{m[2]}")

        time.sleep(1)

if __name__ == "__main__":
    try:
        cs = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        cs.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        cs.bind(('0.0.0.0', 7777))
    except socket.error as msg:
        print("Error socket creation: ", msg.strerror)
        exit(-1)

    update_thread = threading.Thread(target=update)
    update_thread.start()

    broadcast_thread = threading.Thread(target=broadcast, args=(cs,))
    broadcast_thread.start()

    try:
        while True:
            data, source = cs.recvfrom(1024) # data = request from broadcast / response
            data = data.decode('utf-8')


            current_date_time = datetime.now()

            if data == "TIMEQUERY":
                response = "TIME "
                response += current_date_time.strftime("%H:%M:%S")
                cs.sendto(response.encode('utf-8'), source)
            elif data == "DATEQUERY":
                response = "DATE "
                response += current_date_time.strftime("%d:%m:%Y")
                cs.sendto(response.encode('utf-8'), source)
            elif data.startswith("TIME "):
                if source not in peers:
                    peers[source] = (None, None)
                old_time, old_date = peers[source]

                peers[source] = (data, old_date)
            elif data.startswith("DATE "):
                if source not in peers:
                    peers[source] = (None, None)
                old_time, old_date = peers[source]

                peers[source] = (old_time, data)
            else:
                # malformed request/response
                malformed_data.append((source[0], source[1], data))

            time.sleep(0.2)
    except KeyboardInterrupt:
        stop_event.set()
        os.system(CLEAR_OS_COMMAND)
        print("\nProgram interrupted by user")

    update_thread.join()
    broadcast_thread.join()

    cs.close()

# TODO remove peer from list if no response was received after 3 consecutive broadcasts
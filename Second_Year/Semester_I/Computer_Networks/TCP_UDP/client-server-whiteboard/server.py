import socket, threading
import time
import turtle


IP = '0.0.0.0'
PORT = 1234
TCP_PORT = 1235
clients = []

update_event = threading.Event()
update_event.clear()
save_event = threading.Event()
save_event.clear()

def set_whiteboard():
    window = turtle.Screen()
    window.title("Whiteboard")

def handle_client(client_command, client_source):
    global clients, update_event, save_event

    if client_source not in clients:
        print("New client from: ", client_source)
        clients.append(client_source)

    print("Command: ", client_command)
    draw(client_command)
    update_event.set()
    # save_event.set()

def draw(command):
    args = command.split()
    shape = args[0]

    if shape == "line":
        draw_line(float(args[1]), float(args[2]), float(args[3]), float(args[4]))
    elif shape == "circle":
        draw_circle(float(args[1]), float(args[2]), float(args[3]))

def draw_line(start_x, start_y, end_x, end_y):
    draw_turtle = turtle.Turtle(visible=False)

    print("Draw line...")
    draw_turtle.penup()
    draw_turtle.goto(start_x, start_y)
    draw_turtle.pendown()
    draw_turtle.showturtle()

    draw_turtle.goto(end_x, end_y)
    draw_turtle.hideturtle()

def draw_circle(center_x, center_y, radius):
    draw_turtle = turtle.Turtle(visible=False)

    print("Draw circle...")
    draw_turtle.penup()
    draw_turtle.goto(center_x, center_y - radius)
    draw_turtle.pendown()
    draw_turtle.showturtle()

    draw_turtle.circle(radius)
    draw_turtle.hideturtle()

def update(s):
    global clients, update_event

    while True:
        update_event.wait()
        print("Update...")

        for c in clients:
            cs = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            cs.connect((c[0], TCP_PORT))

            cs.sendall(bytes("Draw update", 'ascii'))
            cs.close()
            time.sleep(1)
            # s.sendto(bytes("Drawing update", 'ascii'), c)
        update_event.clear()
        time.sleep(0.5)

# def check_save():
#     while True:
#         save_event.wait()
#         save_image()
#         update_event.set()
#         save_event.clear()
#         time.sleep(0.25)
#
# def save_image():
#     turtle.Screen().getcanvas().postscript(file='whiteboard.ps')
#
# check_save()

if __name__ == "__main__":
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP socket
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) # reuse the port (sometimes port gets blocked)
    s.bind((IP, PORT))

    set_whiteboard()

    update_thread = threading.Thread(target=update, daemon=True, args=(s,))
    update_thread.start()

    while True:
        print("Waiting for clients...")

        client_command, client_source = s.recvfrom(1024) # client_source = [client_IP, client_PORT]
        client_command = client_command.decode('ascii')

        # command_thread = threading.Thread(target=handle_client, args=(client_command, client_source,))
        # command_thread.start()
        handle_client(client_command, client_source)
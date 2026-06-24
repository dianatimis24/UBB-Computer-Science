import socket
import threading


SERVER_IP = '0.0.0.0'
SERVER_PORT = 1234

threads = []
parts_lock = threading.Lock()
order_lock = threading.Lock()

# number: {"name", "price", "quantity", "description"
parts = {
    "A1234": {
        "name": "Brake Pad Set",
        "price": 59.99,
        "quantity": 25,
        "description": "High-performance ceramic brake pads for front wheels."
    },
    "B5678": {
        "name": "Oil Filter",
        "price": 12.49,
        "quantity": 100,
        "description": "Standard oil filter compatible with most sedans and SUVs."
    },
    "C9012": {
        "name": "Spark Plug",
        "price": 6.75,
        "quantity": 200,
        "description": "Copper core spark plug for improved ignition performance."
    },
    "D3456": {
        "name": "Air Filter",
        "price": 18.99,
        "quantity": 75,
        "description": "Engine air filter with high dust-holding capacity."
    },
    "E7890": {
        "name": "Headlight Bulb",
        "price": 24.95,
        "quantity": 60,
        "description": "Halogen headlight bulb with long-lasting illumination."
    }
}

order_id = 0

def manage_command(server_socket, source, data):
    data = data.split()
    command = data[0]

    message = "Unknown command"
    if command == "exit":
        message = f"Client {source} disconnected."
        print(message)
    elif len(data) > 1:
        part_number = data[1]

        if command == "search":
            if search(part_number):
                if in_stock(part_number):
                    message = f"Part {part_number} is in stock."
                else:
                    message = f"Part {part_number} is not in stock."
            else:
                message = f"Part {part_number} was not found in inventory."

        elif command == "get":
            message = get(part_number)

        elif command == "order":
            quantity = int(data[2])
            message = order(part_number, quantity)

    server_socket.sendto(message.encode(), source)


def search(part_number):
    global parts

    return (part_number in parts.keys())

def in_stock(part_number):
    global parts, parts_lock

    if search(part_number):
        parts_lock.acquire()
        status = parts[part_number]["quantity"] > 0
        parts_lock.release()

        return status
    else:
        return False

def get(part_number):
    global parts, parts_lock

    response = f"Part {part_number} was not found in inventory."
    if search(part_number):
        parts_lock.acquire()
        response = f"Name: {parts[part_number]["name"]}\nPrice: {parts[part_number]["price"]}\nQuantity: {parts[part_number]["quantity"]}\nDescription: {parts[part_number]["description"]}"
        parts_lock.release()

    return response

def order(part_number, quantity):
    global parts, order_id, parts_lock, order_lock

    order_lock.acquire()
    current_order_id = order_id
    order_id += 1
    order_lock.release()

    response = f"FAIL -- Order {current_order_id}: {part_number}, {quantity} pieces. Part was not found in inventory"
    if search(part_number):
        parts_lock.acquire()
        parts[part_number]["quantity"] -= quantity

        if parts[part_number]["quantity"] >= 0:
            response = f"SUCCESS - Order {order_id}: {part_number}, {quantity} pieces."
        else:
            left_quantity = quantity - abs(parts[part_number]["quantity"])
            parts[part_number]["quantity"] = 0
            response = f"SUCCESS -- Order {current_order_id}: {part_number}, {left_quantity} pieces. No more pieces in stock!"

        parts_lock.release()

    return response

if __name__ == "__main__":
    try:
        server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        server_socket.bind((SERVER_IP, SERVER_PORT))
    except socket.error as msg:
        print("Error creating server: ", msg.strerror)
        exit(-1)

    while True:
        print("Waiting for commands ...")
        data, source = server_socket.recvfrom(1024)
        print(f"New command from {source}")

        command_thread = threading.Thread(target=manage_command, args=(server_socket, source, data.decode(),), daemon=True)
        threads.append(command_thread)
        command_thread.start()
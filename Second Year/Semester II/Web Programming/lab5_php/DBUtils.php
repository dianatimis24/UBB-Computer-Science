<?php
header("Access-Control-Allow-Origin: http://localhost:4200");
header("Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS");
header("Access-Control-Allow-Headers: Content-Type");
header("Access-Control-Allow-Credentials: true");

if ($_SERVER['REQUEST_METHOD'] === 'OPTIONS') {
    http_response_code(200);
    exit;
}

session_start();

class DBConnection
{
    private $host = "localhost";
    private $user = "root";
    private $pass = "";
    private $db = "room_booking";
    private $charset = "utf8";
    private $pdo;

    public function __construct()
    {
        $dsn = "mysql:host={$this->host};dbname={$this->db};charset={$this->charset}";
        $opt = [
            PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION,
            PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
            PDO::ATTR_EMULATE_PREPARES => false,
        ];
        try {
            $this->pdo = new PDO($dsn, $this->user, $this->pass, $opt);
        } catch (PDOException $e) {
            http_response_code(500);
            echo json_encode(["error" => "Database connection failed."]);
            exit;
        }
    }

    public function getAllHotels(): array
    {
        $statement = $this->pdo->prepare("SELECT * FROM hotels ORDER BY id");
        $statement->execute();
        return $statement->fetchAll();
    }

    public function getHotelByName(string $name): array
    {
        $statement = $this->pdo->prepare("SELECT * FROM hotels WHERE name LIKE ?");
        $statement->execute(["%$name%"]);
        return $statement->fetchAll();
    }

    public function getHotelByAddress(string $address): array
    {
        $statement = $this->pdo->prepare("SELECT * FROM hotels WHERE address LIKE ?");
        $statement->execute(["%$address%"]);
        return $statement->fetchAll();
    }

    public function insertHotel(string $name, string $address): bool
    {
        $statement = $this->pdo->prepare("INSERT INTO hotels (name, address) VALUES (?, ?)");
        return $statement->execute([$name, $address]);
    }

    public function updateHotel(int $id, string $name, string $address): bool
    {
        $statement = $this->pdo->prepare("UPDATE hotels SET name = ?, address = ? WHERE id = ?");
        return $statement->execute([$name, $address, $id]);
    }

    public function deleteHotel(int $id): bool
    {
        $statement = $this->pdo->prepare("DELETE FROM hotels WHERE id = ?");
        return $statement->execute([$id]);
    }

    public function getAllRooms(): array
    {
        $statement = $this->pdo->prepare(
            "SELECT rooms.id, hotels.name AS hotel_name,
                    rooms.room_number, rooms.category, rooms.type, rooms.price
             FROM rooms
             INNER JOIN hotels ON rooms.hotel_id = hotels.id
             ORDER BY hotels.name, rooms.room_number"
        );
        $statement->execute();
        return $statement->fetchAll();
    }

    public function getRoomByCategory(string $category): array
    {
        $statement = $this->pdo->prepare(
            "SELECT rooms.id, hotels.name AS hotel_name,
                    rooms.room_number, rooms.category, rooms.type, rooms.price
             FROM rooms
             INNER JOIN hotels ON rooms.hotel_id = hotels.id
             WHERE rooms.category LIKE ?
             ORDER BY hotels.name"
        );
        $statement->execute(["%$category%"]);
        return $statement->fetchAll();
    }

    public function getRoomByType(string $type): array
    {
        $statement = $this->pdo->prepare(
            "SELECT rooms.id, hotels.name AS hotel_name,
                    rooms.room_number, rooms.category, rooms.type, rooms.price
             FROM rooms
             INNER JOIN hotels ON rooms.hotel_id = hotels.id
             WHERE rooms.type LIKE ?
             ORDER BY hotels.name"
        );
        $statement->execute(["%$type%"]);
        return $statement->fetchAll();
    }

    public function getRoomByPrice(float $price): array
    {
        $statement = $this->pdo->prepare(
            "SELECT rooms.id, hotels.name AS hotel_name,
                    rooms.room_number, rooms.category, rooms.type, rooms.price
             FROM rooms
             INNER JOIN hotels ON rooms.hotel_id = hotels.id
             WHERE rooms.price < ?
             ORDER BY rooms.price"
        );
        $statement->execute([$price]);
        return $statement->fetchAll();
    }

    public function getRoomByHotel(string $hotel_name): array
    {
        $statement = $this->pdo->prepare(
            "SELECT rooms.id, hotels.name AS hotel_name,
                    rooms.room_number, rooms.category, rooms.type, rooms.price
             FROM rooms
             INNER JOIN hotels ON rooms.hotel_id = hotels.id
             WHERE hotels.name LIKE ?
             ORDER BY rooms.room_number"
        );
        $statement->execute(["%$hotel_name%"]);
        return $statement->fetchAll();
    }

    public function insertRoom(int $hotel_id, string $room_number, string $category, string $type, float $price): bool
    {
        $statement = $this->pdo->prepare(
            "INSERT INTO rooms (hotel_id, room_number, category, type, price) VALUES (?, ?, ?, ?, ?)"
        );
        return $statement->execute([$hotel_id, $room_number, $category, $type, $price]);
    }

    public function updateRoom(int $id, string $room_number, string $category, string $type, float $price): bool
    {
        $statement = $this->pdo->prepare(
            "UPDATE rooms SET room_number = ?, category = ?, type = ?, price = ? WHERE id = ?"
        );
        return $statement->execute([$room_number, $category, $type, $price, $id]);
    }

    public function deleteRoom(int $id): bool
    {
        $statement = $this->pdo->prepare("DELETE FROM rooms WHERE id = ?");
        return $statement->execute([$id]);
    }

    public function getReservationsByUsername(string $user_name): array
    {
        $statement = $this->pdo->prepare(
            "SELECT reservations.id, rooms.room_number, hotels.name AS hotel_name,
                    reservations.start_date, reservations.end_date
             FROM reservations
             JOIN rooms ON reservations.room_id = rooms.id
             JOIN hotels ON rooms.hotel_id = hotels.id
             WHERE reservations.user_name = ?
             ORDER BY reservations.start_date DESC"
        );
        $statement->execute([$user_name]);
        return $statement->fetchAll();
    }

    public function isRoomAvailable(int $room_id, string $start_date, string $end_date): bool
    {
        $statement = $this->pdo->prepare(
            "SELECT COUNT(*) FROM reservations
             WHERE room_id = ?
             AND start_date < ?
             AND end_date > ?"
        );
        $statement->execute([$room_id, $end_date, $start_date]);
        return (int)$statement->fetchColumn() === 0;
    }

    public function insertReservation(int $room_id, string $user_name, string $start_date, string $end_date): bool
    {
        $statement = $this->pdo->prepare(
            "INSERT INTO reservations (room_id, user_name, start_date, end_date) VALUES (?, ?, ?, ?)"
        );
        return $statement->execute([$room_id, $user_name, $start_date, $end_date]);
    }

    public function editReservation(int $id, string $start_date, string $end_date): bool
    {
        $statement = $this->pdo->prepare(
            "UPDATE reservations SET start_date = ?, end_date = ? WHERE id = ?"
        );
        return $statement->execute([$start_date, $end_date, $id]);
    }

    public function deleteReservation(int $id): bool
    {
        $statement = $this->pdo->prepare("DELETE FROM reservations WHERE id = ?");
        return $statement->execute([$id]);
    }

    public function selectUserByUsername(string $username): array
    {
        $statement = $this->pdo->prepare("SELECT * FROM users WHERE username = ?");
        $statement->execute([$username]);
        return $statement->fetchAll();
    }

    private function show(mixed $value, int $status = 200): void
    {
        if (ob_get_length()) ob_clean();
        http_response_code($status);
        header("Content-Type: application/json; charset=utf-8");
        echo json_encode($value);
        exit;
    }

    public function run(): void
    {
        $method = $_SERVER['REQUEST_METHOD'];
        $path = trim(parse_url($_SERVER['REQUEST_URI'], PHP_URL_PATH), '/');
        $body = json_decode(file_get_contents('php://input'), true) ?? [];

        $path = preg_replace('#^[^/]+/api/#', 'api/', $path);
        $segments = explode('/', $path);

        $resource = $segments[1] ?? '';
        $id = isset($segments[2]) ? (int)$segments[2] : null;

        match ($resource) {
            'authentication' => $this->handleAuth($method, $segments, $body),
            'hotels' => $this->handleHotels($method, $id, $body),
            'rooms' => $this->handleRooms($method, $id, $body),
            'reservations' => $this->handleReservations($method, $id, $body),
            default => $this->show(["error" => "Not found."], 404)
        };
    }

    private function handleAuth(string $method, array $segments, array $body): void
    {
        $action = $segments[2] ?? '';

        if ($method === 'POST' && $action === 'login') {
            $username = trim($body['username'] ?? '');
            $password = trim($body['password'] ?? '');
            if ($username === '' || $password === '') {
                $this->show(["error" => "Username and password are required."], 400);
            }
            $result = $this->selectUserByUsername($username);
            if (count($result) === 0 || $result[0]['password'] !== $password) {
                $this->show(["error" => "Invalid username or password."], 401);
            }
            $_SESSION['username'] = $result[0]['username'];
            $this->show(["username" => $result[0]['username']]);
        }

        if ($method === 'POST' && $action === 'logout') {
            $_SESSION = [];
            if (ini_get("session.use_cookies")) {
                $params = session_get_cookie_params();
                setcookie(
                    session_name(),
                    '',
                    time() - 42000,
                    $params["path"],
                    $params["domain"],
                    $params["secure"],
                    $params["httponly"]
                );
            }
            session_destroy();
            $this->show(["message" => "Logged out."]);
        }

        if ($method === 'GET' && $action === 'me') {
            $username = $_SESSION['username'] ?? null;
            if ($username === null) {
                $this->show(["error" => "Not logged in."], 401);
            }
            $this->show(["username" => $username]);
        }

        $this->show(["error" => "Not found."], 404);
    }

    private function handleHotels(string $method, ?int $id, array $body): void
    {
        $username = $_SESSION['username'] ?? null;
        if ($username === null) {
            $this->show(["error" => "Not logged in."], 401);
        }

        if ($method === 'GET' && $id === null) {
            $name = trim($_GET['name'] ?? '');
            $address = trim($_GET['address'] ?? '');
            if ($name !== '') $this->show($this->getHotelByName($name));
            if ($address !== '') $this->show($this->getHotelByAddress($address));
            $this->show($this->getAllHotels());
        }

        if ($method === 'POST') {
            $name = trim($body['name'] ?? '');
            $address = trim($body['address'] ?? '');
            if ($name === '' || $address === '') {
                $this->show(["error" => "Name and address are required."], 422);
            }
            if ($this->insertHotel($name, $address)) {
                $this->show(["message" => "Hotel added."], 201);
            }
            $this->show(["error" => "Could not insert hotel."], 500);
        }

        if ($method === 'PUT' && $id !== null) {
            $name = trim($body['name'] ?? '');
            $address = trim($body['address'] ?? '');
            if ($name === '' || $address === '') {
                $this->show(["error" => "Name and address are required."], 422);
            }
            if ($this->updateHotel($id, $name, $address)) {
                $this->show(["message" => "Hotel updated."]);
            }
            $this->show(["error" => "Could not update hotel."], 500);
        }

        if ($method === 'DELETE' && $id !== null) {
            if ($this->deleteHotel($id)) {
                $this->show(["message" => "Hotel deleted."]);
            }
            $this->show(["error" => "Could not delete hotel."], 500);
        }

        $this->show(["error" => "Not found."], 404);
    }

    private function handleRooms(string $method, ?int $id, array $body): void
    {
        if ($method === 'GET' && $id === null) {
            $category = trim($_GET['category'] ?? '');
            $type = trim($_GET['type'] ?? '');
            $maxPrice = (float)($_GET['maxPrice'] ?? 0);
            $hotelName = trim($_GET['hotelName'] ?? '');
            if ($category !== '') $this->show($this->getRoomByCategory($category));
            if ($type !== '') $this->show($this->getRoomByType($type));
            if ($maxPrice > 0) $this->show($this->getRoomByPrice($maxPrice));
            if ($hotelName !== '') $this->show($this->getRoomByHotel($hotelName));
            $this->show($this->getAllRooms());
        }

        $username = $_SESSION['username'] ?? null;
        if ($username === null) {
            $this->show(["error" => "Not logged in."], 401);
        }

        if ($method === 'POST') {
            $hotel_id = (int)($body['hotelId'] ?? 0);
            $room_number = trim($body['roomNumber'] ?? '');
            $category = trim($body['category'] ?? '');
            $type = trim($body['type'] ?? '');
            $price = (float)($body['price'] ?? 0);
            if ($hotel_id <= 0 || $room_number === '' || $category === '' || $type === '' || $price <= 0) {
                $this->show(["error" => "Invalid room data."], 422);
            }
            if ($this->insertRoom($hotel_id, $room_number, $category, $type, $price)) {
                $this->show(["message" => "Room added."], 201);
            }
            $this->show(["error" => "Could not insert room."], 500);
        }

        if ($method === 'PUT' && $id !== null) {
            $room_number = trim($body['roomNumber'] ?? '');
            $category = trim($body['category'] ?? '');
            $type = trim($body['type'] ?? '');
            $price = (float)($body['price'] ?? 0);
            if ($room_number === '' || $category === '' || $type === '' || $price <= 0) {
                $this->show(["error" => "Invalid room data."], 422);
            }
            if ($this->updateRoom($id, $room_number, $category, $type, $price)) {
                $this->show(["message" => "Room updated."]);
            }
            $this->show(["error" => "Could not update room."], 500);
        }

        if ($method === 'DELETE' && $id !== null) {
            if ($this->deleteRoom($id)) {
                $this->show(["message" => "Room deleted."]);
            }
            $this->show(["error" => "Could not delete room."], 500);
        }

        $this->show(["error" => "Not found."], 404);
    }

    private function handleReservations(string $method, ?int $id, array $body): void
    {
        $username = $_SESSION['username'] ?? null;
        if ($username === null) {
            $this->show(["error" => "Not logged in."], 401);
        }

        if ($method === 'GET') {
            $this->show($this->getReservationsByUsername($username));
        }

        if ($method === 'POST') {
            $room_id = (int)($body['roomId'] ?? 0);
            $start_date = trim($body['startDate'] ?? '');
            $end_date = trim($body['endDate'] ?? '');
            if ($room_id <= 0 || $start_date === '' || $end_date === '') {
                $this->show(["error" => "Invalid reservation data."], 422);
            }
            if ($start_date >= $end_date) {
                $this->show(["error" => "Start date must be before end date."], 422);
            }
            if (!$this->isRoomAvailable($room_id, $start_date, $end_date)) {
                $this->show(["error" => "Room is not available for those dates."], 409);
            }
            if ($this->insertReservation($room_id, $username, $start_date, $end_date)) {
                $this->show(["message" => "Reservation created."], 201);
            }
            $this->show(["error" => "Could not create reservation."], 500);
        }

        if ($method === 'PUT' && $id !== null) {
            $start_date = trim($body['startDate'] ?? '');
            $end_date = trim($body['endDate'] ?? '');
            if ($start_date === '' || $end_date === '') {
                $this->show(["error" => "Invalid dates."], 422);
            }
            if ($start_date >= $end_date) {
                $this->show(["error" => "Start date must be before end date."], 422);
            }
            if ($this->editReservation($id, $start_date, $end_date)) {
                $this->show(["message" => "Reservation updated."]);
            }
            $this->show(["error" => "Could not update reservation."], 500);
        }

        if ($method === 'DELETE' && $id !== null) {
            if ($this->deleteReservation($id)) {
                $this->show(["message" => "Reservation deleted."]);
            }
            $this->show(["error" => "Could not delete reservation."], 500);
        }

        $this->show(["error" => "Not found."], 404);
    }
}

$conn = new DBConnection();
if (strpos($_SERVER['REQUEST_URI'], '/api/') !== false) {
    $conn->run();
}
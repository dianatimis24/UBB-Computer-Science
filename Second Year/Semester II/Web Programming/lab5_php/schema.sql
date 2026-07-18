CREATE TABLE IF NOT EXISTS users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(80) NOT NULL UNIQUE,
    password VARCHAR(255) NOT NULL
);

CREATE TABLE IF NOT EXISTS hotels (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    address VARCHAR(200) NOT NULL
);

CREATE TABLE IF NOT EXISTS rooms (
    id INT AUTO_INCREMENT PRIMARY KEY,
    hotel_id INT  NOT NULL,
    room_number VARCHAR(10) NOT NULL,
    category VARCHAR(50) NOT NULL,
    type VARCHAR(50) NOT NULL,
    price DECIMAL(10,2) NOT NULL,
    FOREIGN KEY (hotel_id) REFERENCES hotels(id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS reservations (
    id INT AUTO_INCREMENT PRIMARY KEY,
    room_id INT NOT NULL,
    user_name VARCHAR(80) NOT NULL,
    start_date DATE NOT NULL,
    end_date DATE NOT NULL,
    FOREIGN KEY (room_id) REFERENCES rooms(id) ON DELETE CASCADE
);

INSERT INTO users (username, password) VALUES ('admin', 'admin123');

INSERT INTO hotels (name, address) VALUES
    ('Grand Hotel', '10 Main Street'),
    ('Sea View', '5 Ocean Boulevard'),
    ('Mountain Inn', '22 Alpine Road');

INSERT INTO rooms (hotel_id, room_number, category, type, price) VALUES
    (1, '101', 'standard', 'single', 80.00),
    (1, '102', 'deluxe', 'double', 120.00),
    (2, '201', 'suite', 'double', 200.00),
    (2, '202', 'standard', 'twin', 130.00),
    (3, '301', 'standard', 'single', 75.00),
    (3, '302', 'deluxe', 'twin', 110.00);
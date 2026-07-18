const express = require('express');
const session = require('express-session');
const cors = require('cors');

const authenticationRoutes = require('./routes/authentication');
const hotelRoutes = require('./routes/hotels');
const roomRoutes = require('./routes/rooms');
const reservationRoutes = require('./routes/reservations');

const app = express();

app.use(cors({
    origin: 'http://localhost:4200',
    credentials: true
}));

app.use(express.json());

app.use(session({
    secret: 'hotel_booking_secret',
    resave: false,
    saveUninitialized: false,
    cookie: {
        httpOnly: true,
        maxAge: 2 * 60 * 60 * 1000
    }
}));

app.use('/api/authentication', authenticationRoutes);
app.use('/api/hotels', hotelRoutes);
app.use('/api/rooms', roomRoutes);
app.use('/api/reservations', reservationRoutes);

app.use((error, request, response, next) => {
    console.error(error.stack);
    response.status(500).json({ error: 'Internal server error.' });
});

module.exports = app; 

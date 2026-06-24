use MyArtMuseum

CREATE TABLE ArtStyles
(
asID smallint primary key identity(1, 1),
[name] varchar(100),
[period] varchar(200),
[description] varchar(1000)
)

CREATE TABLE Artists
(
aID smallint primary key identity(1, 1),
[name] varchar(300) unique,
birthDate date,
deathDate date,
originCountry varchar(100),
asID smallint,
foreign key(asID) references ArtStyles(asID)
ON DELETE CASCADE
)

CREATE TABLE ArtworkTypes
(
atID smallint primary key identity(1, 1),
[name] varchar(200),
[description] varchar(1000)
)

CREATE TABLE Collections
(
cID smallint primary key,
[name] varchar(200),
[entryDate] date,
[source] varchar(100),
[description] varchar(1000)
)

CREATE TABLE Artworks
(
artID smallint primary key identity(1, 1),
title varchar(300),
creationYear int,
techinque varchar(200),
aID smallint,
atID smallint,
cID smallint,
foreign key(aID) references Artists(aID) ON DELETE CASCADE,
foreign key(atID) references ArtworkTypes(atID) ON DELETE CASCADE,
foreign key(cID) references Collections(cID) ON DELETE CASCADE
)

CREATE TABLE Employees
(
eID smallint primary key identity(1, 1),
[name] varchar(300),
[role] varchar(300),
email varchar(200) unique,
phone varchar(20) unique,
hireDate date,
salary decimal(10, 2)
)

CREATE TABLE Exhibitions
(
eID smallint primary key identity(1, 1),
[name] varchar(300),
startDate date,
endDate date,
curatorID smallint,
[description] varchar(1000),
foreign key(curatorID) references Employees(eID) ON DELETE CASCADE
)

CREATE TABLE ArtworkExhibitions
(
artID smallint,
eID smallint,
primary key (artID, eID),
foreign key(artID) references Artworks(artID) ON DELETE CASCADE,
foreign key(eID) references Exhibitions(eID) ON DELETE CASCADE
)

CREATE TABLE Visitors
(
vID smallint primary key identity(1, 1),
[name] varchar(200),
visitorType varchar(100),
originCountry varchar(100),
generalFeedback varchar(1000)
)

CREATE TABLE Tickets
(
tID smallint primary key identity(1, 1),
ticketType varchar(100),
price decimal(10, 2),
validity bit,
accessToEvents bit
)

CREATE TABLE Visits
(
vID smallint primary key identity(1, 1),
visitorID smallint,
ticketID smallint,
visitDate date,
duration int,
guided bit,
foreign key(visitorID) references Visitors(vID) ON DELETE CASCADE,
foreign key(ticketID) references Tickets(tID) ON DELETE CASCADE
)

ALTER TABLE Visits
ADD CONSTRAINT UQ_ticket UNIQUE(ticketID)

CREATE TABLE CulturalEvents
(
eID smallint primary key identity(1, 1),
[name] varchar(400),
eventDate date,
[time] time,
duration int,
organizerID smallint,
maximumCapacity int,
[description] varchar(1000),
foreign key(organizerID) references Employees(eID) ON DELETE CASCADE
)

CREATE TABLE EventParticipations
(
visitorID smallint,
eventID smallint,
primary key (visitorID, eventID),
foreign key(visitorID) references Visitors(vID) ON DELETE CASCADE,
foreign key(eventID) references CulturalEvents(eID) ON DELETE CASCADE
)

ALTER TABLE Exhibitions
ADD CONSTRAINT UQ_curator UNIQUE(curatorID)

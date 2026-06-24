use MyArtMuseum

-- drop tables in reverse dependency order to avoid FK constraint errors

if object_id('EventParticipations', 'U') is not null drop table EventParticipations
if object_id('CulturalEvents', 'U') is not null drop table CulturalEvents
if object_id('Visits', 'U') is not null drop table Visits
if object_id('Tickets', 'U') is not null drop table Tickets
if object_id('Visitors', 'U') is not null drop table Visitors
if object_id('ArtworkExhibitions', 'U') is not null drop table ArtworkExhibitions
if object_id('Exhibitions', 'U') is not null drop table Exhibitions
if object_id('Artworks', 'U') is not null drop table Artworks
if object_id('Employees', 'U') is not null drop table Employees
if object_id('Collections', 'U') is not null drop table Collections
if object_id('Artists', 'U') is not null drop table Artists
if object_id('ArtworkTypes', 'U') is not null drop table ArtworkTypes
if object_id('ArtStyles', 'U') is not null drop table ArtStyles
if object_id('LogTable', 'U') is not null drop table LogTable

-- recreate tables

create table ArtStyles (
	asID smallint primary key identity(1,1),
	[name] varchar(100),
	[period] varchar(200),
	[description] varchar(1000)
)

create table Artists (
	aID smallint primary key identity(1,1),
	[name] varchar(300) unique,
	birthDate date,
	deathDate date,
	originCountry varchar(100),
	asID smallint,
	foreign key (asID) references ArtStyles(asID) on delete cascade
)

create table ArtworkTypes (
	atID smallint primary key identity(1,1),
	[name] varchar(200),
	[description] varchar(1000)
)

create table Collections (
	cID smallint primary key,
	[name] varchar(200),
	entryDate date,
	[source] varchar(100),
	[description] varchar(1000)
)

create table Artworks (
	artID smallint primary key identity(1,1),
	title varchar(300),
	creationYear int,
	techinque varchar(200),
	aID smallint,
	atID smallint,
	cID smallint,
	foreign key (aID) references Artists(aID) on delete cascade,
	foreign key (atID) references ArtworkTypes(atID) on delete cascade,
	foreign key (cID) references Collections(cID) on delete cascade
)

create table Employees (
	eID smallint primary key identity(1,1),
	[name] varchar(300),
	[role] varchar(300),
	email varchar(200) unique,
	phone varchar(20) unique,
	hireDate date,
	salary decimal(10,2)
)

create table Exhibitions (
	eID smallint primary key identity(1,1),
	[name] varchar(300),
	startDate date,
	endDate date,
	curatorID smallint,
	[description] varchar(1000),
	foreign key (curatorID) references Employees(eID) on delete cascade
)

alter table Exhibitions
add constraint UQ_curator unique(curatorID)

create table ArtworkExhibitions (
	artID smallint,
	eID smallint,
	primary key (artID, eID),
	foreign key (artID) references Artworks(artID) on delete cascade,
	foreign key (eID) references Exhibitions(eID) on delete cascade
)

create table Visitors (
	vID smallint primary key identity(1,1),
	[name] varchar(200),
	visitorType varchar(100),
	originCountry varchar(100),
	generalFeedback varchar(1000)
)

create table Tickets (
	tID smallint primary key identity(1,1),
	ticketType varchar(100),
	price decimal(10,2),
	validity bit,
	accessToEvents bit
)

create table Visits (
	vID smallint primary key identity(1,1),
	visitorID smallint,
	ticketID smallint,
	visitDate date,
	duration int,
	guided bit,
	foreign key (visitorID) references Visitors(vID) on delete cascade,
	foreign key (ticketID) references Tickets(tID) on delete cascade
)

alter table Visits
add constraint UQ_ticket unique(ticketID)

create table CulturalEvents (
	eID smallint primary key identity(1,1),
	[name] varchar(400),
	eventDate date,
	[time] time,
	duration int,
	organizerID smallint,
	maximumCapacity int,
	[description] varchar(1000),
	foreign key (organizerID) references Employees(eID) on delete cascade
)

create table EventParticipations (
	visitorID smallint,
	eventID smallint,
	primary key (visitorID, eventID),
	foreign key (visitorID) references Visitors(vID) on delete cascade,
	foreign key (eventID) references CulturalEvents(eID) on delete cascade
)

create table LogTable (
	Lid int identity primary key,
	TypeOperation varchar(50),
	TableOperation varchar(100),
	Details varchar(500),
	ExecutionDate datetime default getdate()
)


use MyArtMuseum

-- ArtStyles (identity starts at 1)
insert into ArtStyles ([name], [period], [description]) values
('Renaissance', '14th-17th Century', 'Characterized by classical influence and humanism.'),
('Baroque', '17th-18th Century', 'Dramatic, bold, and emotional art style.'),
('Impressionism', '19th Century', 'Focus on light and color rather than detail.'),
('Cubism', 'Early 20th Century', 'Abstract art with geometric shapes.'),
('Surrealism', '1920s-1950s', 'Dreamlike, illogical compositions.'),
('Modernism', 'Late 19th-20th Century', 'Experimentation with form and abstraction.'),
('Expressionism', 'Early 20th Century', 'Emotion conveyed through distorted forms.'),
('Abstract', '20th Century', 'Non-representational art focused on color and shape.'),
('Pop Art', '1950s-1970s', 'Inspired by mass culture and advertising.'),
('Minimalism', '1960s-1970s', 'Art reduced to simplest forms and colors.')

-- ArtworkTypes (identity starts at 1)
insert into ArtworkTypes ([name], [description]) values
('Painting', 'Artwork created using pigments on a surface.'),
('Sculpture', 'Three-dimensional artwork formed by shaping materials.'),
('Drawing', 'Artwork created using lines, often on paper.'),
('Mosaic', 'Art created using small pieces of colored glass or stone.'),
('Fresco', 'Painting done rapidly in watercolor on wet plaster.'),
('Print', 'Artwork produced by printing techniques.'),
('Installation', 'Large-scale, mixed-media construction.'),
('Photograph', 'Artistic image created with a camera.'),
('Digital Art', 'Artwork created using digital tools.'),
('Ceramic', 'Art made of clay and hardened by heat.')

-- Collections (manual primary key)
insert into Collections (cID, [name], entryDate, [source], [description]) values
(1, 'Renaissance Masters', '2001-05-20', 'Donation', 'Works from Italian Renaissance.'),
(2, 'Baroque Wonders', '2003-11-10', 'Purchase', 'Major Baroque artworks.'),
(3, 'Impressionist Dreams', '2005-06-15', 'Donation', 'Impressionist paintings.'),
(4, 'Cubist Geometry', '2010-04-18', 'Purchase', 'Cubist works.'),
(5, 'Surrealist Vision', '2012-09-23', 'Donation', 'Surrealist art collection.'),
(6, 'Modern Abstraction', '2015-03-30', 'Purchase', 'Modern and abstract art.'),
(7, 'Expressionist Soul', '2017-07-21', 'Donation', 'Expressionist pieces.'),
(8, 'Pop Art Explosion', '2018-02-10', 'Purchase', 'Famous Pop Art works.'),
(9, 'Minimalist Designs', '2019-05-14', 'Donation', 'Minimalist artworks.'),
(10, 'Contemporary Mix', '2020-01-01', 'Purchase', 'Mixed modern art pieces.')

-- Artists (identity starts at 1; asID values reference ArtStyles identity above)
insert into Artists ([name], birthDate, deathDate, originCountry, asID) values
('Leonardo da Vinci', '1452-04-15', '1519-05-02', 'Italy', 1),
('Michelangelo', '1475-03-06', '1564-02-18', 'Italy', 1),
('Caravaggio', '1571-09-29', '1610-07-18', 'Italy', 2),
('Claude Monet', '1840-11-14', '1926-12-05', 'France', 3),
('Pablo Picasso', '1881-10-25', '1973-04-08', 'Spain', 4),
('Salvador Dali', '1904-05-11', '1989-01-23', 'Spain', 5),
('Jackson Pollock', '1912-01-28', '1956-08-11', 'USA', 8),
('Andy Warhol', '1928-08-06', '1987-02-22', 'USA', 9),
('Mark Rothko', '1903-09-25', '1970-02-25', 'Latvia', 10),
('Edvard Munch', '1863-12-12', '1944-01-23', 'Norway', 7)

-- Employees (identity starts at 1)
insert into Employees ([name], [role], email, phone, hireDate, salary) values
('Alice Johnson', 'Curator', 'alice.j@mymuseum.org', '111-111-1111', '2010-02-10', 55000),
('Bob Smith', 'Art Restorer', 'bob.s@mymuseum.org', '222-222-2222', '2012-03-15', 48000),
('Clara Evans', 'Guide', 'clara.e@mymuseum.org', '333-333-3333', '2015-07-21', 40000),
('David Kim', 'Security Chief', 'david.k@mymuseum.org', '444-444-4444', '2016-09-01', 42000),
('Ella Brown', 'Archivist', 'ella.b@mymuseum.org', '555-555-5555', '2017-11-12', 46000),
('Frank Wilson', 'Curator', 'frank.w@mymuseum.org', '666-666-6666', '2018-04-25', 56000),
('Grace Lee', 'Administrator', 'grace.l@mymuseum.org', '777-777-7777', '2019-02-14', 50000),
('Henry Davis', 'Event Manager', 'henry.d@mymuseum.org', '888-888-8888', '2020-01-10', 53000),
('Ivy Chen', 'Guide', 'ivy.c@mymuseum.org', '999-999-9999', '2021-05-05', 41000),
('Jack Turner', 'Curator', 'jack.t@mymuseum.org', '101-010-1010', '2022-06-30', 57000)

-- Artworks (identity starts at 1; aID, atID, cID reference identities above)
insert into Artworks (title, creationYear, techinque, aID, atID, cID) values
('Mona Lisa', 1503, 'Oil on wood', 1, 1, 1),
('The Creation of Adam', 1512, 'Fresco', 2, 5, 1),
('The Calling of Saint Matthew', 1600, 'Oil on canvas', 3, 1, 2),
('Water Lilies', 1916, 'Oil on canvas', 4, 1, 3),
('Les Demoiselles d Avignon', 1907, 'Oil on canvas', 5, 1, 4),
('The Persistence of Memory', 1931, 'Oil on canvas', 6, 1, 5),
('No. 5, 1948', 1948, 'Drip painting', 7, 1, 6),
('Campbell Soup Cans', 1962, 'Synthetic polymer paint', 8, 1, 8),
('Orange and Yellow', 1956, 'Oil on canvas', 9, 1, 9),
('The Scream', 1893, 'Tempera on board', 10, 1, 7)

-- Exhibitions (identity starts at 1; curatorID references Employees above)
insert into Exhibitions ([name], startDate, endDate, curatorID, [description]) values
('Renaissance Highlights', '2021-03-01', '2021-06-01', 1, 'Showcase of Renaissance masterpieces.'),
('Baroque Brilliance', '2021-07-10', '2021-10-10', 2, 'Baroque art and sculpture.'),
('Dreams and Reality', '2022-01-15', '2022-04-15', 3, 'Exploring surrealist visions.'),
('Modern Masters', '2022-05-20', '2022-09-20', 4, 'Modernist painters and abstract forms.'),
('Pop Explosion', '2023-02-01', '2023-05-01', 5, 'Iconic works from Pop Art.'),
('Impressionist Light', '2023-06-10', '2023-09-10', 6, 'Impressionist landscapes.'),
('Expression and Emotion', '2023-10-15', '2024-01-15', 7, 'Expressionist paintings.'),
('Minimal Forms', '2024-02-01', '2024-05-01', 8, 'Minimalism and form.'),
('Abstract Visions', '2024-06-10', '2024-09-10', 9, 'Abstract modern art.'),
('Contemporary Now', '2025-01-01', '2025-04-01', 10, 'Current trends in art.')

-- ArtworkExhibitions (artID and eID reference identities above)
insert into ArtworkExhibitions (artID, eID) values
(1, 1),
(2, 2),
(3, 3),
(4, 4),
(5, 5),
(6, 6),
(7, 7),
(8, 8),
(9, 9),
(10, 10)

-- Visitors (identity starts at 1)
insert into Visitors ([name], visitorType, originCountry, generalFeedback) values
('John Carter', 'Adult', 'USA', 'Great experience!'),
('Maria Lopez', 'Student', 'Spain', 'Loved the impressionists.'),
('Ken Tanaka', 'Adult', 'Japan', 'Very informative guides.'),
('Lina Rossi', 'Senior', 'Italy', 'Beautiful artworks.'),
('George Wang', 'Adult', 'China', 'Wonderful exhibits.'),
('Sara Ahmed', 'Student', 'Egypt', 'Enjoyed the surrealism.'),
('Thomas Muller', 'Adult', 'Germany', 'Excellent curation.'),
('Olivia Brown', 'Child', 'UK', 'Fun activities!'),
('Lucas Silva', 'Adult', 'Brazil', 'Amazing museum.'),
('Emma White', 'Adult', 'Canada', 'Loved the modern art section.')

-- Tickets (identity starts at 1)
insert into Tickets (ticketType, price, validity, accessToEvents) values
('Adult', 20.00, 1, 0),
('Student', 10.00, 1, 1),
('Senior', 15.00, 1, 0),
('Child', 5.00, 1, 0),
('VIP', 50.00, 1, 1),
('Weekend', 25.00, 1, 1),
('Member', 100.00, 1, 1),
('Free Pass', 0.00, 1, 0),
('Evening', 12.00, 1, 0),
('Group', 80.00, 1, 1)

-- Visits (identity starts at 1; visitorID and ticketID reference identities above)
insert into Visits (visitorID, ticketID, visitDate, duration, guided) values
(1, 1, '2024-03-01', 120, 1),
(2, 2, '2024-03-02', 90, 0),
(3, 3, '2024-03-03', 60, 1),
(4, 4, '2024-03-04', 150, 0),
(5, 5, '2024-03-05', 200, 1),
(6, 6, '2024-03-06', 130, 1),
(7, 7, '2024-03-07', 100, 0),
(8, 8, '2024-03-08', 90, 0),
(9, 9, '2024-03-09', 110, 1),
(10, 10, '2024-03-10', 140, 1)

-- CulturalEvents (identity starts at 1; organizerID references Employees above)
insert into CulturalEvents ([name], eventDate, [time], duration, organizerID, maximumCapacity, [description]) values
('Art Lecture: Renaissance', '2024-03-15', '14:00', 120, 1, 100, 'Educational lecture on Renaissance art.'),
('Workshop: Modern Painting', '2024-04-10', '10:00', 180, 2, 50, 'Hands-on painting workshop.'),
('Panel: Women in Art', '2024-05-20', '16:00', 90, 3, 80, 'Panel discussion on women artists.'),
('Concert: Classical Night', '2024-06-01', '19:00', 120, 4, 150, 'Classical music in the gallery.'),
('Lecture: Pop Art Icons', '2024-07-10', '13:00', 90, 5, 60, 'Talk on Pop Art movement.'),
('Workshop: Sculpture Basics', '2024-08-15', '09:00', 180, 6, 40, 'Learn sculpture techniques.'),
('Seminar: Abstract Expressionism', '2024-09-20', '11:00', 120, 7, 70, 'In-depth look at abstract art.'),
('Film Screening: Art and Life', '2024-10-05', '18:00', 150, 8, 120, 'Documentary screening.'),
('Lecture: Art and Technology', '2024-11-10', '15:00', 100, 9, 90, 'Digital art exploration.'),
('Music Night: Jazz and Art', '2024-12-01', '20:00', 180, 10, 200, 'Live jazz concert among art.')

-- EventParticipations (visitorID and eventID reference identities above)
insert into EventParticipations (visitorID, eventID) values
(1, 1),
(2, 2),
(3, 3),
(4, 4),
(5, 5),
(6, 6),
(7, 7),
(8, 8),
(9, 9),
(10, 10)
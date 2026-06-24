USE MyArtMuseum;
GO

INSERT INTO ArtStyles ([name], [period], [description]) VALUES
('Renaissance', '14th–17th Century', 'Characterized by classical influence and humanism.'),
('Baroque', '17th–18th Century', 'Dramatic, bold, and emotional art style.'),
('Impressionism', '19th Century', 'Focus on light and color rather than detail.'),
('Cubism', 'Early 20th Century', 'Abstract art with geometric shapes.'),
('Surrealism', '1920s–1950s', 'Dreamlike, illogical compositions.'),
('Modernism', 'Late 19th–20th Century', 'Experimentation with form and abstraction.'),
('Expressionism', 'Early 20th Century', 'Emotion conveyed through distorted forms.'),
('Abstract', '20th Century', 'Non-representational art focused on color and shape.'),
('Pop Art', '1950s–1970s', 'Inspired by mass culture and advertising.'),
('Minimalism', '1960s–1970s', 'Art reduced to simplest forms and colors.');

INSERT INTO ArtworkTypes ([name], [description]) VALUES
('Painting', 'Artwork created using pigments on a surface.'),
('Sculpture', 'Three-dimensional artwork formed by shaping materials.'),
('Drawing', 'Artwork created using lines, often on paper.'),
('Mosaic', 'Art created using small pieces of colored glass or stone.'),
('Fresco', 'Painting done rapidly in watercolor on wet plaster.'),
('Print', 'Artwork produced by printing techniques.'),
('Installation', 'Large-scale, mixed-media construction.'),
('Photograph', 'Artistic image created with a camera.'),
('Digital Art', 'Artwork created using digital tools.'),
('Ceramic', 'Art made of clay and hardened by heat.');

INSERT INTO Collections (cID, [name], entryDate, [source], [description]) VALUES
(1, 'Renaissance Masters', '2001-05-20', 'Donation', 'Works from Italian Renaissance.'),
(2, 'Baroque Wonders', '2003-11-10', 'Purchase', 'Major Baroque artworks.'),
(3, 'Impressionist Dreams', '2005-06-15', 'Donation', 'Impressionist paintings.'),
(4, 'Cubist Geometry', '2010-04-18', 'Purchase', 'Cubist works.'),
(5, 'Surrealist Vision', '2012-09-23', 'Donation', 'Surrealist art collection.'),
(6, 'Modern Abstraction', '2015-03-30', 'Purchase', 'Modern and abstract art.'),
(7, 'Expressionist Soul', '2017-07-21', 'Donation', 'Expressionist pieces.'),
(8, 'Pop Art Explosion', '2018-02-10', 'Purchase', 'Famous Pop Art works.'),
(9, 'Minimalist Designs', '2019-05-14', 'Donation', 'Minimalist artworks.'),
(10, 'Contemporary Mix', '2020-01-01', 'Purchase', 'Mixed modern art pieces.');

INSERT INTO Artists ([name], birthDate, deathDate, originCountry, asID) VALUES
('Leonardo da Vinci', '1452-04-15', '1519-05-02', 'Italy', 151),
('Michelangelo', '1475-03-06', '1564-02-18', 'Italy', 151),
('Caravaggio', '1571-09-29', '1610-07-18', 'Italy', 152),
('Claude Monet', '1840-11-14', '1926-12-05', 'France', 153),
('Pablo Picasso', '1881-10-25', '1973-04-08', 'Spain', 154),
('Salvador Dalí', '1904-05-11', '1989-01-23', 'Spain', 155),
('Jackson Pollock', '1912-01-28', '1956-08-11', 'USA', 158),
('Andy Warhol', '1928-08-06', '1987-02-22', 'USA', 159),
('Mark Rothko', '1903-09-25', '1970-02-25', 'Latvia', 160),
('Edvard Munch', '1863-12-12', '1944-01-23', 'Norway', 157);

INSERT INTO Employees ([name], [role], email, phone, hireDate, salary) VALUES
('Alice Johnson', 'Curator', 'alice.j@mymuseum.org', '111-111-1111', '2010-02-10', 55000),
('Bob Smith', 'Art Restorer', 'bob.s@mymuseum.org', '222-222-2222', '2012-03-15', 48000),
('Clara Evans', 'Guide', 'clara.e@mymuseum.org', '333-333-3333', '2015-07-21', 40000),
('David Kim', 'Security Chief', 'david.k@mymuseum.org', '444-444-4444', '2016-09-01', 42000),
('Ella Brown', 'Archivist', 'ella.b@mymuseum.org', '555-555-5555', '2017-11-12', 46000),
('Frank Wilson', 'Curator', 'frank.w@mymuseum.org', '666-666-6666', '2018-04-25', 56000),
('Grace Lee', 'Administrator', 'grace.l@mymuseum.org', '777-777-7777', '2019-02-14', 50000),
('Henry Davis', 'Event Manager', 'henry.d@mymuseum.org', '888-888-8888', '2020-01-10', 53000),
('Ivy Chen', 'Guide', 'ivy.c@mymuseum.org', '999-999-9999', '2021-05-05', 41000),
('Jack Turner', 'Curator', 'jack.t@mymuseum.org', '101-010-1010', '2022-06-30', 57000);

INSERT INTO Artworks (title, creationYear, techinque, aID, atID, cID) VALUES
('Mona Lisa', 1503, 'Oil on wood', 106, 21, 1),
('The Creation of Adam', 1512, 'Fresco', 107, 25, 1),
('The Calling of Saint Matthew', 1600, 'Oil on canvas', 108, 21, 2),
('Water Lilies', 1916, 'Oil on canvas', 109, 21, 3),
('Les Demoiselles d’Avignon', 1907, 'Oil on canvas', 100, 21, 4),
('The Persistence of Memory', 1931, 'Oil on canvas', 101, 21, 5),
('No. 5, 1948', 1948, 'Drip painting', 102, 21, 6),
('Campbell’s Soup Cans', 1962, 'Synthetic polymer paint', 103, 21, 8),
('Orange and Yellow', 1956, 'Oil on canvas', 104, 21, 9),
('The Scream', 1893, 'Tempera on board', 105, 21, 7);

-- INSERT INTO Artworks (title, creationYear, techinque, aID, atID, cID) VALUES
-- ('Imaginary Artwork', 2021, 'Digital collage', 999, 9, 10); -- Referential integrity violation: artist 999 does not exist

INSERT INTO Exhibitions ([name], startDate, endDate, curatorID, [description]) VALUES
('Renaissance Highlights', '2021-03-01', '2021-06-01', 21, 'Showcase of Renaissance masterpieces.'),
('Baroque Brilliance', '2021-07-10', '2021-10-10', 22, 'Baroque art and sculpture.'),
('Dreams and Reality', '2022-01-15', '2022-04-15', 23, 'Exploring surrealist visions.'),
('Modern Masters', '2022-05-20', '2022-09-20', 24, 'Modernist painters and abstract forms.'),
('Pop Explosion', '2023-02-01', '2023-05-01', 25, 'Iconic works from Pop Art.'),
('Impressionist Light', '2023-06-10', '2023-09-10', 26, 'Impressionist landscapes.'),
('Expression and Emotion', '2023-10-15', '2024-01-15', 27, 'Expressionist paintings.'),
('Minimal Forms', '2024-02-01', '2024-05-01', 28, 'Minimalism and form.'),
('Abstract Visions', '2024-06-10', '2024-09-10', 29, 'Abstract modern art.'),
('Contemporary Now', '2025-01-01', '2025-04-01', 30, 'Current trends in art.');

INSERT INTO ArtworkExhibitions (artID, eID) VALUES
(62, 18),
(53, 19),
(54, 20),
(55, 21),
(56, 22),
(57, 23),
(58, 24),
(59, 25),
(60, 26),
(61, 27);

INSERT INTO Visitors ([name], visitorType, originCountry, generalFeedback) VALUES
('John Carter', 'Adult', 'USA', 'Great experience!'),
('Maria Lopez', 'Student', 'Spain', 'Loved the impressionists.'),
('Ken Tanaka', 'Adult', 'Japan', 'Very informative guides.'),
('Lina Rossi', 'Senior', 'Italy', 'Beautiful artworks.'),
('George Wang', 'Adult', 'China', 'Wonderful exhibits.'),
('Sara Ahmed', 'Student', 'Egypt', 'Enjoyed the surrealism.'),
('Thomas Müller', 'Adult', 'Germany', 'Excellent curation.'),
('Olivia Brown', 'Child', 'UK', 'Fun activities!'),
('Lucas Silva', 'Adult', 'Brazil', 'Amazing museum.'),
('Emma White', 'Adult', 'Canada', 'Loved the modern art section.');

INSERT INTO Tickets (ticketType, price, validity, accessToEvents) VALUES
('Adult', 20.00, 1, 0),
('Student', 10.00, 1, 1),
('Senior', 15.00, 1, 0),
('Child', 5.00, 1, 0),
('VIP', 50.00, 1, 1),
('Weekend', 25.00, 1, 1),
('Member', 100.00, 1, 1),
('Free Pass', 0.00, 1, 0),
('Evening', 12.00, 1, 0),
('Group', 80.00, 1, 1);

INSERT INTO Visits (visitorID, ticketID, visitDate, duration, guided) VALUES
(21, 21, '2024-03-01', 120, 1),
(22, 22, '2024-03-02', 90, 0),
(23, 23, '2024-03-03', 60, 1),
(24, 24, '2024-03-04', 150, 0),
(25, 25, '2024-03-05', 200, 1),
(26, 26, '2024-03-06', 130, 1),
(27, 27, '2024-03-07', 100, 0),
(28, 28, '2024-03-08', 90, 0),
(29, 29, '2024-03-09', 110, 1),
(30, 30, '2024-03-10', 140, 1);

INSERT INTO CulturalEvents ([name], eventDate, [time], duration, organizerID, maximumCapacity, [description]) VALUES
('Art Lecture: Renaissance', '2024-03-15', '14:00', 120, 21, 100, 'Educational lecture on Renaissance art.'),
('Workshop: Modern Painting', '2024-04-10', '10:00', 180, 22, 50, 'Hands-on painting workshop.'),
('Panel: Women in Art', '2024-05-20', '16:00', 90, 23, 80, 'Panel discussion on women artists.'),
('Concert: Classical Night', '2024-06-01', '19:00', 120, 24, 150, 'Classical music in the gallery.'),
('Lecture: Pop Art Icons', '2024-07-10', '13:00', 90, 25, 60, 'Talk on Pop Art movement.'),
('Workshop: Sculpture Basics', '2024-08-15', '09:00', 180, 26, 40, 'Learn sculpture techniques.'),
('Seminar: Abstract Expressionism', '2024-09-20', '11:00', 120, 27, 70, 'In-depth look at abstract art.'),
('Film Screening: Art & Life', '2024-10-05', '18:00', 150, 28, 120, 'Documentary screening.'),
('Lecture: Art and Technology', '2024-11-10', '15:00', 100, 29, 90, 'Digital art exploration.'),
('Music Night: Jazz & Art', '2024-12-01', '20:00', 180, 30, 200, 'Live jazz concert among art.');

INSERT INTO EventParticipations (visitorID, eventID) VALUES
(21, 12),
(22, 13),
(23, 14),
(24, 15),
(25, 16),
(26, 17),
(27, 18),
(28, 19),
(29, 20),
(30, 21);



-- Change the title of an artwork.
UPDATE Artworks
SET title = 'The Scream (Restored Edition)', techinque = 'Tempera and oil on board'
WHERE title = 'The Scream';

-- Give artists from the Renaissance period a description update if born between 1400 and 1600.
UPDATE Artists
SET originCountry = 'Italy (Updated)'
WHERE originCountry = 'Italy'
  AND birthDate BETWEEN '1400-01-01' AND '1600-12-31'
  AND [name] LIKE '%Leonardo%' OR [name] LIKE '%Michelangelo%';

-- Increase salaries of curators or archivists earning less than 56000.
UPDATE Employees
SET salary = salary + 2000
WHERE [role] IN ('Curator', 'Archivist')
  AND salary < 56000
  AND email IS NOT NULL;

-- Change the technique for artworks created after 1900 that are not digital and have “Oil” in their technique
UPDATE Artworks
SET techinque = 'Oil-based mixed technique'
WHERE creationYear >= 1900
  AND NOT techinque LIKE '%Digital%'
  AND techinque LIKE '%Oil%';



-- Delete visitors who are Students or Children with missing feedback
DELETE FROM Visitors
WHERE visitorType IN ('Student', 'Child')
  OR generalFeedback IS NULL;

-- Delete artworks not created between 1500 and 2000, and not part of collection 1
DELETE FROM Artworks
WHERE NOT (creationYear BETWEEN 1500 AND 2000)
  AND cID <> 1;



-- a. 2 queries with the union operation; use UNION [ALL] and OR;

-- Q1. Select all the artists from Italy or USA and all employees that are curators or guides.
SELECT [name], originCountry, 'Artist' AS Role
FROM Artists
WHERE originCountry = 'Italy' OR originCountry = 'USA'
UNION
SELECT [name], 'N/A', [role]
FROM Employees
WHERE [role] LIKE '%Curator%' OR [role] LIKE '%Guide%'
ORDER BY [name];

-- Q2. Select all visitors and employees whose name starts with 'A' and for each one a name score (the double of the length of the name).
SELECT [name], 'Visitor' AS Role, LEN([name]) * 2 AS NameScore
FROM Visitors
WHERE [name] LIKE 'A%'
UNION ALL
SELECT [name], [role], LEN([name]) * 2 AS NameScore
FROM Employees
WHERE [name] LIKE 'A%';


-- b. 2 queries with the intersection operation; use INTERSECT and IN;

-- Q3. Select the countries that are the origin countrie both for artists and visitors.
SELECT DISTINCT originCountry 
FROM Artists
INTERSECT
SELECT DISTINCT originCountry 
FROM Visitors;

-- Q4. Select the artists that are from countries with top-paying visitors (adults or VIPs).
SELECT [name], originCountry
FROM Artists
WHERE originCountry IN (
    SELECT DISTINCT originCountry
    FROM Visitors
    WHERE visitorType IN ('Adult', 'VIP')
);


-- c. 2 queries with the difference operation; use EXCEPT and NOT IN;

-- Q5. Select the countries that are the origin countries for some artists, but not for any visitor.
SELECT DISTINCT originCountry 
FROM Artists
EXCEPT
SELECT DISTINCT originCountry 
FROM Visitors;

-- Q6. Select the employees that are not curators (the role or for an exhibition).
SELECT eID, [name], [role]
FROM Employees
WHERE eID NOT IN (
    SELECT curatorID FROM Exhibitions
)
AND [role] NOT LIKE '%Curator%';


-- d. 4 queries with INNER JOIN, LEFT JOIN, RIGHT JOIN, and FULL JOIN (one  query per operator); 
-- one query will join at least 3 tables, while another one will join at least two many-to-many relationships;

-- Q7. Select artists that have their artworks being part of a collection, show their name, the title of the artwork and the collection.
SELECT a.[name] AS Artist, aw.title AS Title, c.[name] AS Collection
FROM Artists a
INNER JOIN Artworks aw ON a.aID = aw.aID
INNER JOIN Collections c ON aw.cID = c.cID
ORDER BY a.[name];

-- Q8. Select all the artworks that are part of an exhibition and show their title and the exhibition.
SELECT aw.title AS Title, e.[name] AS Exhibition
FROM Artworks aw
LEFT JOIN ArtworkExhibitions ae ON aw.artID = ae.artID
LEFT JOIN Exhibitions e ON ae.eID = e.eID;

-- Q9. Select all the exhibitions and their artworks and show their title and the exhibition.
SELECT aw.title AS Title, e.[name] AS Exhibition
FROM Artworks aw
RIGHT JOIN ArtworkExhibitions ae ON aw.artID = ae.artID
RIGHT JOIN Exhibitions e ON ae.eID = e.eID
ORDER BY e.[name];

-- Q10. Select all the visitors and all the cultural events.
SELECT v.[name] AS Visitor, ce.[name] AS Event
FROM Visitors v
FULL JOIN EventParticipations ep ON v.vID = ep.visitorID
FULL JOIN CulturalEvents ce ON ep.eventID = ce.eID
ORDER BY Visitor;


-- e. 2 queries using the IN operator to introduce a subquery in the WHERE clause; 
-- in at least one query, the subquery should include a subquery in its own WHERE clause;

-- Q11. Select the visitors that attended events organized by the emplyees that have the role of curators.
SELECT [name] AS Name, visitorType AS VisitorType
FROM Visitors
WHERE vID IN (
    SELECT visitorID
    FROM EventParticipations
    WHERE eventID IN (
        SELECT eID
        FROM CulturalEvents
        WHERE organizerID IN (
            SELECT eID 
            FROM Employees 
            WHERE [role] LIKE '%Curator%'
        )
    )
);

-- Q12. Select the emplyees that have the role of administrators that curated exhibitions in 2023.
SELECT [name] AS Name, [role] AS Role
FROM Employees
WHERE eID IN (
    SELECT curatorID
    FROM Exhibitions
    WHERE startDate BETWEEN '2023-01-01' AND '2023-12-31'
)
AND [role] = 'Administrator';


-- f. 2 queries using the EXISTS operator to introduce a subquery in the WHERE clause;

-- Q13. Select all the artists that have artworks.
SELECT [name] AS ArtistName
FROM Artists a
WHERE EXISTS (
    SELECT 1 
    FROM Artworks aw 
    WHERE aw.aID = a.aID
);

-- Q14. Select all the collections that do not have any artwork.
SELECT [name] AS CollectionName
FROM Collections c
WHERE NOT EXISTS (
    SELECT 1 
    FROM Artworks aw 
    WHERE aw.cID = c.cID
);


-- g. 2 queries with a subquery in the FROM clause;

-- Q15. Select the average salary of an employee, based on the role.
SELECT r.[role] AS Role, AVG(r.salary) AS AverageSalary
FROM (
    SELECT [role], salary 
    FROM Employees
) AS r
GROUP BY r.[role];

-- Q16. Count the noumber of artworks of each artist and for each one of them establish a score (number_of_artworks * 10).
SELECT s.Artist, s.ArtCount AS NumberOfArtworks, s.ArtCount * 10 AS ArtistScore
FROM (
    SELECT a.[name] AS Artist, COUNT(aw.artID) AS ArtCount
    FROM Artists a
    LEFT JOIN Artworks aw ON a.aID = aw.aID
    GROUP BY a.[name]
) AS s
WHERE s.ArtCount > 0;


-- h. 4 queries with the GROUP BY clause, 3 of which also contain the HAVING clause; 
-- 2 of the latter will also have a subquery in the HAVING clause; use the aggregation operators: COUNT, SUM, AVG, MIN, MAX;

-- Q17. Count the number of artworks of each artist and order them decreasingly.
SELECT a.[name] AS Artist, COUNT(aw.artID) AS ArtworkCount
FROM Artists a
JOIN Artworks aw ON a.aID = aw.aID
GROUP BY a.[name]
ORDER BY COUNT(aw.artID) DESC;

-- Q18. Compute the average salary for each role and show increasingly the oanes higher than 45000.
SELECT [role] AS Role, AVG(salary) AS AverageSalary
FROM Employees
GROUP BY [role]
HAVING AVG(salary) > 45000
ORDER BY AVG(salary);

-- Q19. Select all the roles of the employees that earn more than the average salary and 
-- show the roles and the total salary of all the employees having that role.
SELECT [role] AS Role, SUM(salary) AS TotalSalary
FROM Employees
GROUP BY [role]
HAVING AVG(salary) > (
    SELECT AVG(salary) 
    FROM Employees
);

-- Q20. Select the countries that are the origin countries for more artists than average and 
-- show their CountryScore (the double of the number of artists that came from there).
SELECT originCountry AS OriginCountry, COUNT(*) AS ArtistCount, COUNT(*) * 2 AS CountryScore
FROM Artists
GROUP BY originCountry
HAVING COUNT(*) > (
    SELECT AVG(CountryArtistCount)
    FROM (
        SELECT COUNT(*) AS CountryArtistCount
        FROM Artists
        GROUP BY originCountry
    ) AS CountryCounts
);


-- i. 4 queries using ANY and ALL to introduce a subquery in the WHERE clause; 
-- rewrite 2 of them with aggregation operators, and the other 2 with [NOT] IN.

-- Q21. Select the first 5 artists that were born before any employee's hire year.
SELECT TOP 5 [name] AS Name, birthDate AS Birthdate
FROM Artists
WHERE YEAR(birthDate) < ANY (
    SELECT YEAR(hireDate) 
    FROM Employees
);

SELECT TOP 5 [name] AS Name, birthDate AS Birthdate
FROM Artists
WHERE YEAR(birthDate) < (
    SELECT MAX(YEAR(hireDate))
    FROM Employees
);

-- Q22. Select all the employees that earn more than all the archivists.
SELECT [name] AS Name, salary AS Salary
FROM Employees
WHERE salary > ALL (
    SELECT salary 
    FROM Employees 
    WHERE [role] = 'Archivist'
);

SELECT [name] AS Name, salary AS Salary
FROM Employees 
WHERE salary > (SELECT MAX(salary) FROM Employees WHERE [role] = 'Archivist');

-- Q23. Select all the artworks created before all Pablo Picasso's artworks.
SELECT title AS Title, creationYear AS CreationYear
FROM Artworks
WHERE creationYear < ALL (
    SELECT creationYear
    FROM Artworks aw
    JOIN Artists a ON aw.aID = a.aID
    WHERE a.[name] = 'Pablo Picasso'
);

SELECT title AS Title, creationYear AS CreationYear
FROM Artworks
WHERE artID NOT IN (
     SELECT aw.artID 
     FROM Artworks aw 
     JOIN Artists a ON aw.aID = a.aID 
     WHERE a.[name] = 'Pablo Picasso' 
     AND aw.creationYear >= Artworks.creationYear
);

-- Q24. Select the first 3 employees that earn less or equal than any guide.
SELECT TOP 3 [name] AS Name, salary AS Salary
FROM Employees
WHERE salary <= ANY (
    SELECT salary 
    FROM Employees 
    WHERE [role] = 'Guide'
);

SELECT TOP 3 [name] AS Name, salary AS Salary
FROM Employees
WHERE eID IN (
     SELECT eID 
     FROM Employees 
     WHERE salary <= (SELECT MAX(salary) FROM Employees WHERE [role] = 'Guide')
);

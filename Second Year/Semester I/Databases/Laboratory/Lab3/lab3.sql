USE MyArtMuseum

DROP PROCEDURE IF EXISTS changePriceFromDecimalToInt
DROP PROCEDURE IF EXISTS changePriceFromIntToDecimal
DROP PROCEDURE IF EXISTS removeEmployeesHireDate
DROP PROCEDURE IF EXISTS addEmployeesHireDate
DROP PROCEDURE IF EXISTS addDefaultConstraintToVisitsDuration
DROP PROCEDURE IF EXISTS removeDefaultConstraintFromVisitsDuration
DROP PROCEDURE IF EXISTS addPKToMuseumRooms
DROP PROCEDURE IF EXISTS removePKOfMuseumRooms
DROP PROCEDURE IF EXISTS addArtStyleNameAsCandidate
DROP PROCEDURE IF EXISTS removeArtStyleNameCandidate
DROP PROCEDURE IF EXISTS removeFKOfExhibitions
DROP PROCEDURE IF EXISTS addFKToExhibitions
DROP PROCEDURE IF EXISTS createMuseumRooms 
DROP PROCEDURE IF EXISTS dropMuseumRooms
DROP PROCEDURE IF EXISTS goToVersion
DROP TABLE IF EXISTS VERSION_TABLE
DROP TABLE IF EXISTS PROCEDURES_TABLE
GO

-- a. modify the type of a column
-- create procedure to change the type of Price for Tickets from Decimal to Int
CREATE PROCEDURE changePriceFromDecimalToInt AS
	ALTER TABLE Tickets ALTER COLUMN price INT NOT NULL
GO

-- reversed
-- create procedure to change the type of price for Tickets from Int to Decimal
CREATE PROCEDURE changePriceFromIntToDecimal AS
	ALTER TABLE Tickets ALTER COLUMN Price DECIMAL(10, 2) NOT NULL
GO


-- b. add / remove a column
-- remove the hireDate column from the Employees, if it exists
CREATE PROCEDURE removeEmployeesHireDate AS
	IF EXISTS (SELECT * FROM sys.columns WHERE 
	Name = N'hireDate' AND OBJECT_ID = OBJECT_ID(N'Employees'))
		ALTER TABLE Employees DROP COLUMN hireDate
GO

-- reversed
-- add the hireDate column fom the Employees, if it doesn't exist
CREATE PROCEDURE addEmployeesHireDate AS
	IF NOT EXISTS (SELECT * FROM sys.columns WHERE 
	Name = N'hireDate' AND OBJECT_ID = OBJECT_ID(N'Employees'))
		ALTER TABLE Employees ADD hireDate date
GO


-- c. add / remove a DEFAULT constraint
-- add the DEFAULT CONSTRAINT to duration, Visits Table
CREATE PROCEDURE addDefaultConstraintToVisitsDuration AS
	ALTER TABLE Visits ADD CONSTRAINT Duration DEFAULT 60 FOR duration
Go

-- reversed
-- remove the DEFAULT constraint from duration column, Visits Table
CREATE PROCEDURE removeDefaultConstraintFromVisitsDuration AS
	ALTER TABLE Visits DROP CONSTRAINT Duration 
GO


-- d. add / remove a primary key
-- create a procedure to add a primary key to the MuseumRooms
CREATE PROCEDURE addPKToMuseumRooms AS
	ALTER TABLE MuseumRooms ADD CONSTRAINT 
	roomID PRIMARY KEY (roomID)
GO

-- reversed
-- create a procedure to remove the primary key of MuseumRooms
CREATE PROCEDURE removePKOfMuseumRooms AS
	ALTER TABLE MuseumRooms DROP CONSTRAINT roomID 
GO


-- e. add / remove a candidate key
-- create a procedure to add to the ArtStyles the [name] as a candidate key
CREATE PROCEDURE addArtStyleNameAsCandidate AS
	ALTER TABLE ArtStyles ADD CONSTRAINT 
	nameArtStyle UNIQUE ([name])
GO

-- reversed
-- create procedure to add remove from the ArtStyles the candidate key
CREATE PROCEDURE removeArtStyleNameCandidate AS
	ALTER TABLE ArtStyles DROP CONSTRAINT nameArtStyle
GO


-- f. add / remove a foreign key
-- create procedure to remove the Foreign Fey (UQ_curator = curatorID) from Exhibitions table
CREATE PROCEDURE removeFKOfExhibitions AS
	ALTER TABLE Exhibitions DROP CONSTRAINT UQ_curator
GO

-- reversed
-- create procedure to add the Foreign Key (UQ_curator = curatorID) to Exhibitions Table
CREATE PROCEDURE addFKToExhibitions AS
	ALTER TABLE Exhibitions ADD CONSTRAINT UQ_curator
	FOREIGN KEY (curatorID) REFERENCES Employees(eID)
GO


-- g. create / drop a table
-- create a table MuseumRooms (without a primary key for d))
CREATE PROCEDURE createMuseumRooms AS
	CREATE TABLE MuseumRooms(
		roomID smallint NOT NULL,
		[name] varchar(100),
		capacity int);
GO

-- reversed 
-- drop MuseumRooms table
CREATE PROCEDURE dropMuseumRooms AS
	DROP TABLE IF EXISTS MuseumRooms
GO



CREATE TABLE VERSION_TABLE(
        version int,
        PRIMARY KEY(version)
    );
INSERT INTO VERSION_TABLE VALUES(0);

CREATE TABLE PROCEDURES_TABLE(
	fromVersion INT,
	toVersion INT,
	procedureName VARCHAR(255),
	PRIMARY KEY(fromVersion, toVersion)
);

INSERT INTO PROCEDURES_TABLE VALUES(0, 1, 'changePriceFromDecimalToInt');
INSERT INTO PROCEDURES_TABLE VALUES(1, 2, 'removeEmployeesHireDate');
INSERT INTO PROCEDURES_TABLE VALUES(2, 3, 'addDefaultConstraintToVisitsDuration');
INSERT INTO PROCEDURES_TABLE VALUES(3, 4, 'createMuseumRooms');
INSERT INTO PROCEDURES_TABLE VALUES(4, 5, 'addPKToMuseumRooms');
INSERT INTO PROCEDURES_TABLE VALUES(5, 6, 'addArtStyleNameAsCandidate');
INSERT INTO PROCEDURES_TABLE VALUES(6, 7, 'removeFKOfExhibitions');

INSERT INTO PROCEDURES_TABLE VALUES(7, 6, 'addFKToExhibitions');
INSERT INTO PROCEDURES_TABLE VALUES(6, 5, 'removeArtStyleNameCandidate');
INSERT INTO PROCEDURES_TABLE VALUES(5, 4, 'removePKOfMuseumRooms');
INSERT INTO PROCEDURES_TABLE VALUES(4, 3, 'dropMuseumRooms');
INSERT INTO PROCEDURES_TABLE VALUES(3, 2, 'removeDefaultConstraintFromVisitsDuration');
INSERT INTO PROCEDURES_TABLE VALUES(2, 1, 'addEmployeesHireDate');
INSERT INTO PROCEDURES_TABLE VALUES(1, 0, 'changePriceFromIntToDecimal');
GO

CREATE PROCEDURE goToVersion(@newVersion INT) AS
	BEGIN
		DECLARE @currentVersion INT
		DECLARE @procName VARCHAR(255)

		SELECT @currentVersion = version FROM VERSION_TABLE

		IF @newVersion > (SELECT MAX(toVersion) FROM PROCEDURES_TABLE)
            RAISERROR('Invalid version', 16, 1);

		IF @newVersion < (SELECT MIN(fromVersion) FROM PROCEDURES_TABLE)
            RAISERROR('Invalid version', 16, 1);

		WHILE @currentVersion < @newVersion BEGIN
            SELECT @procName = procedureName FROM PROCEDURES_TABLE 
			WHERE fromVersion = @currentVersion AND toVersion = @currentVersion + 1;

            EXEC (@procName);

            SET @currentVersion = @currentVersion + 1;
            UPDATE VERSION_TABLE SET version = @currentVersion;
        END;

		WHILE @currentVersion > @newVersion BEGIN
            SELECT @procName = procedureName FROM PROCEDURES_TABLE 
			WHERE fromVersion = @currentVersion AND toVersion = @currentVersion - 1;

            EXEC (@procName);

            SET @currentVersion = @currentVersion - 1;
            UPDATE VERSION_TABLE SET version = @currentVersion;
        END;
	END;
GO


EXEC goToVersion 0
SELECT * FROM VERSION_TABLE

EXEC goToVersion 7
SELECT * FROM VERSION_TABLE
SELECT * FROM MuseumRooms
SELECT * FROM Employees

EXEC goToVersion 1
SELECT * FROM MuseumRooms
SELECT * FROM VERSION_TABLE
SELECT * FROM Employees
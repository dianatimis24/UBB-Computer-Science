USE MyArtMuseum
GO

-- drop all the foreign key constraints
if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunTables_Tables]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestRunTables] DROP CONSTRAINT FK_TestRunTables_Tables
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestTables_Tables]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestTables] DROP CONSTRAINT FK_TestTables_Tables
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunTables_TestRuns]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestRunTables] DROP CONSTRAINT FK_TestRunTables_TestRuns
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunViews_TestRuns]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestRunViews] DROP CONSTRAINT FK_TestRunViews_TestRuns
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestTables_Tests]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestTables] DROP CONSTRAINT FK_TestTables_Tests
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestViews_Tests]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestViews] DROP CONSTRAINT FK_TestViews_Tests
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunViews_Views]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestRunViews] DROP CONSTRAINT FK_TestRunViews_Views
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestViews_Views]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestViews] DROP CONSTRAINT FK_TestViews_Views
GO


-- drop tables
if exists (select * from dbo.sysobjects where id = object_id(N'[Tables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [Tables]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestRunTables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestRunTables]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestRunViews]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestRunViews]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestRuns]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestRuns]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestTables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestTables]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestViews]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestViews]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[Tests]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [Tests]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[Views]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [Views]
GO


-- create the tables
CREATE TABLE [Tables] (
	[TableID] [int] IDENTITY (1, 1) NOT NULL ,
	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 
) ON [PRIMARY]
GO


CREATE TABLE [TestRunTables] (
	[TestRunID] [int] NOT NULL ,
	[TableID] [int] NOT NULL ,
	[StartAt] [datetime] NOT NULL ,
	[EndAt] [datetime] NOT NULL 
) ON [PRIMARY]
GO



CREATE TABLE [TestRunViews] (
	[TestRunID] [int] NOT NULL ,
	[ViewID] [int] NOT NULL ,
	[StartAt] [datetime] NOT NULL ,
	[EndAt] [datetime] NOT NULL 
) ON [PRIMARY]
GO


CREATE TABLE [TestRuns] (
	[TestRunID] [int] IDENTITY (1, 1) NOT NULL ,
	[Description] [nvarchar] (2000) COLLATE SQL_Latin1_General_CP1_CI_AS NULL ,
	[StartAt] [datetime] NULL ,
	[EndAt] [datetime] NULL 
) ON [PRIMARY]
GO


CREATE TABLE [TestTables] (
	[TestID] [int] NOT NULL ,
	[TableID] [int] NOT NULL ,
	[NoOfRows] [int] NOT NULL ,
	[Position] [int] NOT NULL 
) ON [PRIMARY]
GO


CREATE TABLE [TestViews] (
	[TestID] [int] NOT NULL ,
	[ViewID] [int] NOT NULL 
) ON [PRIMARY]
GO


CREATE TABLE [Tests] (  
	[TestID] [int] IDENTITY (1, 1) NOT NULL ,
	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 
) ON [PRIMARY]
GO


CREATE TABLE [Views] (
	[ViewID] [int] IDENTITY (1, 1) NOT NULL ,
	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 
) ON [PRIMARY]
GO


-- adding the constraints
ALTER TABLE [Tables] WITH NOCHECK ADD 
	CONSTRAINT [PK_Tables] PRIMARY KEY  CLUSTERED 
	([TableID]) ON [PRIMARY]
GO


ALTER TABLE [TestRunTables] WITH NOCHECK ADD 
	CONSTRAINT [PK_TestRunTables] PRIMARY KEY  CLUSTERED 
	(
		[TestRunID],
		[TableID]
	) ON [PRIMARY] 
GO


ALTER TABLE [TestRunViews] WITH NOCHECK ADD 
	CONSTRAINT [PK_TestRunViews] PRIMARY KEY  CLUSTERED 
	([TestRunID], [ViewID]) ON [PRIMARY] 
GO



ALTER TABLE [TestRuns] WITH NOCHECK ADD 
	CONSTRAINT [PK_TestRuns] PRIMARY KEY  CLUSTERED 
	([TestRunID]) ON [PRIMARY] 
GO


ALTER TABLE [TestTables] WITH NOCHECK ADD 
	CONSTRAINT [PK_TestTables] PRIMARY KEY  CLUSTERED 
	([TestID], [TableID]) ON [PRIMARY] 
GO


ALTER TABLE [TestViews] WITH NOCHECK ADD 
	CONSTRAINT [PK_TestViews] PRIMARY KEY  CLUSTERED 
	([TestID], [ViewID]) ON [PRIMARY] 
GO


ALTER TABLE [Tests] WITH NOCHECK ADD 
	CONSTRAINT [PK_Tests] PRIMARY KEY  CLUSTERED 
	([TestID]) ON [PRIMARY] 
GO


ALTER TABLE [Views] WITH NOCHECK ADD 
	CONSTRAINT [PK_Views] PRIMARY KEY  CLUSTERED 
	([ViewID]) ON [PRIMARY] 
GO


ALTER TABLE [TestRunTables] ADD 
	CONSTRAINT [FK_TestRunTables_Tables] FOREIGN KEY 
	([TableID]) REFERENCES [Tables] ([TableID]) ON DELETE CASCADE  ON UPDATE CASCADE,
	CONSTRAINT [FK_TestRunTables_TestRuns] FOREIGN KEY 
	([TestRunID]) REFERENCES [TestRuns] ([TestRunID]) ON DELETE CASCADE  ON UPDATE CASCADE 
GO


ALTER TABLE [TestRunViews] ADD 
	CONSTRAINT [FK_TestRunViews_TestRuns] FOREIGN KEY 
	([TestRunID]) REFERENCES [TestRuns] ([TestRunID]) ON DELETE CASCADE  ON UPDATE CASCADE,
	CONSTRAINT [FK_TestRunViews_Views] FOREIGN KEY 
	([ViewID]) REFERENCES [Views] ([ViewID]) ON DELETE CASCADE  ON UPDATE CASCADE 
GO


ALTER TABLE [TestTables] ADD 
	CONSTRAINT [FK_TestTables_Tables] FOREIGN KEY 
	([TableID]) REFERENCES [Tables] ([TableID]) ON DELETE CASCADE  ON UPDATE CASCADE,
	CONSTRAINT [FK_TestTables_Tests] FOREIGN KEY 
	([TestID]) REFERENCES [Tests] ([TestID]) ON DELETE CASCADE  ON UPDATE CASCADE 
GO


ALTER TABLE [TestViews] ADD 
	CONSTRAINT [FK_TestViews_Tests] FOREIGN KEY 
	([TestID]) REFERENCES [Tests] ([TestID]),
	CONSTRAINT [FK_TestViews_Views] FOREIGN KEY 
	([ViewID]) REFERENCES [Views] ([ViewID])
GO



-- a view on one table
CREATE OR ALTER VIEW EmployeesView
AS
	SELECT * FROM Employees
GO

-- a view with 2 tables
CREATE OR ALTER VIEW ArtistsArtworksView
AS 
	SELECT a.[name] AS [Artist Name], art.title AS [Artwork Title], a.originCountry AS [Origin Country], art.creationYear AS [Creation Year] 
	FROM Artists a FULL JOIN Artworks art ON a.aID = art.aID
GO

--  a view with Group By
CREATE OR ALTER VIEW ArtistsArtworksGroupedView
AS
	SELECT a.[name] AS [Artist Name], art.title AS [Artwork Title], a.originCountry AS [Origin Country], art.creationYear AS [Creation Year] 
	FROM Artists a FULL JOIN Artworks art ON a.aID = art.aID
	GROUP BY a.[name], a.originCountry, art.creationYear, art.title
GO



-- 1 PK
CREATE OR ALTER PROCEDURE populateTableArtStyles (@rows INT)
AS
DECLARE @i INT
SET @i = 0
WHILE @i < @rows BEGIN
	INSERT INTO ArtStyles ([name], [period], [description])
	VALUES('ArtStyle' + CAST(@i AS VARCHAR(50)), CAST(@i AS VARCHAR(100)), '-')
	SET @i = @i + 1
END
GO

-- 1 PK and 1 FK 
CREATE OR ALTER PROCEDURE populateTableArtists (@rows INT)
AS
DECLARE @i INT
SET @i = 0
DECLARE @artstyleId SMALLINT
SET @artstyleId = (SELECT TOP 1 asID FROM ArtStyles)
WHILE @i < @rows BEGIN
	INSERT INTO Artists ([name], birthDate, deathDate, originCountry, asID)
	VALUES('Name' + CAST(@i AS VARCHAR(255)), SYSDATETIME(), SYSDATETIME(), 'Country' + CAST(@i AS VARCHAR(50)), @artstyleId)
	SET @i = @i + 1
END
GO


-- Multicolumn PK
-- Parent for Artworks FK (atID)
CREATE OR ALTER PROCEDURE populateTableArtworkTypes (@rows INT)
AS
DECLARE @i INT
SET @i = 0
WHILE @i < @rows BEGIN
	INSERT INTO ArtworkTypes ([name], [description])
	VALUES('Type' + CAST(@i AS VARCHAR(200)), 'Description' + CAST(@i AS VARCHAR(1000)))
	SET @i = @i + 1
END
GO

-- Parent for ArtworkExhibitions (artID)
CREATE OR ALTER PROCEDURE populateTableArtworks (@rows INT)
AS
DECLARE @i INT
SET @i = 0
DECLARE @aID SMALLINT = (SELECT TOP 1 aID FROM Artists)
DECLARE @atID SMALLINT = (SELECT TOP 1 atID FROM ArtworkTypes)
DECLARE @cID SMALLINT = (SELECT TOP 1 cID FROM Collections)
WHILE @i < @rows BEGIN
	INSERT INTO Artworks (title, creationYear, techinque, aID, atID, cID)
	VALUES('Title' + CAST(@i AS VARCHAR(300)), 1900 + @i % 100, 'Technique' + CAST(@i AS VARCHAR(200)), @aID, @atID, @cID)
	SET @i = @i + 1
END
GO

-- Parent for Exhibitions (curatorID)
CREATE OR ALTER PROCEDURE populateTableEmployees (@rows INT)
AS
DECLARE @i INT
SET @i = 0
WHILE @i < @rows BEGIN
	INSERT INTO Employees ([name], [role], email, phone, hireDate, salary)
	VALUES(
		'Employee' + CAST(@i AS VARCHAR(300)),
		'Curator',
		'email' + CAST(@i AS VARCHAR(200)) + '@museum.com',
		'555-' + RIGHT('0000' + CAST(@i AS VARCHAR(4)), 4),
		GETDATE(),
		50000.00
	)
	SET @i = @i + 1
END
GO

-- Parent for Artworks FK (cID)
CREATE OR ALTER PROCEDURE populateTableCollections (@rows INT)
AS
DECLARE @i INT
SET @i = 1 -- Start from 1 for cID
WHILE @i <= @rows BEGIN
	INSERT INTO Collections (cID, [name], [entryDate], [source], [description])
	VALUES(@i, 'Collection' + CAST(@i AS VARCHAR(200)), GETDATE(), 'Source' + CAST(@i AS VARCHAR(100)), 'Desc')
	SET @i = @i + 1
END
GO

-- Parent for ArtworkExhibitions (eID)
CREATE OR ALTER PROCEDURE populateTableExhibitions (@rows INT)
AS
DECLARE @i INT
SET @i = 0
DECLARE @curatorID SMALLINT
WHILE @i < @rows BEGIN
	SET @curatorID = (SELECT eID FROM Employees ORDER BY eID OFFSET @i ROWS FETCH NEXT 1 ROW ONLY)
	IF @curatorID IS NULL BREAK;
	INSERT INTO Exhibitions ([name], startDate, endDate, curatorID, [description])
	VALUES(
		'Exhibition' + CAST(@i AS VARCHAR(300)),
		DATEADD(day, @i, GETDATE()),
		DATEADD(month, 3, DATEADD(day, @i, GETDATE())),
		@curatorID,
		'Description'
	)
	SET @i = @i + 1
END
GO

CREATE OR ALTER PROCEDURE populateTableArtworkExhibitions (@rows INT)
AS
DECLARE @i INT
SET @i = 0
DECLARE @artID SMALLINT
DECLARE @eID SMALLINT

SET @artID = (SELECT TOP 1 artID FROM Artworks)
SET @eID = (SELECT TOP 1 eID FROM Exhibitions)

WHILE @i < @rows BEGIN
	INSERT INTO ArtworkExhibitions (artID, eID)
	VALUES(@artID + @i, @eID + @i % 5) 
	SET @i = @i + 1
END
GO



CREATE OR ALTER PROCEDURE RunTest @TestID INT
AS
BEGIN
    SET NOCOUNT ON;
    
    DECLARE @TestRunID INT;
    DECLARE @StartTime DATETIME = GETDATE();
    DECLARE @EndTime DATETIME;
    

    INSERT INTO TestRuns (Description, StartAt)
    VALUES ('Run for TestID: ' + CAST(@TestID AS VARCHAR), @StartTime);
    
    SET @TestRunID = SCOPE_IDENTITY();


    DECLARE @TableName NVARCHAR(50);
    DECLARE @TableID INT;
    DECLARE @Position INT;
    
    -- Cursor for Deletion
    DECLARE DeleteCursor CURSOR FOR
    SELECT T.Name, T.TableID
    FROM TestTables TT
    INNER JOIN Tables T ON TT.TableID = T.TableID
    WHERE TT.TestID = @TestID
    ORDER BY TT.Position ASC;

    OPEN DeleteCursor;
    FETCH NEXT FROM DeleteCursor INTO @TableName, @TableID;

    WHILE @@FETCH_STATUS = 0
    BEGIN
        DECLARE @DeleteSQL NVARCHAR(MAX) = N'DELETE FROM ' + @TableName;
        EXEC sp_executesql @DeleteSQL;

        FETCH NEXT FROM DeleteCursor INTO @TableName, @TableID;
    END
    CLOSE DeleteCursor;
    DEALLOCATE DeleteCursor;


    DECLARE @NoOfRows INT;
    DECLARE @T1 DATETIME;
    DECLARE @T2 DATETIME;
    
    -- Cursor for Insertion
    DECLARE InsertCursor CURSOR FOR
    SELECT T.Name, T.TableID, TT.NoOfRows
    FROM TestTables TT
    INNER JOIN Tables T ON TT.TableID = T.TableID
    WHERE TT.TestID = @TestID
    ORDER BY TT.Position DESC;

    OPEN InsertCursor;
    FETCH NEXT FROM InsertCursor INTO @TableName, @TableID, @NoOfRows;

    WHILE @@FETCH_STATUS = 0
    BEGIN
        SET @T1 = GETDATE();

        IF @TableName = 'ArtStyles' EXEC populateTableArtStyles @NoOfRows;
        ELSE IF @TableName = 'ArtworkTypes' EXEC populateTableArtworkTypes @NoOfRows;
        ELSE IF @TableName = 'Collections' EXEC populateTableCollections @NoOfRows;
        ELSE IF @TableName = 'Employees' EXEC populateTableEmployees @NoOfRows;
        ELSE IF @TableName = 'Exhibitions' EXEC populateTableExhibitions @NoOfRows;
        ELSE IF @TableName = 'Artists' EXEC populateTableArtists @NoOfRows;
        ELSE IF @TableName = 'Artworks' EXEC populateTableArtworks @NoOfRows;
        ELSE IF @TableName = 'ArtworkExhibitions' EXEC populateTableArtworkExhibitions @NoOfRows;
        
        SET @T2 = GETDATE();

        INSERT INTO TestRunTables(TestRunID, TableID, StartAt, EndAt)
        VALUES (@TestRunID, @TableID, @T1, @T2);

        FETCH NEXT FROM InsertCursor INTO @TableName, @TableID, @NoOfRows;
    END
    CLOSE InsertCursor;
    DEALLOCATE InsertCursor;


    DECLARE @ViewName NVARCHAR(50);
    DECLARE @ViewID INT;

    DECLARE ViewCursor CURSOR FOR
    SELECT V.Name, V.ViewID
    FROM TestViews TV
    INNER JOIN Views V ON TV.ViewID = V.ViewID
    WHERE TV.TestID = @TestID;

    OPEN ViewCursor;
    FETCH NEXT FROM ViewCursor INTO @ViewName, @ViewID;

    WHILE @@FETCH_STATUS = 0
    BEGIN
        SET @T1 = GETDATE();

        DECLARE @ViewSQL NVARCHAR(MAX) = N'SELECT * FROM ' + @ViewName;
        EXEC sp_executesql @ViewSQL;

        SET @T2 = GETDATE();

        INSERT INTO TestRunViews(TestRunID, ViewID, StartAt, EndAt)
        VALUES (@TestRunID, @ViewID, @T1, @T2);

        FETCH NEXT FROM ViewCursor INTO @ViewName, @ViewID;
    END
    CLOSE ViewCursor;
    DEALLOCATE ViewCursor;


    SET @EndTime = GETDATE();
    
    UPDATE TestRuns
    SET EndAt = @EndTime
    WHERE TestRunID = @TestRunID;

END
GO


DELETE FROM TestTables;
DELETE FROM TestViews;
DELETE FROM Tests;
DELETE FROM Tables;
DELETE FROM Views;


INSERT INTO Tables(Name) VALUES ('ArtStyles');          
INSERT INTO Tables(Name) VALUES ('ArtworkTypes');       
INSERT INTO Tables(Name) VALUES ('Collections');        
INSERT INTO Tables(Name) VALUES ('Employees');         
INSERT INTO Tables(Name) VALUES ('Exhibitions');        
INSERT INTO Tables(Name) VALUES ('Artists');     
INSERT INTO Tables(Name) VALUES ('Artworks');  
INSERT INTO Tables(Name) VALUES ('ArtworkExhibitions');


INSERT INTO Views(Name) VALUES ('EmployeesView');
INSERT INTO Views(Name) VALUES ('ArtistsArtworksView');
INSERT INTO Views(Name) VALUES ('ArtistsArtworksGroupedView');


INSERT INTO Tests(Name) VALUES ('Full Performance Test');
DECLARE @TestID INT = SCOPE_IDENTITY();


INSERT INTO TestTables(TestID, TableID, NoOfRows, Position) SELECT @TestID, TableID, 5, 1 FROM Tables WHERE Name = 'ArtStyles';
INSERT INTO TestTables(TestID, TableID, NoOfRows, Position) SELECT @TestID, TableID, 5, 2 FROM Tables WHERE Name = 'ArtworkTypes';
INSERT INTO TestTables(TestID, TableID, NoOfRows, Position) SELECT @TestID, TableID, 5, 3 FROM Tables WHERE Name = 'Collections';
INSERT INTO TestTables(TestID, TableID, NoOfRows, Position) SELECT @TestID, TableID, 5, 4 FROM Tables WHERE Name = 'Employees';
INSERT INTO TestTables(TestID, TableID, NoOfRows, Position) SELECT @TestID, TableID, 5, 5 FROM Tables WHERE Name = 'Exhibitions';

INSERT INTO TestTables(TestID, TableID, NoOfRows, Position) SELECT @TestID, TableID, 50, 6 FROM Tables WHERE Name = 'Artists';
INSERT INTO TestTables(TestID, TableID, NoOfRows, Position) SELECT @TestID, TableID, 50, 7 FROM Tables WHERE Name = 'Artworks';
INSERT INTO TestTables(TestID, TableID, NoOfRows, Position) SELECT @TestID, TableID, 100, 8 FROM Tables WHERE Name = 'ArtworkExhibitions';


INSERT INTO TestViews(TestID, ViewID) SELECT @TestID, ViewID FROM Views WHERE Name = 'EmployeesView';
INSERT INTO TestViews(TestID, ViewID) SELECT @TestID, ViewID FROM Views WHERE Name = 'ArtistsArtworksView';
INSERT INTO TestViews(TestID, ViewID) SELECT @TestID, ViewID FROM Views WHERE Name = 'ArtistsArtworksGroupedView';


EXEC RunTest @TestID;


SELECT * FROM TestRuns;
SELECT * FROM TestRunTables;
SELECT * FROM TestRunViews;
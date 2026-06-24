USE MyArtMuseum
GO

DROP TABLE IF EXISTS DepartmentProjects;
DROP TABLE IF EXISTS Projects;
DROP TABLE IF EXISTS Departments;
DROP PROCEDURE IF EXISTS populateTableDepartments;
DROP PROCEDURE IF EXISTS populateTableProjects;
DROP PROCEDURE IF EXISTS populateTableDepartmentProjects;
GO

-- Table Ta: Departments
CREATE TABLE Departments (
    dID INT NOT NULL PRIMARY KEY,
    deptartmentCode INT NOT NULL UNIQUE, 
    [name] VARCHAR(100) NOT NULL,
    [location] VARCHAR(100) NOT NULL
);
GO

-- Table Tb: Projects
CREATE TABLE Projects (
    pID INT NOT NULL PRIMARY KEY,
    projectCode INT NOT NULL,
    projectTitle VARCHAR(200) NOT NULL
);
GO

-- Table Tc: DepartmentProjects
CREATE TABLE DepartmentProjects (
	dpID INT NOT NULL,
    dID INT NOT NULL,
    pID INT NOT NULL,
    hoursAllocated INT NOT NULL,
    CONSTRAINT FK_Dept FOREIGN KEY (dID) REFERENCES Departments(dID) ON DELETE CASCADE,
    CONSTRAINT FK_Proj FOREIGN KEY (pID) REFERENCES Projects(pID) ON DELETE CASCADE
);
GO

CREATE PROCEDURE populateTableDepartments(@rows INT) AS
	while @rows > 0 
	BEGIN
		INSERT INTO Departments VALUES(@rows, @rows + 20, 'Name' + CAST(@rows AS VARCHAR(6)), 'Location' + CAST(@rows AS VARCHAR(6)))
		SET @rows = @rows - 1
	END;
GO

CREATE PROCEDURE populateTableProjects(@rows INT) AS
	while @rows > 0 
	BEGIN
		INSERT INTO Projects VALUES(@rows, @rows + 1, 'Title' + CAST(@rows AS VARCHAR(6)))
		SET @rows = @rows - 1
	END;
GO

CREATE PROCEDURE populateTableDepartmentProjects(@rows INT) AS
	IF @rows > (SELECT COUNT(*) FROM Departments) * (SELECT COUNT(*) FROM Projects) 
	BEGIN
		RAISERROR ('Too many entities requested', 10, 1)
	END
	DECLARE valuesCursor CURSOR LOCAL FOR (
		SELECT d.dID, p.pID
		FROM Departments d CROSS JOIN Projects p
	)
	DECLARE @dID INT
	DECLARE @pID INT
	OPEN valuesCursor
	FETCH valuesCursor INTO @dID, @pID
	while @@FETCH_STATUS = 0 AND @rows > 0 BEGIN
		INSERT INTO DepartmentProjects VALUES(@rows, @dID, @pID, @rows % 100 + 1)
		FETCH valuesCursor INTO @dID, @pID
		SET @rows = @rows - 1
	END
	CLOSE valuesCursor 
	DEALLOCATE valuesCursor;
GO

exec populateTableDepartments 10000;
exec populateTableProjects 10000;
exec populateTableDepartmentProjects 12000;



-- a. Write queries on Ta such that their execution plans contain the following operators:

IF EXISTS (SELECT * FROM sys.indexes WHERE name = 'index1')
    DROP INDEX index1 ON Departments;

IF NOT EXISTS (SELECT * FROM sys.indexes WHERE name = 'index1')
    CREATE NONCLUSTERED INDEX index1 ON Departments(deptartmentCode);

-- Clustered index scan
SELECT * FROM Departments ORDER BY deptartmentCode;

-- Clustered index seek
SELECT * FROM Departments WHERE deptartmentCode = 100;

-- Nonclustered index scan + Key lookup
SELECT deptartmentCode AS DepartmentCode FROM Departments;

-- Nonclustered index seek + Key lookup
SELECT * FROM Departments WHERE deptartmentCode = 14;


-- b. Write a query on table Tb with a WHERE clause of the form WHERE b2 = value and analyze its execution plan. 
-- Create a nonclustered index that can speed up the query. Recheck the query's execution plan (operators, SELECT's estimated subtree cost).

IF EXISTS (SELECT * FROM sys.indexes WHERE name = 'index2')
    DROP INDEX index2 ON Tb;

SELECT * FROM Projects WHERE projectCode = 1000;

CREATE NONCLUSTERED INDEX index2 on Projects(projectTitle);
SELECT * FROM Projects WHERE projectCode = 1000;
GO 


-- c. Create a view that joins at least 2 tables. Check whether existing indexes are helpful; 
-- if not, reassess existing indexes / examine the cardinality of the tables.

CREATE OR ALTER VIEW my_view AS 
	SELECT dp.pID, SUM(d.deptartmentCode) AS [sum]
	FROM DepartmentProjects dp INNER JOIN Projects p ON dp.pID = p.pID INNER JOIN Departments d ON dp.dID = d.dID
	WHERE d.deptartmentCode <= 10000 AND p.projectCode <= 10000
	GROUP BY dp.pID;
GO

SELECT * FROM my_view;
IF EXISTS (SELECT * FROM sys.indexes WHERE name = 'index1')
    DROP INDEX index1 ON Departments;
IF EXISTS (SELECT * FROM sys.indexes WHERE name = 'index2')
    DROP INDEX index2 ON Projects;

CREATE NONCLUSTERED INDEX index1 ON Departments(deptartmentCode);
CREATE NONCLUSTERED INDEX index2 on Projects(projectCode);
SELECT * FROM my_view;


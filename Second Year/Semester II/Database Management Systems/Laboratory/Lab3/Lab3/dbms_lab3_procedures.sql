use MyArtMuseum
go

-- tables chosen: Artworks and Exhibitions, linked by ArtworkExhibitions (m:n)
-- Artworks also depends on Artists, ArtworkTypes, Collections for foreign keys

-- log table to track executed actions
if object_id('dbo.LogTable', 'U') is not null
	drop table LogTable

create table LogTable (
	Lid int identity primary key,
	TypeOperation varchar(50),
	TableOperation varchar(100),
	Details varchar(500),
	ExecutionDate datetime default getdate()
)

go

-- validation functions

-- check that a varchar field is not null and not empty
create or alter function uf_ValidateNotEmpty(@value varchar(500))
returns int as
begin
	declare @result int = 0
	if @value is not null and ltrim(rtrim(@value)) <> ''
		set @result = 1
	return @result
end
go

-- check that creation year is between 1000 and current year
create or alter function uf_ValidateYear(@year int)
returns int as
begin
	declare @result int = 0
	if @year is not null and @year >= 1000 and @year <= year(getdate())
		set @result = 1
	return @result
end
go

-- check that end date is on or after start date
create or alter function uf_ValidateDateRange(@startDate date, @endDate date)
returns int as
begin
	declare @result int = 0
	if @startDate is not null and @endDate is not null and @endDate >= @startDate
		set @result = 1
	return @result
end
go

-- check that technique is one of the accepted values
create or alter function uf_ValidateTechnique(@technique varchar(200))
returns int as
begin
	declare @result int = 0
	if @technique in ('Oil on canvas', 'Watercolor', 'Fresco', 'Sculpture',
		'Photography', 'Engraving', 'Pastel', 'Acrylic', 'Tempera')
		set @result = 1
	return @result
end
go


-- create a stored procedure that inserts data in tables that are in a m:n relationship; 
-- if one insert fails, all the operations performed by the procedure must be rolled back
create or alter procedure procedure_1
	@artworkTitle varchar(300),
	@creationYear int,
	@technique varchar(200),
	@artistName varchar(300),
	@artworkTypeName varchar(200),
	@collectionName varchar(200),
	@exhibitionName varchar(300),
	@startDate date,
	@endDate date,
	@curatorName varchar(300),
	@exhibitionDesc varchar(1000)
as
begin
	declare @artID smallint
	declare @eID smallint
	declare @aID smallint
	declare @atID smallint
	declare @cID smallint
	declare @curatorID smallint

	begin transaction
	begin try
		if dbo.uf_ValidateNotEmpty(@artworkTitle) = 0
			throw 50001, 'Artwork title cannot be empty.', 1;

		if dbo.uf_ValidateYear(@creationYear) = 0
			throw 50002, 'Creation year must be between 1000 and the current year.', 1;

		if dbo.uf_ValidateTechnique(@technique) = 0
			throw 50003, 'Technique must be one of: Oil on canvas, Watercolor, Fresco, Sculpture, Photography, Engraving, Pastel, Acrylic, Tempera.', 1;

		if dbo.uf_ValidateNotEmpty(@exhibitionName) = 0
			throw 50004, 'Exhibition name cannot be empty.', 1;

		if dbo.uf_ValidateDateRange(@startDate, @endDate) = 0
			throw 50005, 'End date must be on or after start date.', 1;

		select @aID = aID from Artists where [name] = @artistName
		if @aID is null
			throw 50006, 'Artist not found.', 1;

		select @atID = atID from ArtworkTypes where [name] = @artworkTypeName
		if @atID is null
			throw 50007, 'Artwork type not found.', 1;

		select @cID = cID from Collections where [name] = @collectionName
		if @cID is null
			throw 50008, 'Collection not found.', 1;

		select @curatorID = eID from Employees where [name] = @curatorName
		if @curatorID is null
			throw 50009, 'Curator not found.', 1;

		if exists (select 1 from Exhibitions where curatorID = @curatorID)
			throw 50010, 'This curator is already assigned to another exhibition.', 1;

		insert into Artworks (title, creationYear, techinque, aID, atID, cID)
		values (@artworkTitle, @creationYear, @technique, @aID, @atID, @cID)

		set @artID = scope_identity()

		insert into LogTable (TypeOperation, TableOperation, Details)
		values ('INSERT', 'Artworks', concat('Inserted artwork: ', @artworkTitle))

		insert into Exhibitions ([name], startDate, endDate, curatorID, [description])
		values (@exhibitionName, @startDate, @endDate, @curatorID, @exhibitionDesc)

		set @eID = scope_identity()

		insert into LogTable (TypeOperation, TableOperation, Details)
		values ('INSERT', 'Exhibitions', concat('Inserted exhibition: ', @exhibitionName))

		insert into ArtworkExhibitions (artID, eID)
		values (@artID, @eID)

		insert into LogTable (TypeOperation, TableOperation, Details)
		values ('INSERT', 'ArtworkExhibitions', concat('Linked artID=', @artID, ' with eID=', @eID))

		commit transaction
		select 'Transaction committed successfully.' as Result
	end try
	begin catch
		rollback transaction

		insert into LogTable (TypeOperation, TableOperation, Details)
		values ('ROLLBACK', 'ALL', concat('Rolled back due to: ', error_message()))

		select 'Transaction rolled back.' as Result
		select error_number() as ErrorNumber, error_message() as ErrorMessage
	end catch
end;

-- example that works:
select * from Artworks
select * from Exhibitions
select * from ArtworkExhibitions

exec procedure_1
	@artworkTitle = 'Starry Night Over the Danube',
	@creationYear = 1890,
	@technique = 'Oil on canvas',
	@artistName = 'Vincent van Gogh',
	@artworkTypeName = 'Painting',
	@collectionName = 'Impressionism Collection',
	@exhibitionName = 'Light and Color',
	@startDate = '2024-03-01',
	@endDate = '2024-06-30',
	@curatorName = 'Alice Johnson',
	@exhibitionDesc = 'An exhibition of luminous works.'

select * from Artworks
select * from Exhibitions
select * from ArtworkExhibitions
select * from LogTable

-- example that does not work (invalid technique -> full rollback):
select * from Artworks
select * from Exhibitions
select * from ArtworkExhibitions

exec procedure_1
	@artworkTitle = 'Abstract Chaos',
	@creationYear = 2020,
	@technique = 'Digital Art',
	@artistName = 'Vincent van Gogh',
	@artworkTypeName = 'Painting',
	@collectionName = 'Impressionism Collection',
	@exhibitionName = 'Modern Visions',
	@startDate = '2024-07-01',
	@endDate = '2024-09-30',
	@curatorName = 'Bob Smith',
	@exhibitionDesc = 'Contemporary abstract works.'

select * from Artworks
select * from Exhibitions
select * from ArtworkExhibitions
select * from LogTable

go


-- create a stored procedure that inserts data in tables that are in a m:n relationship; 
-- if an insert fails, try to recover as much as possible from the entire operation;
-- if the artwork insert fails, the exhibition should still remain in the database, and vice versa

create or alter procedure procedure_2
	@artworkTitle varchar(300),
	@creationYear int,
	@technique varchar(200),
	@artistName varchar(300),
	@artworkTypeName varchar(200),
	@collectionName varchar(200),
	@exhibitionName varchar(300),
	@startDate date,
	@endDate date,
	@curatorName varchar(300),
	@exhibitionDesc varchar(1000)
as
begin
	declare @artID smallint = null
	declare @eID smallint = null
	declare @aID smallint
	declare @atID smallint
	declare @cID smallint
	declare @curatorID smallint

	begin transaction

	begin try
		save transaction sp_artwork

		if dbo.uf_ValidateNotEmpty(@artworkTitle) = 0
			throw 50001, 'Artwork title cannot be empty.', 1;

		if dbo.uf_ValidateYear(@creationYear) = 0
			throw 50002, 'Creation year must be between 1000 and the current year.', 1;

		if dbo.uf_ValidateTechnique(@technique) = 0
			throw 50003, 'Technique must be one of the accepted values.', 1;

		select @aID = aID from Artists where [name] = @artistName
		if @aID is null
			throw 50006, 'Artist not found.', 1;

		select @atID = atID from ArtworkTypes where [name] = @artworkTypeName
		if @atID is null
			throw 50007, 'Artwork type not found.', 1;

		select @cID = cID from Collections where [name] = @collectionName
		if @cID is null
			throw 50008, 'Collection not found.', 1;

		insert into Artworks (title, creationYear, techinque, aID, atID, cID)
		values (@artworkTitle, @creationYear, @technique, @aID, @atID, @cID)

		set @artID = scope_identity()

		insert into LogTable (TypeOperation, TableOperation, Details)
		values ('INSERT', 'Artworks', concat('Inserted artwork: ', @artworkTitle))
	end try
	begin catch
		rollback transaction sp_artwork

		insert into LogTable (TypeOperation, TableOperation, Details)
		values ('ROLLBACK (partial)', 'Artworks', concat('Artwork insert failed: ', error_message()))

		select concat('Artwork insert failed: ', error_message()) as ArtworkWarning
	end catch

	begin try
		save transaction sp_exhibition

		if dbo.uf_ValidateNotEmpty(@exhibitionName) = 0
			throw 50004, 'Exhibition name cannot be empty.', 1;

		if dbo.uf_ValidateDateRange(@startDate, @endDate) = 0
			throw 50005, 'End date must be on or after start date.', 1;

		select @curatorID = eID from Employees where [name] = @curatorName
		if @curatorID is null
			throw 50009, 'Curator not found.', 1;

		if exists (select 1 from Exhibitions where curatorID = @curatorID)
			throw 50010, 'This curator is already assigned to another exhibition.', 1;

		insert into Exhibitions ([name], startDate, endDate, curatorID, [description])
		values (@exhibitionName, @startDate, @endDate, @curatorID, @exhibitionDesc)

		set @eID = scope_identity()

		insert into LogTable (TypeOperation, TableOperation, Details)
		values ('INSERT', 'Exhibitions', concat('Inserted exhibition: ', @exhibitionName))
	end try
	begin catch
		rollback transaction sp_exhibition

		insert into LogTable (TypeOperation, TableOperation, Details)
		values ('ROLLBACK (partial)', 'Exhibitions', concat('Exhibition insert failed: ', error_message()))

		select concat('Exhibition insert failed: ', error_message()) as ExhibitionWarning
	end catch

	if @artID is not null and @eID is not null
	begin
		begin try
			save transaction sp_link

			insert into ArtworkExhibitions (artID, eID)
			values (@artID, @eID)

			insert into LogTable (TypeOperation, TableOperation, Details)
			values ('INSERT', 'ArtworkExhibitions', concat('Linked artID=', @artID, ' with eID=', @eID))
		end try
		begin catch
			rollback transaction sp_link

			insert into LogTable (TypeOperation, TableOperation, Details)
			values ('ROLLBACK (partial)', 'ArtworkExhibitions', concat('Link insert failed: ', error_message()))
		end catch
	end
	else
	begin
		insert into LogTable (TypeOperation, TableOperation, Details)
		values ('SKIP', 'ArtworkExhibitions',
			concat('Skipped link - artID=', isnull(cast(@artID as varchar), 'NULL'),
			', eID=', isnull(cast(@eID as varchar), 'NULL')))

		select 'Artwork-Exhibition link skipped because one or both inserts failed.' as LinkInfo
	end

	commit transaction
	select 'Procedure completed (partial inserts may have occurred).' as Result
	select * from LogTable order by Lid
end;

-- example that works:
select * from Artworks
select * from Exhibitions
select * from ArtworkExhibitions

exec procedure_2
	@artworkTitle = 'Autumn Reflections',
	@creationYear = 1905,
	@technique = 'Watercolor',
	@artistName = 'Claude Monet',
	@artworkTypeName = 'Painting',
	@collectionName = 'Impressionism Collection',
	@exhibitionName = 'Seasons in Color',
	@startDate = '2024-10-01',
	@endDate = '2024-12-31',
	@curatorName = 'Carol White',
	@exhibitionDesc = 'Seasonal artwork from across Europe.'

select * from Artworks
select * from Exhibitions
select * from ArtworkExhibitions
select * from LogTable

-- example that does not fully work (bad technique -> artwork fails, exhibition still inserted):
select * from Artworks
select * from Exhibitions
select * from ArtworkExhibitions

exec procedure_2
	@artworkTitle = 'Glitch in the System',
	@creationYear = 2021,
	@technique = 'NFT',
	@artistName = 'Claude Monet',
	@artworkTypeName = 'Painting',
	@collectionName = 'Impressionism Collection',
	@exhibitionName = 'Future Forms',
	@startDate = '2025-01-01',
	@endDate = '2025-03-31',
	@curatorName = 'David Brown',
	@exhibitionDesc = 'Exploring the future of art.'

-- artwork 'Glitch in the System' should NOT exist, exhibition 'Future Forms' SHOULD exist
select * from Artworks
select * from Exhibitions
select * from ArtworkExhibitions
select * from LogTable
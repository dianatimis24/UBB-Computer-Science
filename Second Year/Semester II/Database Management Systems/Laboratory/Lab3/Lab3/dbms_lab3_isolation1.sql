-- reproduce the following concurrency issues under pessimistic isolation 
-- levels: dirty read, non-repeatable read, phantom read, deadlock; 
-- you can use stored procedures and / or stand-alone queries; 
-- find solutions to solve / workaround the concurrency issues 

use MyArtMuseum

-- dirty read
select * from ArtStyles

begin transaction
update ArtStyles set [description] = 'brand new dirty description'
where asID = 1
waitfor delay '00:00:10'
rollback transaction

-- non-repeatable read
begin tran
waitfor delay '00:00:05'
update ArtStyles set [description] = 'updated during T2 read'
where asID = 1
commit tran

-- phantom read
begin tran
waitfor delay '00:00:05'
insert into ArtStyles ([name], [period], [description])
values ('Neo-Expressionism', '1970s-1990s', 'Raw emotional expressionism revival')
commit tran

-- deadlock
begin tran
update ArtStyles set [description] = 'Deadlock T1' where asID = 1
waitfor delay '00:00:10'
update Artists set originCountry = 'Deadlock T1' where aID = 1
commit tran


-- solution: run both updates in the same order in both transactions
begin tran
update ArtStyles set [description] = 'Solution T1' where asID = 1
waitfor delay '00:00:10'
update Artists set originCountry = 'Solution T1' where aID = 1
commit tran



-- reproduce the update conflict under an optimistic isolation level
alter database MyArtMuseum set ALLOW_SNAPSHOT_ISOLATION ON

waitfor delay '00:00:05'
begin tran
update ArtStyles set [description] = 'Updated by T1 - optimistic conflict test'
where asID = 1
waitfor delay '00:00:05'
commit tran

alter database MyArtMuseum set ALLOW_SNAPSHOT_ISOLATION OFF
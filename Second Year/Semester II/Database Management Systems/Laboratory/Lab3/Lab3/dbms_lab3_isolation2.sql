use MyArtMuseum

-- dirty read
set transaction isolation level read uncommitted

begin tran
select * from ArtStyles
waitfor delay '00:00:15'
select * from ArtStyles
commit tran

-- solution: set level to read committed
set transaction isolation level read committed

begin tran
select * from ArtStyles
waitfor delay '00:00:15'
select * from ArtStyles
commit tran


-- non-repeatable read
set transaction isolation level read committed

begin tran
select * from ArtStyles where asID = 1
waitfor delay '00:00:10'
select * from ArtStyles where asID = 1
commit tran

-- solution: set level to repeatable read
set transaction isolation level repeatable read

begin tran
select * from ArtStyles where asID = 1
waitfor delay '00:00:10'
select * from ArtStyles where asID = 1
commit tran


-- phantom read
set transaction isolation level repeatable read

begin tran
select * from ArtStyles
waitfor delay '00:00:10'
select * from ArtStyles
commit tran

-- solution: set level to serializable
set transaction isolation level serializable

begin tran
select * from ArtStyles
waitfor delay '00:00:10'
select * from ArtStyles
commit tran


-- deadlock
begin tran
update Artists set originCountry = 'Deadlock T2' where aID = 1
waitfor delay '00:00:10'
update ArtStyles set [description] = 'Deadlock T2' where asID = 1
commit tran

-- solution: set deadlock priority high on T2 so T1 is chosen as the victim (implicit priority is normal = 0; T2 survives, T1 is rolled back)
set deadlock_priority high

begin tran
update ArtStyles set [description] = 'Solution T2' where asID = 1
waitfor delay '00:00:10'
update Artists set originCountry = 'Solution T2' where aID = 1
commit tran


-- reproduce the update conflict under an optimistic isolation level
-- T2 reads asID=1 under SNAPSHOT isolation (gets version from start of transaction)
-- T1 commits an update to asID=1 while T2 is active
-- when T2 tries to update the same row -> Error 3960 (update conflict)

set transaction isolation level snapshot
begin tran
select * from ArtStyles where asID = 1
waitfor delay '00:00:10'
select * from ArtStyles where asID = 1
update ArtStyles set [description] = 'Updated by T2 - will cause conflict'
where asID = 1

-- error 3960: snapshot isolation transaction aborted due to update conflict
commit tran
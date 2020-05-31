use ridesharing

select * from Users
select * from Rides
select * from UserRideBridge


---delete from Users where id > 20---

---- SETUP ----

-- HPI = M2M
drop table if exists logs_for_insert_in_HPI
drop table if exists logs_for_insert_in_HPI_v2
drop table if exists transactions
drop procedure if exists insert_in_HPI
drop procedure if exists insert_in_HPI_v2

create table logs_for_insert_in_HPI(
	id int primary key identity,
	descr varchar(1000)
)

create table logs_for_insert_in_HPI_v2(
	id int primary key identity,
	descr varchar(1000)
)

create table transactions(
	id int primary key identity,
	tran_type varchar(75),
	descr varchar(1000)
)

---- V1 ----
go
create procedure insert_in_HPI 
	@identityDocument char(8),
	@firstName varchar(30),
	@lastName varchar(30),
	@birthDate date,
	@isDriver bit,
	@driverId char(8),
	@startAddress varchar(50),
	@endAddress varchar(50),
	@fare float,
	@vehicleId int
as
		insert into logs_for_insert_in_HPI (descr) values ('begun tran')
		begin tran 
	begin try
		insert into Users (IdentityDocument, FirstName, LastName, BirthDate, IsDriver) values (@identityDocument, @firstName, @lastName, @birthDate, @isDriver)
		insert into logs_for_insert_in_HPI (descr) values ('Inserted in Users ID ' + @identityDocument + ' ' +  @firstName + ' ' + @lastName + ' ' + convert(varchar(1), @isDriver))
		
		insert into Rides(DriverId, StartAddress, EndAddress, Fare, VehicleId) values (@driverId, @startAddress, @endAddress, @fare, @vehicleId)
		insert into logs_for_insert_in_HPI (descr) values ('Inserted in Rides ' + @driverId + ' ' + @startAddress + ' ' + @endAddress + ' ' + convert(varchar(50), @fare)+ ' ' + convert(varchar(50), @vehicleId))
		
		declare @rid int
		set @rid = (select RideId from Rides where DriverId = @driverId and StartAddress = @startAddress and EndAddress = @endAddress and Fare = @fare and VehicleId = @vehicleId)
		insert into UserRideBridge values (@identityDocument, @rid)
		insert into logs_for_insert_in_HPI (descr) values ('Inserted in UserRideBridge ' + @identityDocument + ' ' + convert(varchar(50), @rid))
		commit transaction
		insert into logs_for_insert_in_HPI (descr) values ('Transaction commited')
	end try
	begin catch
		print 'Insertion error, rolling back'
		rollback tran
		insert into logs_for_insert_in_HPI (descr) values ('Insertion error, rolled back to last succesful transaction')
		end catch	

delete from Users where IdentityDocument = 'XAEA12R5'
delete from Users where IdentityDocument = 'ABCD1234'
delete from Rides where StartAddress = 'Zorilor 5' and EndAddress = 'Garoafelor 3'
delete from UserRideBridge where UserId = 'ABCD1234'
delete from Vehicles where UserId = 'XAEA12R5'

insert into Users (IdentityDocument, FirstName, LastName, BirthDate, IsDriver) values ('XAEA12R5', 'X Æ A-12', 'Musk', '2020-05-16', 1)
insert into Vehicles (VehicleType, NumberSeats, UserId) values ('car', 5, 'XAEA12R5')
declare @vid int
set @vid = (select VehicleId from Vehicles where UserId = 'XAEA12R5')

exec insert_in_HPI 'ABCD1234', 'Mack', 'Mack', '1990-03-15', 0, 'XAEA12R5', 'Zorilor 5', 'Garoafelor 3', 28.5, @vid

select * from logs_for_insert_in_HPI


---- V2 ----
go
create procedure insert_in_HPI_v2
	@identityDocument char(8),
	@firstName varchar(30),
	@lastName varchar(30),
	@birthDate date,
	@isDriver bit,
	@driverId char(8),
	@startAddress varchar(50),
	@endAddress varchar(50),
	@fare float,
	@vehicleId int
as
	insert into logs_for_insert_in_HPI_v2 (descr) values ('Here we go again')

	begin tran 
	begin try
		insert into Users(IdentityDocument, FirstName, LastName, BirthDate, IsDriver) values (@identityDocument, @firstName, @lastName, @birthDate, @isDriver)
		insert into logs_for_insert_in_HPI_v2 (descr) values ('Inserted in Users ID ' + @identityDocument + ' ' +  @firstName + ' ' + @lastName + ' ' + convert(varchar(1), @isDriver))
		save tran insert_user
		if(@@ERROR<>0)
			rollback tran
			insert into logs_for_insert_in_HPI_v2 (descr) values ('Insertion error, rolling back transaction')

		insert into Rides(DriverId, StartAddress, EndAddress, Fare, VehicleId) values (@driverId, @startAddress, @endAddress, @fare, @vehicleId)
		insert into logs_for_insert_in_HPI_v2 (descr) values ('Inserted in Rides ' + @driverId + ' ' + @startAddress + ' ' + @endAddress + ' ' + convert(varchar(50), @fare)+ ' ' + convert(varchar(50), @vehicleId))
		save tran insert_ride
		if(@@ERROR<>0)
			rollback tran insert_user
			insert into logs_for_insert_in_HPI_v2 (descr) values ('Insertion error, rolling back transaction')

		declare @rid int
		set @rid = (select RideId from Rides where DriverId = @driverId and StartAddress = @startAddress and EndAddress = @endAddress and Fare = @fare and VehicleId = @vehicleId)
		insert into UserRideBridge values (@identityDocument, @rid)
		insert into logs_for_insert_in_HPI_v2 (descr) values ('Inserted in UserRideBridge ' + @identityDocument + ' ' + convert(varchar(50), @rid))
		if(@@ERROR<>0)
			rollback tran insert_ride
			insert into logs_for_insert_in_HPI_v2 (descr) values ('Insertion error, rolling back transaction')

		commit transaction
		insert into logs_for_insert_in_HPI_v2 (descr) values ('Transaction commited')
	end try
	begin catch
	end catch	
go


delete from Users where IdentityDocument = 'XAEA12R5'
delete from Users where IdentityDocument = 'ABCD1234'
delete from Rides where StartAddress = 'Zorilor 5' and EndAddress = 'Garoafelor 3'
delete from UserRideBridge where UserId = 'ABCD1234'
delete from Vehicles where UserId = 'XAEA12R5'

insert into Users (IdentityDocument, FirstName, LastName, BirthDate, IsDriver) values ('XAEA12R5', 'X Æ A-12', 'Musk', '2020-05-16', 1)
insert into Vehicles (VehicleType, NumberSeats, UserId) values ('car', 5, 'XAEA12R5'
declare @vid int
-- MAY NEED LIMIT 1
set @vid = (select VehicleId from Vehicles where UserId = 'XAEA12R5')

exec insert_in_HPI 'ABCD1234', 'Mack', 'Mack', '1990-03-15', 0, 'XAEA12R5', 'Zorilor 5', 'Garoafelor 3', 28.5, @vid

SELECT transaction_isolation_level
FROM sys.dm_exec_sessions
WHERE session_id = @@SPID


---- Dirty Read ----
set transaction isolation level read uncommitted
begin tran 
	------ 2
	insert into transactions (tran_type, descr) values ('dirty read', 'Update data, regardless isolation level')
	update Rides set EndAddress = 'Garoafelor 24' where VehicleId = @vid
	rollback tran

--- select * from Review
--- update Review set comment = null where rid = 3


---- Non-repeatable Read ----
set transaction isolation level repeatable read

begin tran
declare @isol int
	set @isol = (SELECT transaction_isolation_level FROM sys.dm_exec_sessions WHERE session_id = @@SPID)
	if @isol <= 2 
		insert into transactions(tran_type, descr) values ('non-repeatable read', 'Non-repeatable transaction')
	else
		insert into transactions (tran_type, descr) values ('non-repeatable read', 'Repeatable read level, valid transaction')


	----select * from Review where mid = 7

	---select * from Review where mid = 7
commit tran


---- Phantom Reads ----
-- SOLUTION set transaction isolation level serializable
begin tran
	--declare @isol int
	set @isol = (SELECT transaction_isolation_level FROM sys.dm_exec_sessions WHERE session_id = @@SPID)
	if @isol = 4 
		insert into transactions (tran_type, descr) values ('phantom', 'Isolation level is serializable, no phantom')
	else
		insert into transactions(tran_type, descr) values ('phantom', 'Phantom read')

	----- 1
	-- select count(*) from Review

	------ 3
	-- select count(*) from Review
commit tran

-- select * from Review
-- update Review set email = null where rid = 3 or rid = 4
-- update Review set mark = 1 where rid = 3


----- do this with id

---- Deadlock ----
begin tran
	insert into transactions(tran_type, descr) values ('deadlock', 'Transactions wait after each other, creating a deadlock')
	---- 2
	--update Review set email = 'email1@email.varza' where id = 
	---- 4
	--update Review set email = 'email2@email.varza' where username = 'ciorbelVerginique' 
commit tran


---- Update Conflict ----
begin tran
	-- 2
	---update Review set mark = mark+1 where rid = 3

	rollback tran
	commit tran

	------------------todo log everything, take a look again at the deadlock-------------------
	select * from transactions
use ridesharing

---- Dirty Read ----
set transaction isolation level read uncommitted
-- DEFAULT set transaction isolation level read committed
begin tran
	declare @isol int
	----- 1
	set @isol = (SELECT transaction_isolation_level FROM sys.dm_exec_sessions WHERE session_id = @@SPID)
	if @isol = 1 
		insert into transactions(tran_type, descr) values ('dirty read', 'Transaction will read innacurate data')
	else
		insert into transactions (tran_type, descr) values ('dirty read', 'Isolation level read commited, read will be correct')
select * from movie
-- 3
commit tran
---------------------------------------------


SELECT transaction_isolation_level
FROM sys.dm_exec_sessions
WHERE session_id = @@SPID

---- Non-repeatable Read ----
insert into transactions (tran_type, descr) values ('non-repeatable read', 'Update regardless of isolation level')
update Review set comment = 'naiz' where username = 'miau'
-------------------------------------------


select rid from Review
delete from Review where rid = 11
---- Phantom Reads ----
set transaction isolation level repeatable read
-- set transaction isolation level serializable

----- 2
insert into transactions (tran_type, descr) values ('phantom', 'Update regardless of isolation level')
insert into Review(mark, username, mid) values(2,'miau', 1)
----------------------------------------------------------



---- Deadlock ----
begin tran
	insert into transactions(tran_type, descr) values ('deadlock', 'here we let the transactions wait after each other, creating a deadlock')
	---- 1
	update Review set email = 'email2@email.varza' where username = 'ciorbelVerginique' 
	---- 3
	update Review set email = 'email1@email.varza' where username = 'miau'
commit tran

---------------------------------------------------------

select * from Review

---- Update Conflict ----
ALTER DATABASE ridesharing
SET ALLOW_SNAPSHOT_ISOLATION ON  
set transaction isolation level snapshot

begin tran	
	--declare @isol int
	set @isol = (SELECT transaction_isolation_level FROM sys.dm_exec_sessions WHERE session_id = @@SPID)
	if @isol = 5 
		insert into transactions (tran_type, descr) values ('update conflict', 'Isolation level snapshot, transaction will abort in case one commits or proceed normaly otherwise')
	else
		insert into transactions(tran_type, descr) values ('update conflict', '')
	
	-- 1
	select mark from Review where rid = 3
	-- 3
	update Review set mark = mark + 2 where rid = 3
commit tran
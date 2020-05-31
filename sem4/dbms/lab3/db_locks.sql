SELECT resource_type, resource_database_id, request_mode, request_type, request_status,
request_session_id, request_owner_type, request_owner_id
FROM sys.dm_tran_locks
WHERE resource_database_id = (select database_id from sys.databases where name =
'ridesharing' and resource_type = 'KEY')


--- T1
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ
GO
BEGIN TRAN
--- First step
SELECT * FROM Producers WHERE awards >= 5 AND awards <= 9

--- Third step
SELECT * FROM Producers WHERE awards >= 5 AND awards <= 9

COMMIT TRAN


--- T2
GO
BEGIN TRAN
--- Second Step
INSERT INTO Producers (first_name, last_name, nationality, awards) VALUES ('Foo', 'Bar', 'Internetz', 7)
COMMIT TRAN


--- Explanation: If the isolation level is set to less than SERIALIAZABLE, T1 cannot request a Shared lock for the entire range affected by the SELECT predicate
--- This allows T2 to insert rows that would fall under T1's query, i.e. the phantom rows
--- The two transactions are conflict serialiazable, proving that conflict serialiazability does not guarantee that schedule is serialiazable when inserting
CREATE OR ALTER PROCEDURE InsertB @Rows INT
AS
BEGIN
	DECLARE @i INT
	SET @i = 1
	WHILE @i <= @Rows
	BEGIN
		INSERT INTO TableB(id, bar) VALUES (@i, @i)
		SET @i = @i + 1
	END
END
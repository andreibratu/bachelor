CREATE OR ALTER PROCEDURE InsertAB @Rows INT
AS
BEGIN
	DECLARE @i INT
	SET @i = 1
	WHILE @i <= @Rows
	BEGIN
		INSERT INTO TableABBridge(ida, idb) VALUES (@i, @i)
		SET @i = @i + 1
	END
END
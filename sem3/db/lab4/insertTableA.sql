CREATE OR ALTER PROCEDURE InsertTable @TableName VARCHAR(50), @Rows INT
AS
BEGIN
	DECLARE @i INT
	DECLARE @sql VARCHAR(300)
	SET @i = 1
	WHILE @i <= @Rows
	BEGIN
		SET @sql = 'INSERT INTO ' + @TableName + ' VALUES' + '(' + @i + ',' + @i + ')';
		EXEC (@sql)
		SET @i = @i + 1
	END
END
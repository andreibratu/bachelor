CREATE PROCEDURE DropColumnDefault (@TableName VARCHAR(60), @ColumnName VARCHAR(60))
AS
	EXECUTE sp_executesql N'ALTER TABLE @TableName ALTER COLUMN @ColumnName DROP DEFAULT;';
GO
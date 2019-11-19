CREATE PROCEDURE RemoveColumn (@TableName VARCHAR(60), @ColumnName VARCHAR(60))
AS
	EXECUTE sp_executesql N'ALTER TABLE @TableName DROP COLUMN @ColumnName;';
GO
CREATE PROCEDURE DropTable (@TableName VARCHAR(100))
AS
	EXECUTE ps_executesql N'DROP TABLE @TableName;';
GO
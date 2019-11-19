CREATE PROCEDURE AddColumnDefault (@TableName VARCHAR(60), @ColumnName VARCHAR(60))
AS
	DECLARE @ConstrName VARCHAR(200);
	SET @ConstrName = @TableName + '_' + @ColumnName + '+_default';
	EXECUTE sp_executesql N'ALTER TABLE @TableName ADD CONSTRAINT @ConstrName DEFAULT @DefaultValue FOR @ColumnName;';
GO
CREATE PROCEDURE CreateTable (@TableName VARCHAR(200), @PKType VARCHAR(100))
AS
	DECLARE @TablePKColumnName VARCHAR(100);
	DECLARE @PKConstraintName VARCHAR(100);
	SET @TablePKColumnName = @TableName + 'ID';
	SET @PKConstraintName = @TableName + '_PKConstraint';

	EXECUTE sp_executesql 
	N'CREATE TABLE @TableName ( 
		@TablePKColumnName @PKType NOT NULL,
		CONSTRAINT @PKConstraintName PRIMARY KEY ( @PKType )
	);';
GO
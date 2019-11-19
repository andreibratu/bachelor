/*  @Columns is expected to be a tuple of form (col1,col2,...) */
CREATE PROCEDURE AddCandidateKey (@TableName VARCHAR(100), @Columns VARCHAR(100))
AS
	DECLARE @ConstraintName VARCHAR(200);
	SET @ConstraintName = 'CK_' + @TableName;
	EXEC sp_executesql N'ALTER TABLE @TableName ADD CONSTRAINT UNIQUE @Columns;';
GO
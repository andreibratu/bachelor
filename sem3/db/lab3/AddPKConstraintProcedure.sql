/* 
@ColumnNames is expected to be a string-represented tuple 
of all columns falling under PK constraint - e.g. (id1,id2,...)
*/
CREATE PROCEDURE AddPrimaryKeyConstraint (@TableName VARCHAR(50), @ColumnNames VARCHAR(100))
AS
	DECLARE @ConstraintName VARCHAR(100);

	SET @ConstraintName = 'PK_' + @TableName;

	EXECUTE sp_executesql
	N'ALTER TABLE @TableName ADD CONSTRAINT @ConstraintName PRIMARY KEY @ColumnNames;';	
GO
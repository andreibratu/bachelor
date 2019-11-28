CREATE PROCEDURE DropColumnProcedure
AS
	ALTER TABLE Foobar DROP COLUMN Foo;

	IF @@ERROR = 0
		INSERT INTO Versioning VALUES('AddColumnProcedure');
		UPDATE CurrentVersion SET CVersion = CVersion + 1;
GO

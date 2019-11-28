CREATE PROCEDURE AddColumnProcedure
AS
	ALTER TABLE Foobar ADD Foo BIT;

	IF @@ERROR = 0
		INSERT INTO Versioning VALUES ('DropColumnProcedure');
		UPDATE CurrentVersion SET CVersion = CVersion + 1;
GO

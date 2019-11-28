CREATE PROCEDURE AddColumnDefaultProcedure
AS
	ALTER TABLE Foobar ADD CONSTRAINT Users_BAR_default DEFAULT 'cool' FOR Bar;

	IF @@ERROR = 0
		INSERT INTO Versioning VALUES ('DropColumnDefaultProcedure')
		UPDATE CurrentVersion SET CVersion = CVersion + 1;

GO

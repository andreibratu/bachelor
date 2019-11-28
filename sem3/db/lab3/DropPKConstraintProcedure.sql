CREATE PROCEDURE DropPrimaryKeyConstraint
AS
	ALTER TABLE Foobar DROP CONSTRAINT PK_Foobar;

	IF @@ERROR = 0
		INSERT INTO Versioning VALUES ('AddPrimaryKeyConstraint')
		UPDATE CurrentVersion SET CVersion = CVersion + 1;
GO

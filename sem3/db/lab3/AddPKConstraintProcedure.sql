CREATE PROCEDURE AddPrimaryKeyConstraint
AS
	ALTER TABLE Foobar ADD CONSTRAINT PK_Foobar PRIMARY KEY (Id);

	IF @@ERROR = 0
		INSERT INTO Versioning VALUES ('DropPrimaryKeyConstraint');
		UPDATE CurrentVersion SET CVersion = CVersion + 1;
GO

CREATE PROCEDURE AddCandidateKeyProcedure
AS
	ALTER TABLE Foobar ADD CONSTRAINT CKFoobar_Constr UNIQUE (Bar);

	IF @@ERROR = 0
		INSERT INTO Versioning VALUES ('DropCandidateKeyProcedure');
		UPDATE CurrentVersion SET CVersion = CVersion + 1;
GO

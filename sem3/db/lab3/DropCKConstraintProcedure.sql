CREATE PROCEDURE DropCandidateKey (@TableName VARCHAR(100))
AS
	ALTER TABLE Foobar DROP CONSTRAINT CKFoobar_Constr;

	IF @@ERROR = 0
		INSERT INTO Versioning VALUES ('AddCandidateKeyProcedure');
		UPDATE CurrentVersion SET CVersion = CVersion + 1;
GO

CREATE PROCEDURE CreateTableProcedure
AS
	DECLARE @CV INT;
	SET @CV = (SELECT CVersion FROM CurrentVersion);
	CREATE TABLE Foobar (
		Id INT NOT NULL UNIQUE,
		Bar VARCHAR(100) NOT NULL
	);

	IF @@ERROR = 0

		INSERT INTO Versioning VALUES (@CV, 'DropTableProcedure');
		UPDATE CurrentVersion SET CVersion = CVersion + 1;
GO

CREATE PROCEDURE DropTableProcedure
AS
	DROP TABLE Foobar;

	IF @@ERROR = 0
		INSERT INTO Versioning VALUES ('CreateTableProcedure');
		UPDATE CurrentVersion SET CVersion = CVersion + 1;
GO

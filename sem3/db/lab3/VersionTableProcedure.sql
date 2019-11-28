CREATE PROCEDURE VersionTable(@Version INT)
AS
	DECLARE @CurrentVersion INT;
	DECLARE @Query NVARCHAR(200);

	SET @CurrentVersion = (SELECT MAX(CVersion) FROM CurrentVersion);

	WHILE @CurrentVersion < @Version
		SET @CurrentVersion = @CurrentVersion + 1;
		SET @Query = (SELECT Query FROM Versioning WHERE Id = @CurrentVersion);
		EXEC @Query;

	WHILE @CurrentVersion > @Version
		SET @CurrentVersion = @CurrentVersion - 1;
		SET @Query = (SELECT Query FROM Versioning WHERE Id = @CurrentVersion);
		EXEC @Query

	UPDATE CurrentVersion SET CVersion = @CurrentVersion;
GO
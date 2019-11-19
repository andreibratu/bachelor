/* Procedure to track changes for any given table */

CREATE PROCEDURE VersionTable (@TableName VARCHAR(50))
AS
	DECLARE @VersionId INT;
	DECLARE @TN VARCHAR(50), @CN VARCHAR(50), @IN VARCHAR(3), @DT VARCHAR(20), @CML INT; 

	/* Find VersionId for backup */
	SELECT @VersionId = MAX(VersionId) FROM dbo.Versioning;

	IF @VersionId IS NULL
	BEGIN
		SET @VersionId = 0
	END
	ELSE
	BEGIN
		SET @VersionId = @VersionId + 1
	END
	
	/* Iterate through @TableName table meta information and save it in Versioning */
	DECLARE InfoCursor CURSOR FOR
	SELECT TABLE_NAME, COLUMN_NAME, IS_NULLABLE, DATA_TYPE, CHARACTER_MAXIMUM_LENGTH
	FROM INFORMATION_SCHEMA.COLUMNS
	WHERE TABLE_NAME = @TableName;
	
	OPEN InfoCursor;

	FETCH InfoCursor INTO @TN, @CN, @IN, @DT, @CML;
	
	WHILE @@FETCH_STATUS = 0
	BEGIN
		/* For each column meta insert onew row in Versioning */
		INSERT INTO Versioning (VersionId, TABLE_NAME, COLUMN_NAME, IS_NULLABLE, DATA_TYPE, CHARACTER_MAXIMUM_LENGTH)
		VALUES (@VersionId, @TN, @CN, @IN, @DT, @CML);

		FETCH InfoCursor
		INTO @TN, @CN, @IN, @DT, @CML;
	END
GO

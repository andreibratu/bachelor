INSERT INTO Tables(Name) VALUES
	('TableA'),
	('TableB'),
	('TableABBridge')


SELECT * FROM Tables;

INSERT INTO Views(Name)
VALUES
	('TableAView'),
	('TableABGroupView'),
	('TableAB')

INSERT INTO Tests VALUES ('test1');

INSERT INTO Tests VALUES ('test2');

INSERT INTO Tests VALUES ('test3');

DELETE FROM TestTables;

INSERT INTO TestTables VALUES (1, 7, 1000, 500);

INSERT INTO TestTables VALUES (2, 8, 5000, 800);
INSERT INTO TestTables VALUES (3, 9, 10000, 9500)

INSERT INTO TestViews VALUES (3, 3);

GO

CREATE OR ALTER PROCEDURE RunTest @TestId INT
AS
BEGIN
	DECLARE @TableId INT;
	DECLARE @ViewId INT;
	DECLARE @RowsInsert INT;
	DECLARE @RowsDelete INT;

	DECLARE @TableName VARCHAR(100);
	DECLARE @ViewName VARCHAR(100);
	DECLARE @TestName VARCHAR(100);

	SET @TableId = (SELECT TableID FROM TestTables WHERE TestID = @TestId);
	SET @RowsInsert = (SELECT NoOfRows FROM TestTables WHERE TestID = @TestId);
	SET @RowsDelete = (SELECT Position FROM TestTables WHERE TestID = @TestId);
	SET @ViewId = (SELECT ViewId FROM TestViews WHERE TestID = @TestId);

	SET @TestName = (SELECT Name from Tests WHERE TestID = @TestId);
	SET @TableName = (SELECT Name FROM Tables WHERE TableID = @TableId);
	SET @ViewName = (SELECT Name FROM Views WHERE ViewID = @TableId);

	DECLARE @StartInsertDelete DATETIME
	DECLARE @EndInsertDelete DATETIME

	DECLARE @StartView DATETIME
	DECLARE @EndView DATETIME

	SET @StartInsertDelete = GETDATE();

	EXEC InsertTable @TableName, @RowsInsert;
	EXEC DeleteMock @TableName, @RowsDelete;

	SET @EndInsertDelete = GETDATE();

	DECLARE @ViewSQL VARCHAR(100);
	SET @ViewSQL = 'SELECT * FROM ' + @ViewName;

	SET @StartView = GETDATE()
	EXEC (@ViewSQL)
	SET @EndView = GETDATE()


	DECLARE @myRunId INT
	INSERT INTO TestRuns VALUES(@TestName, @StartInsertDelete, @EndInsertDelete);
	SET @myRunId = (SELECT MAX(TestRunID) FROM TestRuns);
	PRINT @myRunID
	INSERT INTO TestRunTables VALUES (@myRunId, @TableID, @StartInsertDelete, @EndInsertDelete);
	INSERT INTO TestRunViews VALUES(@myRunId, @ViewId, @StartView, @EndView);
END

EXEC RunTest 3;

SELECT * FROM TestRuns;

DELETE FROM TestRunTables;

SELECT * FROM TestRuns;
SELECT * FROM TestRunTables;
SELECT * FROM TestRunViews;
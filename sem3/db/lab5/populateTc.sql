DECLARE @aSize INT;
DECLARE @bSize INT;
DECLARE @i INT;

PRINT(@aSize)
PRINT(@bSize)

SET @aSize = (SELECT COUNT(*) FROM Ta);
SET @bSize = (SELECT COUNT(*) FROM Tb);
SET @i = 1;

DECLARE @aIdx INT;
DECLARE @bIdx INT;

WHILE @i < 500
BEGIN
	SET @aIdx = RAND()*@aSize;
	SET @bIdx = RAND()*@bSize;
	PRINT(@aIdx)
	PRINT(@bIdx)
	INSERT INTO Tc VALUES (@aIdx, @bIdx);
	SET @i = @i + 1;
END

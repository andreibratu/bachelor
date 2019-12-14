USE [ridesharing]
GO

/****** Object:  StoredProcedure [dbo].[DeleteMock]    Script Date: 12.12.2019 16:28:18 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE OR ALTER   PROC [dbo].[DeleteMock] @Percent INT, @Table VARCHAR(50)
AS
BEGIN
	DECLARE @sqlCommand varchar(1000);
	SET @sqlCommand = 'DELETE TOP (' + @Percent + ') FROM ' + @Table;
	EXEC (@sqlCommand);
END



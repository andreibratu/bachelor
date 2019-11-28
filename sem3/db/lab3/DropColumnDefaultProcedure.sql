CREATE PROCEDURE DropColumnDefaultProcedure
AS
  DROP DEFAULT IF EXISTS Bar;

  IF @@ERROR = 0
    INSERT INTO Versioning VALUES ('AddColumnDefaultProcedure');
    UPDATE CurrentVersion SET CVersion = CVersion + 1;
GO

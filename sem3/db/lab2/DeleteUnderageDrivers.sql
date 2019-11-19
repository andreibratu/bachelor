/* Delete all drivers that are underage */

DELETE FROM Users
WHERE DATEDIFF(MONTH, GETDATE(), [BirthDate]) / 12 < 18 AND IsDriver = 1;
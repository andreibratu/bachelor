/* Select all drivers older than 25 */

/* g */

SELECT FirstName, LastName
FROM (SELECT * FROM Users WHERE IsDriver = 1) AS DriverUsers
WHERE DATEDIFF(MONTH, BirthDate, GETDATE()) / 12 > 25;

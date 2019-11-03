/* Select all drivers older than 25 */
SELECT FirstName, LastName, BirthDate, IsDriver
FROM Users
WHERE IsDriver = 1
INTERSECT
SELECT FirstName, LastName, BirthDate, IsDriver
FROM Users
WHERE DATEDIFF(MONTH, BirthDate, GETDATE()) / 12 > 25;
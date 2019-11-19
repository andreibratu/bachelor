/* Find oldest driver in database */
/* i */

SELECT IdentityDocument, BirthDate
FROM (SELECT * FROM Users WHERE IsDriver = 1) AS UserDrivers
WHERE BirthDate <= ALL (SELECT BirthDate FROM Users)
